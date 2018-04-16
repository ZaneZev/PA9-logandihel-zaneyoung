#pragma once
#include "testing.h"
#include <SFML/Graphics.hpp>

class RigidBody : public sf::RectangleShape {
public:
	RigidBody(sf::Vector2f &pos=sf::Vector2f(), sf::Vector2f &size=sf::Vector2f()) 
		: sf::RectangleShape(size)
	{
		setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		setOutlineColor(sf::Color::Blue);
		setOutlineThickness(1);
		setPosition(pos);
		setFillColor(sf::Color::Transparent);

		acceleration = sf::Vector2f(0, 0);
		velocity = sf::Vector2f(0, 0);
		force = sf::Vector2f(0, 0);
		linearDrag = sf::Vector2f(0, 0);

		angA = 0.0;
		angV = 0.0;
		torque = 0.0;
		angularDrag = 0.0;
		angularDragC = 2;

		mass = 2.0;
		inertia = 60.0;
		linearDragC = 0.001;
	}

	// https://www.gamedev.net/forums/topic/470497-2d-car-physics-tutorial/
	void addForce(sf::Vector2f &worldForce, sf::Vector2f &relativeOffset = sf::Vector2f(0, 0));
	sf::Vector2f worldToRelative(sf::Vector2f &worldVector);
	sf::Vector2f relativeToWorld(sf::Vector2f &relativeVector);
	sf::Vector2f pointVelocity(sf::Vector2f &relativeOffset);

	void addTorque(float torque);
	void addForceInRelativeDirection(float newForce);
	
	virtual void updatePhysics(float dt);
	float crossProduct(sf::Vector2f &f, sf::Vector2f &offset);

protected:
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f force;
	sf::Vector2f linearDrag;

	float angA;
	float angV;
	float torque;
	float angularDrag;
	float angularDragC;

	float mass;
	float inertia;
	float linearDragC;
};