#pragma once
#include "testing.h"
#include <SFML/Graphics.hpp>

class RigidBody : public sf::RectangleShape {
public:
	RigidBody(sf::Vector2f &pos, sf::Color &c, sf::Vector2f &size) 
		: sf::RectangleShape(size)
	{
		setFillColor(c);
		setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		
		acceleration = sf::Vector2f(0, 0);
		velocity = sf::Vector2f(0, 0);
		force = sf::Vector2f(0, 0);

		angA = 0.0;
		angV = 0.0;
		torque = 0.0;

		mass = 1.0;
		inertia = 60; 
	}

	// https://www.gamedev.net/forums/topic/470497-2d-car-physics-tutorial/
	void addForce(sf::Vector2f worldForce, sf::Vector2f worldOffset = sf::Vector2f(0, 0));

	void update(float dt);

private:
	float crossProduct(sf::Vector2f &worldForce, sf::Vector2f &worldOffset);
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f force;

	float angA;
	float angV;
	float torque;

	float mass;
	float inertia;
};