#pragma once
#include <SFML/Graphics.hpp>
#include "testing.h"
#include "RigidBody.h"

#define PI 3.141592645

class Wheel;

//https://www.gamedev.net/forums/topic/470497-2d-car-physics-tutorial/
class Car : public RigidBody {
public:
	Car(sf::Vector2f &pos, sf::Color color, sf::Vector2f &size)
		: RigidBody(pos, size) 
	{
		setFillColor(sf::Color::Yellow);

		texture = new sf::Texture;
		if (!texture->loadFromFile("./sprites/first-car.png")) {
			cout << "could not load texture" << endl;
		}

		this->setTexture(texture);
	}

	//virtual ~Car();
	//void updatePhysics(float dt);

private:
	Wheel *wheels[4]; // front-left, front-right, bottom-left, bottom-right
	sf::Texture *texture;
	//sf::Sprite *sprite;
};

class Wheel : public RigidBody {

	friend class Car;

public:
	Wheel(sf::Vector2f &relPosition, float radius)
		: RigidBody() {}

	// angle is in degrees
	void setSteeringAngle(float angle);
	void addTransmissionTorque(float torque);
	float getWheelSpeed();
	sf::Vector2f getRelPosition();
	sf::Vector2f calculateForce(sf::Vector2f &relativeGroundSpeed, float dt);

private:
	sf::Vector2f w_forwardAxis;
	sf::Vector2f w_sideAxis;
	sf::Vector2f w_relPosition;

	float w_torque;
	float w_speed;
	float w_inertia;
	float w_radius;
};
