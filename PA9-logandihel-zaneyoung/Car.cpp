#include "Car.h"

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

	// calculate effective velocities
	sf::Vector2f sideVel;
	sf::Vector2f forwardVel;

	return patchSpeed;
}