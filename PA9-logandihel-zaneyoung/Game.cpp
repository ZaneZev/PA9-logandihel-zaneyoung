#include "Game.h"

/*
Public Functions
*/
Game::~Game() {}

// this code runs once
void Game::start() {

	SocketManager sm;



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
	systemtime.restart();
	while (this->isOpen())
	{
		long dtMicro = systemtime.getElapsedTime().asMicroseconds();
		// update calls
		if (dtMicro >= dtTarget) {
			microseconds += dtMicro;
			++updates;
			systemtime.restart();
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
		render();
		++frames;
	}
}

void Game::update() {
	processEvents();
}

void Game::processEvents() {
	sf::Event event;
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			close(); // program over
		}
		else if (event.type == sf::Event::KeyPressed) {
			// TODO: process user input
		}
	}
}

void Game::render() {
	clear();
	// TODO: all rendering goes here
	display();
}