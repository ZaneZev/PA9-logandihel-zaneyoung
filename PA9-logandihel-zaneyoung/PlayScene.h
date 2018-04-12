#pragma once
#include "Scene.h"
#include "LocalPlayer.h"

class PlayScene : public Scene {
public:
	PlayScene() : Scene() 
	{
		font.loadFromFile("./fonts/slope-opera/SlopeOpera.otf");
		text = new sf::Text();
		text->setFont(font);
		text->setCharacterSize(50);
		text->setString("Play Scene");
		text->setColor(sf::Color::White);
		text->setPosition(sf::Vector2f(200,200));
		
		lp = new LocalPlayer();

		// remember that order matters! 
		// what's pushed first is drawn first
		drawables.push_back(text);
		drawables.push_back(lp);
	}

	void update()
	{
		lp->update();
	}

	void updatePhysics(float dt)
	{
		lp->updatePhysics(dt);
	}

private:
	LocalPlayer *lp;
	sf::Font font;
	sf::Text *text;
	
};