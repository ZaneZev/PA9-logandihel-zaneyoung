#include "Game.h"

/*
Public Functions
*/
Game::~Game() {}

// this code runs once
void Game::start() {

	/*try {
		sm = new SocketManager();
	}
	catch (std::exception &e) {
		cout << "Could not connect to server in Game::start()" << endl;
	}*/
	
	loop();
}

/*
Private Functions
*/
void Game::loop() {
	// main game loop
	long dtTarget = 1E6 / targetFPS; // ~30 updates per second
	int frames = 0, updates = 0;
	long microseconds = 0;
	sf::Clock systemtime;
	systemtime.restart().asMicroseconds();
	long sumdt = 0;

	while (this->isOpen()) {

		long dtMicro = systemtime.getElapsedTime().asMicroseconds();
		systemtime.restart();
		sumdt += dtMicro;

		// update calls
		if (sumdt >= dtTarget) {
			microseconds += sumdt;
			++updates;
			sumdt = 0;
			update();
		}
	
		// debug only
#ifdef DEBUG
		if (microseconds >= 1E6) {
			setTitle(title +
				" FPS: " + std::to_string(frames) + 
				" UPS: " + std::to_string(updates));
			frames = 0;
			updates = 0;
			microseconds -= 1E6;
		}
#endif

		// render screen as fast as possible
		updatePhysics(dtMicro/1E6);
		render();
		++frames;
	}
}

void Game::update() {
	processEvents();
	scenes[currentSceneState]->update();
}

void Game::updatePhysics(float dt) {
	scenes[currentSceneState]->updatePhysics(dt);
}

void Game::processEvents() {
	sf::Event event;
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			close(); // program over
		}
	}
}

void Game::render() {
	clear();
	// TODO: all rendering goes here
	draw(*scenes[currentSceneState]);
	display();
}

SceneState Game::getCurrentSceneState() {
	return currentSceneState;
}

void Game::setCurrentSceneState(SceneState state) {
	currentSceneState = state;
}