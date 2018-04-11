#include "Player.h"

Player::~Player() {}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(car, states);
	target.draw(name, states);
}

void Player::update() {
	name.setPosition(car.getPosition());
	car.update();
}

void Player::nudgeLeft() {
	car.acceleration += sf::Vector2f(-1, 0);
}
void Player::nudgeRight() {
	car.acceleration += sf::Vector2f(1, 0);
}
void Player::nudgeUp() {
	float dx = 0.0, dy = 0.0, c = 0.4;
	dy = c * cos(car.rect.getRotation() * PI / 180.0);
	dx = c * sin(car.rect.getRotation() * PI / 180.0);

	// in direction of velocity
	car.acceleration = sf::Vector2f(dx, -dy);
}
void Player::nudgeDown() {
	float dx = 0.0, dy = 0.0, c = 0.4;
	dy = c * cos(car.rect.getRotation() * PI / 180.0);
	dx = c * sin(car.rect.getRotation() * PI / 180.0);

	// in opposite direction of velocity
	car.acceleration = sf::Vector2f(-dx, dy);
}
void Player::stop() {
	car.acceleration = sf::Vector2f(0, 0);
	car.velocity = sf::Vector2f(0, 0);
}
void Player::rotateLeft() {
	car.rect.setRotation(car.rect.getRotation() - 5);
	
	float dx = 0.0, dy = 0.0, c = 0.4;
	dy = c * cos((car.rect.getRotation() - 90) * PI / 180.0);
	dx = c * sin((car.rect.getRotation() - 90) * PI / 180.0);

	// in perpendicular right of velocity
	car.acceleration = sf::Vector2f(dx, -dy);
}
void Player::rotateRight() {
	car.rect.setRotation(car.rect.getRotation() + 5);

	float dx = 0.0, dy = 0.0, c = 0.4;
	dy = c * cos((car.rect.getRotation() + 90) * PI / 180.0);
	dx = c * sin((car.rect.getRotation() + 90) * PI / 180.0);

	// in perpendicular right of velocity
	car.acceleration = sf::Vector2f(dx, -dy);
}