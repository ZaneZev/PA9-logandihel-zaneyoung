#pragma once
#include "Button.h"
#include "testing.h"
#include "Scene.h"
#include "Game.h"
#include "map.h"

extern Scene * CurrentScene;
extern sf::RenderWindow * gameObj;

class MenuScene :public Scene {
public:
	MenuScene() : Scene() {
		Button * temp = new Button(sf::Color::Blue, sf::Color(100, 100, 100, 255), sf::Color(215, 215, 215, 255), "Play", sf::Vector2f((gameObj->getSize().x/2)-50, (gameObj->getSize().y / 2) - 30),sf::Vector2f(100,60),0);
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
					CurrentScene = new PlayScene(sf::Vector2f(470 * 5, 280 * 5), "./sprites/racetrack1.png",new map("./maps/test.svg"));
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