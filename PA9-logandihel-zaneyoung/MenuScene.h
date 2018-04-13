#pragma once
#include "Button.h"
#include "testing.h"
#include "Scene.h"
#include "Game.h"
extern Scene * CurrentScene;
class MenuScene :public Scene {
public:
	MenuScene() : Scene() {
		Button * temp = new Button("Play", 0);
		btns.push_back(temp);
		drawables.push_back(temp);
		temp->addToDraws(drawables);
	}
	virtual void update() {
		sf::Vector2i mouseLoc = sf::Mouse::getPosition();
		bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		for (Button * btn : btns){
			if (btn->checkMouse(mouseLoc, leftMouse)) {
				switch (btn->getId()) {
				case 0:
					CurrentScene = new PlayScene;
					delete this;
				}
			}
		}
	}
	~MenuScene() {
		for (Button * btn : btns) {
			delete btn;
		}
	}
private:
	std::vector<Button *> btns;
};