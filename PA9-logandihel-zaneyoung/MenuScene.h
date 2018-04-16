#pragma once
#include "Button.h"
#include "testing.h"
#include "Scene.h"
#include "Game.h"

extern Scene * CurrentScene;
extern sf::RenderWindow * gameObj;

class MenuScene :public Scene {
public:
	MenuScene() : Scene() {
		Button * temp = new Button("Play", 0);
		btns.push_back(temp);
		drawables.push_back(temp);
	}
	virtual void update() {
		sf::Vector2i mouseLoc = sf::Mouse::getPosition(*gameObj);
		bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		for (Button * btn : btns){
			if (btn->checkMouse(mouseLoc, leftMouse)) {
				switch (btn->getId()) {
				case 0:
					CurrentScene = new PlayScene(sf::Vector2f(470 * 5, 280 * 5), "./sprites/racetrack1.png");
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