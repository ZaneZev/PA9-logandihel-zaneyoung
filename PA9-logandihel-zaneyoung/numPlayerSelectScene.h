#pragma once
#include "Button.h"
#include "testing.h"
#include "Scene.h"
#include "Game.h"
#include "map.h"
#include "CarSelectScene.h"
#include "PlayScene.h"

extern Scene * CurrentScene;
extern sf::RenderWindow * gameObj;

class numPlayerSelectScene :public Scene {
public:
	numPlayerSelectScene() : Scene() {
		for (int i = 0; i < 4; i++) {
			char tempstr[10];
			snprintf(tempstr, 10, "%d Players", 1 + i);
			Button * temp = new Button(sf::Color(0, 255, 255, 255), sf::Color::Blue, sf::Color(100, 255, 255, 255), tempstr, sf::Vector2f(((gameObj->getSize().x - 600) / 2), ((gameObj->getSize().y - 400) / 2) + (150*i)), sf::Vector2f(600, 100), i+1);
			btns.push_back(temp);
			drawables.push_back(temp);
		}
	}
	virtual void update() {
		sf::Vector2i mouseLoc = sf::Mouse::getPosition(*gameObj);
		bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		for (Button * btn : btns) {
			if (btn->checkMouse(mouseLoc, leftMouse)) {
				CurrentScene = new CarSelectScene(btn->getId());
				delete this;
				return;
			}
		}
	}
	~numPlayerSelectScene() {
		for (Button * btn : btns) {
			btn = nullptr;
		}
	}
private:
	std::vector<Button *> btns;
};