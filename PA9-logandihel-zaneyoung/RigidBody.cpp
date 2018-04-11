#include "RigidBody.h"

void RigidBody::addForce(sf::Vector2f worldForce, sf::Vector2f worldOffset) {
	force += worldForce;
	torque += crossProduct(worldForce,worldOffset); 
}

void RigidBody::update(float dt) {
	
	acceleration = force / mass; // force is a vector
	velocity += acceleration * dt;
	setPosition(getPosition() + velocity * dt);
	force = sf::Vector2f(0, 0);

	angA = torque / inertia; // recondiser making torque a vector??
	angV += angA * dt;
	setRotation(getRotation() + angV * dt);
	torque = 0;
}

float RigidBody::crossProduct(sf::Vector2f &worldForce, sf::Vector2f &worldOffset) {
	if (worldOffset.y == 0)
		return 0;

	float f_magn = sqrt(worldForce.x * worldForce.x + worldForce.y * worldForce.y);
	float r_magn = sqrt(worldOffset.x * worldOffset.x + worldOffset.y * worldOffset.y);

	//cout << r_magn << endl;

	// we could calculate sin(atan(y/x)), but sin(atan(s)) = s/sqrt(s^2+1) ~ 1/s => x/y
	float sinatan = sin(atan(worldOffset.y / worldOffset.x));

	return -f_magn * r_magn * sinatan;
}