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

	this->up = sf::Vector2f(sinangle, cosangle);
	this->right = sf::Vector2f(cosangle, sinangle);
}

void RigidBody2::updatePhysics(float dt) {

	// linear movement
	acceleration = force * inv_mass;
	velocity += acceleration * dt;
	// accounts for the screen coordinates flipping the up axis
	if (velocity.x != 0.f || velocity.y != 0.f) {
		sf::Vector2f ds = sf::Vector2f(-velocity.x, velocity.y) * dt;
		setPosition(getPosition() + ds);
	}

	// angular movement
	angA = torque * inv_inertia;
	angV += angA * dt;
	if (angV != 0.f) {
		setRotation(getRotation() + angV * dt);
		updateUnitVectors();
	}
	
	// prepare for next frame
	force.x = 0.f;
	force.y = 0.f;
	torque = 0.f;

}