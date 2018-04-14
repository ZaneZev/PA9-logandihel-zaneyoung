#pragma once
#include "Scene.h"
#include "SplashScreen.h"
#include "PlayScene.h"
#include "Game.h"

extern Scene * CurrentScene;
class SplashScene : public Scene {
protected:
	
public:
	virtual void update() {
		//cout << fCount << endl;
		fCount++;
		if (fCount >= (15 * 3)) {
			text->setScale(sf::Vector2f(1 - ((float)(fCount - 45) / 45.0f), 1 - ((float)(fCount - 45) / 45.0f)));
		}
		if (fCount == (30*3)) {
			CurrentScene = new PlayScene(sf::Vector2f(470*5, 280*5), "./sprites/racetrack1.png");
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