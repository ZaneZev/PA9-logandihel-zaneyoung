#include "Player.h"

Player::~Player() {}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(*car, states);
	target.draw(name, states);
}

void Player::update(float dt) {
	name.setPosition(car->getPosition());
	car->update(dt);
}

void Player::nudgeLeft() {
	//car.acceleration += sf::Vector2f(-1, 0);
}
void Player::nudgeRight() {
	//car.acceleration += sf::Vector2f(1, 0);
}
void Player::nudgeUp() {
	car->addForce(sf::Vector2f(0, -1000));
}
void Player::nudgeDown() {
	car->addForce(sf::Vector2f(0, 1000));
}
void Player::stop() {}
void Player::rotateLeft() {
	car->addForce(sf::Vector2f(-1000, 0), sf::Vector2f(2, 20));
	
}
void Player::rotateRight() {
	car->addForce(sf::Vector2f(1000, 0), sf::Vector2f(2, -20));

}