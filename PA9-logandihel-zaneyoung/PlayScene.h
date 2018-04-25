#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "Scene.h"
#include "LocalPlayer.h"
#include "map.h"
#include "collisionHandler.h"
#include <SFML\Audio.hpp>
#include <vector>
#include "PauseMenu.h"
 
extern sf::RenderWindow * gameObj;
extern Scene * CurrentScene;

typedef enum playstate {
	PLAYING = 0,
	PAUSE = 1,
	FINISH = 2,
	EXIT = 3
} PlayState;

class PlayScene : public Scene {
public:
	PlayScene(sf::Vector2f &size, string filepath , map *theMap , vector<string> carPaths) : Scene(size, filepath) 
	{
		sf::Vector2f offset(24, 0);
		font.loadFromFile("./fonts/slope-opera/SlopeOpera.otf");
		for (int i = 0; i < carPaths.size(); i++) {
			switch (i)
			{
			case 0:
				localPlayers.push_back(new LocalPlayer(theMap->startBox->getPosition()+((float)i*offset), carPaths[i], "wasd", "P1"));
				break;
			case 1:
				localPlayers.push_back(new LocalPlayer(theMap->startBox->getPosition()+ ((float)i*offset), carPaths[i], "ijkl", "P2"));
				break;
			case 2:
				localPlayers.push_back(new LocalPlayer(theMap->startBox->getPosition()+ ((float)i*offset), carPaths[i], "tfgh", "P3"));
				break;
			case 3:
				localPlayers.push_back(new LocalPlayer(theMap->startBox->getPosition()+ ((float)i*offset), carPaths[i], "=[]\\", "P4"));
				break;
			default:
				break;
			}
		}
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
			cout << "p" << endl;
		}
    
		hitHelper = new collisionHandler(theMap, players);
		view = new sf::View(sf::Vector2f(0,0), (sf::Vector2f)gameObj->getSize());
		view->zoom(0.75);
		seconds = 0.f;

		pm = new PauseMenu(view, font);

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
			// save high score
			// display high score
			// exit the program
			exit(1);
			// cry
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
	float seconds;
	int lap;
	int totalLaps;
	PlayState state;

	// pause menu
	PauseMenu *pm;

	// music
	sf::Music *music;
};

#endif