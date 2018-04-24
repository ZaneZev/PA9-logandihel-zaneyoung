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
		timetext = new sf::Text();
		laptext = new sf::Text();
		othertext = new sf::Text();

		timetext->setFont(font);
		laptext->setFont(font);
		othertext->setFont(font);

		timetext->setCharacterSize(50);
		laptext->setCharacterSize(30);
		othertext->setCharacterSize(30);

		this->theMap = theMap;
		
		
		localPlayers.push_back( new LocalPlayer(theMap->startBox->getPosition(),"wasd","P1"));
	//	localPlayers.push_back( new LocalPlayer(theMap->startBox->getPosition() + sf::Vector2f(32, 0), "ijkl", "P2"));
		for (Player * p : localPlayers) {
			p->nextCheckpoint = theMap->pStart;
			players.push_back(p);
		}
		hitHelper = new collisionHandler(theMap, players);
		view = new sf::View(sf::Vector2f(0,0), (sf::Vector2f)gameObj->getSize());
		view->zoom(0.75);
		seconds = 0.f;
		lap = 1;
		//sidebar = new RectangleShape();

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
		
	}

	void update()
	{
		for (Player * p : players) {
			p->update();
			lap = (p->getCheckpointsHit()-1) / theMap->numCheckpoints + 1;
		}
	}

	void updatePhysics(float dt)
	{

		seconds += dt;

		char buffer[7];
		snprintf(buffer, 7, "%03.3f", seconds);
		timetext->setString(buffer);

		snprintf(buffer, 7, "Lap %d", lap);
		laptext->setString(buffer);

		timetext->setPosition(view->getCenter() - view->getSize()/2.f);
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

private:
	collisionHandler * hitHelper;
	vector<LocalPlayer *>localPlayers;
	vector<Player *> players;
	map *theMap;
	sf::Font font;
	sf::Text *timetext;
	sf::Text *laptext;
	sf::Text *othertext;
	sf::RectangleShape *sidebar;
	float seconds;
	int lap;
};