#pragma once
#include "PlayScene.h"
#include "SplashScene.h"
#include "Scene.h"
#include "MenuScene.h"
#include "Game.h"
#include "PlayScene.h"
#include "SplashScene.h"
#include "Scene.h"
#include "MenuScene.h"

extern Scene * CurrentScene;
class SplashScene : public Scene {
protected:
	
public:
	virtual void update() {
		cout << fCount << endl;
		fCount++;
		if (fCount >= (15 * 3)) {
			text->setScale(sf::Vector2f(1 - ((float)(fCount - 45) / 45.0f), 1 - ((float)(fCount - 45) / 45.0f)));
		}
		if (fCount == (30*3)) {
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