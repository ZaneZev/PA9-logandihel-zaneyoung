#include "LocalPlayer.h"

// override
void LocalPlayer::update() {
	updateKeyboard();
	// send server updates if applicable
}

void LocalPlayer::updatePhysics(float dt) {
	//car->addForce(); ...

	if (leftIsPressed) {
		car->addForce(sf::Vector2f(-1000, 0), sf::Vector2f(15, 15));
	}
	if (rightIsPressed) {
		car->addForce(sf::Vector2f(1000, 0), sf::Vector2f(-15, 15));
	}
	if (upIsPressed) {
		car->addForce(sf::Vector2f(0, -1000));
	}
	if (downIsPressed) {
		car->addForce(sf::Vector2f(0, 1000));
	}

	car->updatePhysics(dt);
}

void LocalPlayer::updateKeyboard() {
	upIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	downIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	leftIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	rightIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	shiftIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
}

bool LocalPlayer::getLeftPressed() { return leftIsPressed; }
bool LocalPlayer::getRightPressed() { return rightIsPressed; }
bool LocalPlayer::getUpPressed() { return upIsPressed; }
bool LocalPlayer::getDownPressed() { return downIsPressed; }
bool LocalPlayer::getShiftPressed() { return shiftIsPressed; }