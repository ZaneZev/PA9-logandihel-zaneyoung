#pragma once
#include "Scene.h"
#include "LocalPlayer.h"
#include "map.h"
#include "collisionHandler.h"
#include <vector>
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
		lp = new LocalPlayer();
		hitHelper = new collisionHandler(theMap, { lp });
		view = new sf::View();
		//view->zoom(0.25);

		// remember that order matters! 
		// what's pushed first is drawn first
		drawables.push_back(background);
		drawables.push_back(text);
		drawables.push_back(lp);
		drawables.push_back(theMap);
		//drawables.push_back(background);
	}

	void update()
	{
		lp->update();
	}

	void updatePhysics(float dt)
	{
		lp->updatePhysics(dt);
		// center on the car(s)
		view->setCenter(lp->getCar()->getPosition());
		hitHelper->handleCollisions();
	}

private:
	collisionHandler * hitHelper;
	LocalPlayer *lp;
	sf::Font font;
	sf::Text *text;
};