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
#include "PlayScene.h"
#include "SplashScene.h"
#include "Scene.h"
#include "MenuScene.h"

/*z
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

	Game(string title="", int width=1000, int height=1000, int fps=30) :
		sf::RenderWindow(sf::VideoMode(width, height), title) {
		this->targetFPS = fps;
		this->title = title;
		CurrentScene = new SplashScene;
		justResized = false;
	}
	~Game();
	void start();

private:
	int targetFPS;
	int width;
	int height;
	string title;
	bool justResized;
	
	void updatePhysics(float dt);
	void update();
	void processEvents();
	void render();
	void loop();
};