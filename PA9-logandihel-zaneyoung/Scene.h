#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "testing.h"
#include "Button.h"
#include "LocalPlayer.h"
#include "map.h"
#include "collisionHandler.h"
#include "PauseMenu.h"

using std::string;
using std::ifstream;
using std::vector;


// forward declarations
class MenuScene;
class SplashScene;
class CarSelectScene;
class PlayScene;
class Scene;

extern Scene * CurrentScene;
extern sf::RenderWindow * gameObj;

// plz extend me
class Scene : public sf::Drawable {

public:
	Scene(sf::Vector2f &size = sf::Vector2f(0, 0), string textureFilePath="", std::vector<sf::Drawable *> &drawables=std::vector<sf::Drawable *>(), string name="");
	virtual ~Scene();
	virtual void update(); // update the view
	virtual void updatePhysics(float dt);
	
	string getName();
	void setName(string &name);
	sf::View * getView();
	sf::Vector2f getSize();
	void setTexture(sf::Texture * newTexture);

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	std::vector<sf::Drawable *> drawables;
	sf::View *view;
	sf::Vector2f size;
	sf::RectangleShape *background;

private:
	string name;
	sf::Texture *texture;
};

// menu scene
class MenuScene :public Scene {
public:
	MenuScene() : Scene() {
		Button * temp = new Button(sf::Color(0, 255, 255, 255), sf::Color::Blue, sf::Color(100, 255, 255, 255), "Play", sf::Vector2f(600, 200), sf::Vector2f(((gameObj->getSize().x - 600) / 2), ((gameObj->getSize().y - 200) / 2) + 150), 0);
		btns.push_back(temp);
		drawables.push_back(temp);
	}
	virtual void update() {
		sf::Vector2i mouseLoc = sf::Mouse::getPosition(*gameObj);
		bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		for (Button * btn : btns) {
			if (btn->checkMouse(mouseLoc, leftMouse)) {
				switch (btn->getId()) {
				case 0:
					//CurrentScene = new PlayScene(sf::Vector2f(4000, 2000), "./maps/racetrack2.png",new map("./maps/racetrack2.svg"));
					CurrentScene = new CarSelectScene();
					delete this;
					return;
				}
			}
		}
	}
	~MenuScene() {
		for (Button * btn : btns) {
			btn = nullptr;
		}
	}
private:
	std::vector<Button *> btns;
};

// car select scene
class CarSelectScene : public Scene {
public:
	CarSelectScene() : Scene() {
		ifstream carList;
		carList.open("./sprites/list.txt");
		vector<string> cars;
		string temp;
		while (!carList.eof()) {
			carList >> temp;
			cars.push_back(temp);
		}
		int counter = 0;
		for (string carName : cars) {
			string spriteString = "./sprites/" + carName + ".png";
			carPaths.push_back(spriteString);
			cout << "CAR : " << spriteString << endl;
			btns.push_back(new Button(spriteString, carName, sf::Vector2f(200, 200), 5.f, counter));
			counter++;
		}
		float spacex = 50.f;
		float spacey = 50.f;
		sf::Vector2f pos(200, 200);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < btns.size() / 2; j++) {
				btns[i*(btns.size() / 2) + j]->rect->setPosition(pos + sf::Vector2f(j*(spacex + btns[i]->rect->getGlobalBounds().width), i*(spacey + btns[i]->rect->getGlobalBounds().height)));
				cout << "car " << j << " , " << i << " : " << btns[i*(btns.size() / 2) + j]->rect->getPosition().x << " , " << btns[i*(btns.size() / 2) + j]->rect->getPosition().x << endl;
				btns[i*(btns.size() / 2) + j]->updateTextPos();
			}
		}
		for (Button * btn : btns) {
			drawables.push_back(btn);
		}
	}
	virtual void update() {
		sf::Vector2i mouseLoc = sf::Mouse::getPosition(*gameObj);
		bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		for (Button * btn : btns) {
			if (btn->checkMouse(mouseLoc, leftMouse)) {
				CurrentScene = new PlayScene(sf::Vector2f(4000, 2000), "./maps/racetrack2.png", new map("./maps/racetrack2.svg"), carPaths[btn->getId()]);
				delete this;
				return;
			}
		}
	}
	~CarSelectScene() {
		for (Button * btn : btns) {
			btn = nullptr;
		}
	}
private:
	std::vector<string> carPaths;
	std::vector<Button *> btns;
};

// play scene
typedef enum playstate {
	PLAYING = 0,
	PAUSE = 1,
	FINISH = 2,
	EXIT = 3
} PlayState;

