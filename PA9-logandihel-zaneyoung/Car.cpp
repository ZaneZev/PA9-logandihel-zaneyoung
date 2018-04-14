#include "Car.h"

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(*carBody, states);
	target.draw(*chasis, states);
	
	// draw anything else that's relevant
}

void Car::updatePhysics(float dt) {
	chasis->updatePhysics(dt);

	carBody->setPosition(chasis->getPosition());
	carBody->setRotation(chasis->getRotation());

}

// TODO fill these in correctly
void Car::driveForward() {
	double a = chasis->getRotation() * PI / 180.f;
	//chasis->addForce(500.f * sf::Vector2f(sin(a), -cos(a)));
	chasis->addForce(sf::Vector2f(5E6, 0.f));
}

void Car::turnLeft(float angle) {
	//chasis->addForce(sf::Vector2f(1000, 0), sf::Vector2f(-50, 50));
	chasis->addTorque(-2E4);
}

void Car::turnRight(float angle) {
	//chasis->addForce(sf::Vector2f(-1000, 0), sf::Vector2f(50, 50));
	chasis->addTorque(2E4);
}

void Car::turbo(float turboPower) {

}

void Car::brake(float brakeTorque) {

}

void Car::driveBackward() {
	//double a = chasis->getRotation() * PI / 180.f;
	chasis->addForce(sf::Vector2f(-5E6, 0.f));
}

void Car::start_drift() {
	// not sure what to do
}

void Car::stop_drift() {
	// not sure what to do
}