#pragma once
#include "testing.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <iostream>
#include "SocketManager.h"
#include <vector>
#include "Car.h"
#include "LocalPlayer.h"

/*
DEBUG MODE
COMMENT OUT TO PUT
INTO PRODUCTION MODE
*/
#define DEBUG

using std::string;
using std::cout;
using std::endl;
using std::vector;

/*
Game.h
Inherits from the sf::RenderWindow class
Functions as the main loop for the game
Main game code will go inside the update() and render() methods
*/

class Game : public sf::RenderWindow {
public:
	Game::Game(string title="", int width=800, int height=600, int fps=30) :
		sf::RenderWindow(sf::VideoMode(width, height), title) {
		this->targetFPS = fps;
		this->title = title;
		this->sm = nullptr;
	}
	~Game();

	void start();

private:
	SocketManager *sm;
	int targetFPS;
	int width;
	int height;
	string title;
	vector<sf::Drawable *> players;
	
	void updatePhysics(float dt);
	void update();
	void processEvents();
	void render();
	void loop();
};