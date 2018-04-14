#include "LocalPlayer.h"

// override
void LocalPlayer::update() {
	updateKeyboard();
	// send server updates if applicable
}

void LocalPlayer::updatePhysics(float dt) {

	if (upIsPressed) {
		car->driveForward();
	}
	else if (downIsPressed) {
		car->driveBackward();
	}

	if (leftIsPressed) {
		car->turnLeft();
	}
	else if (rightIsPressed) {
		car->turnRight();
	}
	else {
		// car->turnLeft(0);
	}

	if (shiftIsPressed) {
		car->start_drift();
	}
	else {
		car->stop_drift();
	}


	car->updatePhysics(dt);
}

void LocalPlayer::updateKeyboard() {
	upIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	downIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	leftIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	rightIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	shiftIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
}

bool LocalPlayer::getLeftPressed() { return leftIsPressed; }
bool LocalPlayer::getRightPressed() { return rightIsPressed; }
bool LocalPlayer::getUpPressed() { return upIsPressed; }
bool LocalPlayer::getDownPressed() { return downIsPressed; }
bool LocalPlayer::getShiftPressed() { return shiftIsPressed; }