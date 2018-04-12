#include "LocalPlayer.h"

// override
void LocalPlayer::update() {
	updateKeyboard();
	// send server updates if applicable
}

void LocalPlayer::updatePhysics(float dt) {

	if (rightIsPressed) {
		car->addForce(sf::Vector2f(-1000, 0), sf::Vector2f(50, 50));
	}
	if (leftIsPressed) {
		car->addForce(sf::Vector2f(1000, 0), sf::Vector2f(-50, 50));
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