class PlayScene : public Scene {
public:
	PlayScene(sf::Vector2f &size, string filepath, map *theMap, string carPath) : Scene(size, filepath)
	{
		font.loadFromFile("./fonts/slope-opera/SlopeOpera.otf");

		localPlayers.push_back(new LocalPlayer(theMap->startBox->getPosition(), carPath, "wasd", "P1"));
		//localPlayers.push_back( new LocalPlayer(theMap->startBox->getPosition(), carPath, "ijkl", "P2"));

		timetext = new sf::Text();
		laptext = new sf::Text();
		othertext = new sf::Text();

		timetext->setFont(font);
		laptext->setFont(font);
		othertext->setFont(font);

		timetext->setCharacterSize(50);
		laptext->setCharacterSize(50);
		othertext->setCharacterSize(50);

		lap = 1;
		totalLaps = 2;

		state = PLAYING;

		this->theMap = theMap;

		music = new sf::Music();
		if (music->openFromFile("./songs/blockrunner.wav")) {
			music->play();
		}

		for (Player * p : localPlayers) {
			p->nextCheckpoint = theMap->pStart;
			players.push_back(p);
		}

		hitHelper = new collisionHandler(theMap, players);
		view = new sf::View(sf::Vector2f(0, 0), (sf::Vector2f)gameObj->getSize());
		view->zoom(0.75);
		seconds = 0.f;

		pm = new PauseMenu(view, font);

		pauseBackground = new sf::RectangleShape(view->getSize()*3.f / 4.f);
		pauseBackground->setOrigin(view->getCenter());
		pauseBackground->setFillColor(sf::Color::Cyan);

		// remember that order matters! 
		// what's pushed first is drawn first
		drawables.push_back(background);
		drawables.push_back(theMap);
		drawables.push_back(timetext);
		drawables.push_back(laptext);
		drawables.push_back(othertext);

		for (Player * p : players) {
			drawables.push_back(p);
		}

		drawables.push_back(pm);
	}

	void update()
	{

		if (state == PLAYING) {
			pm->isRendered = false;
			int maxLap = 0;
			for (Player * p : players) {
				p->update();
				int l = (p->getCheckpointsHit() - 1) / theMap->numCheckpoints + 1;
				if (l > maxLap) {
					maxLap = l;
				}
			}
			lap = maxLap;

			// race is finished
			if (lap > totalLaps) {
				state = FINISH;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				state = PAUSE;
			}
		}
		else if (state == PAUSE || state == FINISH) {
			pm->isRendered = true;
			pm->resize();

			if (state == PAUSE) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					state = PLAYING;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
					state = EXIT;
				}
			}
			else {
				// new highscore??
				pm->message->setString("FINISH\n\nPress Q to Save and Quit");
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
					state = EXIT;
				}
			}
		}
		else if (state == EXIT) {
			//CurrentScene = new MenuScene;
			//delete this;
			// switch to main menu and delete this pupper
		}
	}

	void updatePhysics(float dt)
	{
		if (state == PLAYING) {
			seconds += dt;

			char buffer[7];
			snprintf(buffer, 7, "%03.3f", seconds);
			timetext->setString(buffer);


			snprintf(buffer, 7, "Lap %d", lap);
			laptext->setString(buffer);

			timetext->setPosition(view->getCenter() - view->getSize() / 2.f);
			laptext->setPosition(timetext->getPosition() + sf::Vector2f(300, 0));

			hitHelper->handleCollisions();
			sf::Vector2f sumPos;
			for (Player * p : players) {
				p->updatePhysics(dt);
				// center on the car(s)
				sumPos += p->getCar()->getPosition();
			}
			view->setCenter(sumPos / (float)players.size());
		}
		else if (state == PAUSE) {
			cout << "paused" << endl;
		}
		else if (state == FINISH) {
			for (Player * p : players) {
				p->getCar()->updatePhysics(dt);
				// let them all coast with no control
			}
			laptext->setString("Finish");
		}
	}

	virtual ~PlayScene() {
		delete hitHelper;
		delete theMap;
		delete timetext;
		delete laptext;
		delete othertext;
		delete pauseBackground;
		delete pm;

		music->stop();
		delete music;
	}

private:
	collisionHandler * hitHelper;
	vector<LocalPlayer *>localPlayers;
	vector<Player *> players;
	map *theMap;
	sf::Font font;
	sf::Text *timetext;
	sf::Text *laptext;
	sf::Text *othertext;
	sf::RectangleShape *pauseBackground;
	float seconds;
	int lap;
	int totalLaps;
	PlayState state;

	// pause menu
	PauseMenu *pm;

	// music
	sf::Music *music;
};

// splash scene
class SplashScene : public Scene {
protected:

public:
	virtual void update() {
		fCount++;
		if (fCount >= (15 * 3)) {
			text->setScale(sf::Vector2f(1 - ((float)(fCount - 45) / 45.0f), 1 - ((float)(fCount - 45) / 45.0f)));
		}
		if (fCount == (30 * 3)) {
			CurrentScene = new MenuScene;
			delete this;
		}

	}
	SplashScene() : Scene() {
		fCount = 0;
		font.loadFromFile("./fonts/slope-opera/SlopeOpera.otf");
		text = new sf::Text();
		text->setFont(font);
		text->setCharacterSize(50);
		text->setString("Splash Screen!");
		text->setPosition(sf::Vector2f(200, 200));

		// remember that order matters! 
		// what's pushed first is drawn first
		drawables.push_back(text);
	}
private:
	int fCount;
	sf::Font font;
	sf::Text *text;
};



#endif