#include "Car.h"

void Car::setAcceleration(sf::Vector2f &acceleration) {
	this->acceleration = acceleration;
}

void Car::setVelocity(sf::Vector2f &velocity) {
	this->velocity = velocity;
}

void Car::setPosition(sf::Vector2f &position) {
	this->position = position;
}

sf::Vector2f Car::getAcceleration() {
	return acceleration;
}

sf::Vector2f Car::getVelocity() {
	return velocity;
}

sf::Vector2f Car::getPosition() {
	return position;
}
#include <iostream>
// Override
void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const {

	// define a 100x100 square, red, with a 10x10 texture mapped on it
	//std::cout << rect.getOrigin().x << ", " << rect.getOrigin().y << std::endl;

	sf::Vertex accelerationVerticies[] =
	{
		sf::Vertex(sf::Vector2f(0,0), sf::Color::Red),
		sf::Vertex(acceleration, sf::Color::Red)
	};

	sf::Vertex velocityVerticies[] =
	{
		sf::Vertex(sf::Vector2f(0,0), sf::Color::Blue),
		sf::Vertex(velocity, sf::Color::Blue)
	};

	// draw it
	target.draw(rect, states);
	target.draw(accelerationVerticies, 2, sf::Lines);
	target.draw(velocityVerticies, 2, sf::Lines);
}

// update the position, velocity, and acceleration
void Car::update() {
	// TODO add more physics like friction, weight, etc.
	velocity += acceleration;
	std::cout << position.x << ", " << position.y << std::endl;
	position += velocity;

	// TODO hard coded friction forces
	acceleration.x = 0;
	acceleration.y = 0;

	rect.setPosition(position);
}