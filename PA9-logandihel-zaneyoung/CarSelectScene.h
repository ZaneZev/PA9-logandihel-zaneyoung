#pragma once
#include "Button.h"
#include "testing.h"
#include "Scene.h"
#include "Game.h"
#include "map.h"

extern Scene * CurrentScene;
extern sf::RenderWindow * gameObj;

class CarSelectScene :public Scene {
public:
	CarSelectScene() :Scene() {
		ifstream carList;
		carList.open("./sprites/list.txt");
		vector<string> cars;
		string temp;
		while (!carList.eof()){
			carList >> temp;
			cars.push_back(temp);
		}
		int counter = 0;
		for (string carName : cars) {
			string spriteString = "./sprites/" + carName + ".png";
			btns.pop_back(new Button(spriteString, carName,sf::Vector2f(0,0),1.f, counter));
			counter++;
		}
	}
	virtual void update() {
		sf::Vector2i mouseLoc = sf::Mouse::getPosition(*gameObj);
		bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		for (Button * btn : btns) {
			if (btn->checkMouse(mouseLoc, leftMouse)) {
				switch (btn->getId()) {
				case 0:
					CurrentScene = new PlayScene(sf::Vector2f(4000, 2000), "./maps/racetrack2.png", new map("./maps/racetrack2.svg"));
					delete this;
					return;
				}
			}
		}
	}
	~CarSelectScene() {
		for (Button * btn : btns) {
			btn = nullptr;
		}
	}
private:
	std::vector<Button *> btns;
};