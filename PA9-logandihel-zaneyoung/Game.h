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
#include "Scene.h"
#include "SplashScene.h"
#include "PlayScene.h"

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

#define NUM_SCENES 2
typedef enum scenestate {
	SPLASH_SCENE,
	PLAY_SCENE
} SceneState;

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

		scenes[SPLASH_SCENE] = new SplashScene();
		scenes[PLAY_SCENE] = new PlayScene();
		currentSceneState = PLAY_SCENE;
	}
	~Game();
	void start();

	// returns at ENUM to which scene we're in
	SceneState getCurrentSceneState();

	// allows us to change the scene being updated and rendered
	void setCurrentSceneState(SceneState state);

private:
	int targetFPS;
	int width;
	int height;
	string title;
	SceneState currentSceneState;
	Scene* scenes[NUM_SCENES];
	
	void updatePhysics(float dt);
	void update();
	void processEvents();
	void render();
	void loop();
};