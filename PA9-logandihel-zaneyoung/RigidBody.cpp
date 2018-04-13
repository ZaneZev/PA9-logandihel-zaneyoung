#include "RigidBody.h"

void RigidBody::addForce(sf::Vector2f &worldForce, sf::Vector2f &relativeOffset) {
	force += worldForce;
	torque += crossProduct(worldForce, relativeOffset);
}

void RigidBody::addTorque(float torque) {
	this->torque += torque;
}

void RigidBody::updatePhysics(float dt) {

	float magVel2 = pow(velocity.x, 2) + pow(velocity.y, 2);
	if (magVel2 != 0) {
		linearDrag = -velocity * magVel2 * linearDragC / sqrt(magVel2);
	}
	else {
		linearDrag.x = 0;
		linearDrag.y = 0;
	}

	// angular drag stuffs
	angularDrag = -pow(angV, 2) * angularDragC;
	if (angV < 0) {
		angularDrag *= -1;
	}


	acceleration = (force + linearDrag) / mass; // force is a vector

	velocity += acceleration * dt;
	setPosition(getPosition() + velocity * dt);
	force = sf::Vector2f(0, 0);

	angA = (torque + angularDrag) / inertia; 
	angV += angA * dt;
	setRotation(getRotation() + angV * dt);
	torque = 0;
}

// precondition: we have determined the force should interact with RigidBody instance
float RigidBody::crossProduct(sf::Vector2f &f, sf::Vector2f &offset) {
	// no rotation if the offsets are zero
	if (offset.x == 0 || offset.y == 0)
		return 0;

	float f_magn = sqrt(f.x * f.x + f.y * f.y);
	float r_magn = sqrt(offset.x * offset.x + offset.y * offset.y);

	// we could calculate sin(atan(y/x)), but sin(atan(s)) = s/sqrt(s^2+1) ~ 1/s => x/y
	// but approx makes the game feel a lot more sluggish...
	//float sinatanapprox = offset.x / offset.y;
	float sinatan = sin(atan(offset.y / offset.x));
	//cout << "exact: " << sinatan << ", approx: " << sinatanapprox << ", diff: " << sinatanapprox - sinatan << endl;

	return f_magn * r_magn * sinatan;
}

sf::Vector2f RigidBody::worldToRelative(sf::Vector2f &worldVector) {
	return worldVector - getOrigin();
}

sf::Vector2f RigidBody::relativeToWorld(sf::Vector2f &relativeVector) {
	return relativeVector + getOrigin();
}

// https://www.gamedev.net/forums/topic/470497-2d-car-physics-tutorial/
sf::Vector2f RigidBody::pointVelocity(sf::Vector2f &relativeOffset) {
	sf::Vector2f tangent = sf::Vector2f(-relativeOffset.y, relativeOffset.x);
	return tangent * angV + velocity;
}
