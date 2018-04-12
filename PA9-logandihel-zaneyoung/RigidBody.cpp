#include "RigidBody.h"

void RigidBody::addForce(sf::Vector2f &worldForce, sf::Vector2f &relativeOffset) {
	force += worldForce;
	torque += crossProduct(worldForce, relativeOffset);
}

void RigidBody::updatePhysics(float dt) {
	acceleration = force / mass; // force is a vector
	velocity += acceleration * dt;
	setPosition(getPosition() + velocity * dt);
	force = sf::Vector2f(0, 0);

	angA = torque / inertia; 
	angV += angA * dt;
	setRotation(getRotation() + angV * dt);
	torque = 0;
}

float RigidBody::crossProduct(sf::Vector2f &f, sf::Vector2f &offset) {
	if (offset.y == 0)
		return 0;

	float f_magn = sqrt(f.x * f.x + f.y * f.y);
	float r_magn = sqrt(offset.x * offset.x + offset.y * offset.y);

	// we could calculate sin(atan(y/x)), but sin(atan(s)) = s/sqrt(s^2+1) ~ 1/s => x/y
	float sinatan = sin(atan(offset.y / offset.x));

	return f_magn * r_magn * sinatan;
}

sf::Vector2f RigidBody::worldToRelative(sf::Vector2f &worldVector) {
	return worldVector - getOrigin();
}

sf::Vector2f RigidBody::relativeToWorld(sf::Vector2f &relativeVector) {
	return relativeVector + getOrigin();
}