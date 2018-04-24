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
		text->setOutlineColor(sf::Color::Black);
		//sidebar = new RectangleShape();

		// remember that order matters! 
		// what's pushed first is drawn first
		drawables.push_back(background);
		drawables.push_back(theMap);
		drawables.push_back(text);
		for (Player * p : players) {
			drawables.push_back(p);
		}
		
	}

	void update()
	{
		for(Player * p:players)
			p->update();
	}

	void updatePhysics(float dt)
	{

		seconds += dt;
		text->setString(std::to_string(seconds));
		text->setPosition(view->getCenter() + sf::Vector2f(view->getSize().x/6.f, -view->getSize().y/2.f+50));

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
	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *sidebar;
	float seconds;
};