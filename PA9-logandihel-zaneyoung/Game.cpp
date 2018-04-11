#include "Game.h"

/*
Public Functions
*/
Game::~Game() {
	delete sm;
}

// this code runs once
void Game::start() {

	//drawables.push_back(new Car(30.f, 60.f));
	players.push_back(new Player("Racecar"));

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
	systemtime.restart();
	while (this->isOpen())
	{
		long dtMicro = systemtime.getElapsedTime().asMicroseconds();
		// update calls
		if (dtMicro >= dtTarget) {
			microseconds += dtMicro;
			++updates;
			systemtime.restart();
			update(dtMicro/1E6);
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

void Game::update(float dt) {
	processEvents();

	for (int i = 0; i < players.size(); i++) {
		(dynamic_cast<Player *>(players.at(0)))->update(dt);
	}
}

void Game::processEvents() {
	sf::Event event;
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			close(); // program over
		}
	}


	// handle user input seperately
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		// nudge player up
		cout << "up" << endl;
		(dynamic_cast<Player *>(players.at(0)))->nudgeUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		// nudge player down
		cout << "down" << endl;
		(dynamic_cast<Player *>(players.at(0)))->nudgeDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		// nudge player left
		cout << "left" << endl;
		(dynamic_cast<Player *>(players.at(0)))->rotateLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		// nudge player right
		cout << "right" << endl;
		(dynamic_cast<Player *>(players.at(0)))->rotateRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		cout << "Lshift" << endl;
		(dynamic_cast<Player *>(players.at(0)))->stop();
	}
}

void Game::render() {
	clear();
	// TODO: all rendering goes here
	for (int i = 0; i < players.size(); i++) {
		//draw(level.at(loadedlevelindex));
		draw(*players.at(i));
	}
	display();
}