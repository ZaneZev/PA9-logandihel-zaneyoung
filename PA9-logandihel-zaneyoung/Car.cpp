#include "Car.h"

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(*chasis, states);
	// draw anything else that's relevant
}

void Car::updatePhysics(float dt) {
	chasis->updatePhysics(dt);

	for (int i = 0; i < 4; i++) {
		if (wheels[i] != nullptr) {
			wheels[i]->calculateForce(chasis->pointVelocity(wheels[i]->getRelPosition()), dt);
		}
	}
}

// TODO fill these in correctly
void Car::driveForward() {
	chasis->addForce(sf::Vector2f(0, -1000));
}

void Car::turnLeft(float angle) {
	chasis->addForce(sf::Vector2f(1000, 0), sf::Vector2f(-50, 50));
}

void Car::turnRight(float angle) {
	chasis->addForce(sf::Vector2f(-1000, 0), sf::Vector2f(50, 50));
}

void Car::turbo(float turboPower) {

}

void Car::brake(float brakeTorque) {

}

void Car::driveBackward() {
	chasis->addForce(sf::Vector2f(0, 1000));
}

/*
- WHEEL CLASS
*/

void Wheel::setSteeringAngle(float angle) {

	/*
	forward direction
	points in direction car will move
	<sin(x), -cos(x)>
	<a, b>
	*/
	w_forwardAxis.x = sin(angle * 180.f / PI);
	w_forwardAxis.y = -cos(angle * 180.f / PI);

	/*
	side direction
	is perpendicular to foward direction
	<cos(x), sin(x)>
	<-b, a>
	*/
	w_sideAxis.x = cos(angle * 180.f / PI);
	w_sideAxis.y = sin(angle * 180.f / PI);
}

sf::Vector2f Wheel::calculateForce(sf::Vector2f &relativeGroundSpeed, float dt) {

	// calculate ground speed of tire
	sf::Vector2f patchSpeed = -w_forwardAxis * w_speed * w_radius;

	// calculate velocity difference (for acceleration purposes)
	sf::Vector2f velDifference = relativeGroundSpeed + patchSpeed;

	// TODO calculate effective velocities
	float forwardMag = 0;
	sf::Vector2f sideVel;
	sf::Vector2f forwardVel;

	// update torques and angular physics stuffs
	w_torque += forwardMag * w_radius;
	w_speed += w_torque / w_inertia * dt;
	w_torque = 0;

	return patchSpeed;
}

void Wheel::addTransmissionTorque(float torque) {}

float Wheel::getWheelSpeed() {
	return w_speed;
}

sf::Vector2f Wheel::getRelPosition() {
	return w_relPosition;
}