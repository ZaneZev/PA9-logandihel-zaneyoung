#pragma once
#include "Scene.h"
#include "LocalPlayer.h"
#include "map.h"
#include "collisionHandler.h"
#include <vector>
extern sf::RenderWindow * gameObj;

class PlayScene : public Scene {
public:
	PlayScene(sf::Vector2f &size, string filepath , map *theMap) : Scene(size, filepath) 
	{
		font.loadFromFile("./fonts/slope-opera/SlopeOpera.otf");
		text = new sf::Text();
		text->setFont(font);
		text->setCharacterSize(50);
		text->setString("Play Scene");
		text->setPosition(sf::Vector2f(200,200));
		localPlayers.push_back( new LocalPlayer(theMap->startBox->getPosition(),theMap,"wasd","P1"));
		// localPlayers.push_back( new LocalPlayer(theMap->startBox->getPosition() + sf::Vector2f(32,0), "ijkl", "P2"));
		for (Player * p : localPlayers) {
			players.push_back(p);
		}
		hitHelper = new collisionHandler(theMap, players);
		view = new sf::View(sf::Vector2f(0,0), (sf::Vector2f)gameObj->getSize());
		view->zoom(0.75);

		// remember that order matters! 
		// what's pushed first is drawn first
		drawables.push_back(background);
		drawables.push_back(theMap);
		drawables.push_back(text);
		for (Player * p : players) {
			drawables.push_back(p);
    }
		drawables.push_back(theMap);
	}

	void update()
	{
		sf::Vector2f sumPos;
		for (Player * p : players) {
			p->update();
			sumPos += p->getCar()->getPosition();
		}

		sf::Vector2f avPos = sumPos / (float)players.size();
		view->setCenter(avPos);

		/*sf::Vector2f pos = players.at(0)->getCar()->getPosition() - avPos;
		float distanceSq = pos.x * pos.x + pos.y * pos.y;
		float rSq = view->getSize().y * view->getSize().y;

		view->zoom(distanceSq / (rSq));*/
		//view->set
	}

	void updatePhysics(float dt)
	{
		hitHelper->handleCollisions();
		sf::Vector2f sumPos;
		for (Player * p : players) {
			p->updatePhysics(dt);
			sumPos += p->getCar()->getPosition();
		}
	
		sf::Vector2f avPos = sumPos / (float)players.size();
		view->setCenter(avPos);
	}

private:
	collisionHandler * hitHelper;
	vector<LocalPlayer *>localPlayers;
	vector<Player *> players;
	sf::Font font;
	sf::Text *text;
};