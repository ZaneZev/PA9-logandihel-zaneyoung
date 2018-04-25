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
	CarSelectScene(vector<string> PcarPaths,int numPlayers) :Scene(){
		this->PcarPaths = PcarPaths;
		ifstream carList;
		carList.open("./sprites/list.txt");
		vector<string> cars;
		string temp;
		while (!carList.eof()) {
			carList >> temp;
			cars.push_back(temp);
		}
		int counter = 0;
		for (string carName : cars) {
			string spriteString = "./sprites/" + carName + ".png";
			carPaths.push_back(spriteString);
			cout << "CAR : " << spriteString << endl;
			btns.push_back(new Button(spriteString, carName, sf::Vector2f(200, 200), 5.f, counter));
			counter++;
		}
		float spacex = 50.f;
		float spacey = 50.f;
		sf::Vector2f pos(200, 200);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < btns.size() / 2; j++) {
				btns[i*(btns.size() / 2) + j]->rect->setPosition(pos + sf::Vector2f(j*(spacex + btns[i]->rect->getGlobalBounds().width), i*(spacey + btns[i]->rect->getGlobalBounds().height)));
				cout << "car " << j << " , " << i << " : " << btns[i*(btns.size() / 2) + j]->rect->getPosition().x << " , " << btns[i*(btns.size() / 2) + j]->rect->getPosition().x << endl;
				btns[i*(btns.size() / 2) + j]->updateTextPos();
			}
		}
		for (Button * btn : btns) {
			drawables.push_back(btn);
		}
		this->numPlayers--;
	}
	CarSelectScene(int numPlayers) :Scene() {
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
			carPaths.push_back(spriteString);
			cout << "CAR : " << spriteString << endl;
			btns.push_back(new Button(spriteString, carName,sf::Vector2f(200,200),5.f, counter));
			counter++;
		}
		float spacex = 50.f;
		float spacey = 50.f;
		sf::Vector2f pos(200, 200);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < btns.size() / 2; j++) {
				btns[i*(btns.size() / 2) + j]->rect->setPosition(pos + sf::Vector2f(j*(spacex + btns[i]->rect->getGlobalBounds().width) , i*(spacey + btns[i]->rect->getGlobalBounds().height)));
				cout << "car " << j << " , " << i << " : " << btns[i*(btns.size() / 2) + j]->rect->getPosition().x << " , " << btns[i*(btns.size() / 2) + j]->rect->getPosition().x << endl;
				btns[i*(btns.size() / 2) + j]->updateTextPos();
			}
		}
		for (Button * btn : btns) {
			drawables.push_back(btn);
		}
		this->numPlayers--;
	}
	virtual void update() {
		sf::Vector2i mouseLoc = sf::Mouse::getPosition(*gameObj);
		bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		for (Button * btn : btns) {
			if (btn->checkMouse(mouseLoc, leftMouse)) {
					PcarPaths.push_back(carPaths[btn->getId()]);
				if (numPlayers == 0) {
					CurrentScene = new PlayScene(sf::Vector2f(4000, 2000), "./maps/racetrack2.png", new map("./maps/racetrack2.svg"), PcarPaths);
					delete this;
				}
				else {
					CurrentScene = new CarSelectScene(PcarPaths, numPlayers);
					delete this;
				}
				return;
			}
		}
	}
	~CarSelectScene() {
		for (Button * btn : btns) {
			btn = nullptr;
		}
	}
private:
	vector<string> PcarPaths;
	int numPlayers;
	std::vector<string> carPaths;
	std::vector<Button *> btns;
};