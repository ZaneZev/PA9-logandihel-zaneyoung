#include "RigidBody2.h"

void RigidBody2::addForce(sf::Vector2f &force) {
	this->force += force;
}

void RigidBody2::addTorque(float torque) {
	this->torque += torque;
}

void RigidBody2::updateUnitVectors() {

	float angle_rad = getRotation() * 3.14159f / 180.f;
	float sinangle = sin(angle_rad);
	float cosangle = cos(angle_rad);

	this->up = sf::Vector2f(sinangle, -cosangle);
	this->right = sf::Vector2f(cosangle, -sinangle);
}

void RigidBody2::updatePhysics(float dt) {

	// linear drag forces
	// sets max speed
	sf::Vector2f linDrag;
	linDrag.x = velocity.x * velocity.x * 12 * (velocity.x > 0 ? 1 : -1);
	linDrag.y = velocity.y * velocity.y * 12 * (velocity.y > 0 ? 1 : -1);

	cout << linDrag.x << endl;

	// linear movement
	acceleration = (force - linDrag) * inv_mass;
	velocity += acceleration * dt;

	// forwards friction
	//velocity.x *= 0.9999f;
	// side friction
	//velocity.y *= 0.99f;

	if (velocity.x != 0.f || velocity.y != 0.f) {
		// accounts for the screen coordinates flipping the up axis
		setPosition(getPosition() + (up * velocity.x + right * velocity.y) * dt);
	}

	// angular drag forces
	// sets max rotations/sec
	float angDrag = angV * angV * 0.01 * (angV > 0 ? 1: -1);

	// angular movement
	angA = (torque - angDrag) * inv_inertia;
	angV += angA * dt;

	// also kill angular velocity pretty quickly
	angV *= 0.99;
	
	if (angV != 0.f) {
		setRotation(getRotation() + angV * dt);
		updateUnitVectors();
	}

	// set up for next frame
	force.x = 0.f;
	force.y = 0.f;
	torque = 0.f;
}