#pragma once
#include <SFML/Graphics.hpp>
#include "testing.h"
#include "RigidBody.h"

#define PI 3.141592645

class Wheel;
class Car;

class Wheel {

	friend class Car;

public:
	Wheel(sf::Vector2f &relPosition, float radius)
	{
		w_relPosition = relPosition;
		w_radius = radius;
	}

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

//https://www.gamedev.net/forums/topic/470497-2d-car-physics-tutorial/
class Car : public sf::Drawable {
public:
	Car(sf::Vector2f &pos, sf::Color color, sf::Vector2f &size)
	{

		chasis = new RigidBody(pos, size);
		chasis->setFillColor(sf::Color::Yellow);

		texture = new sf::Texture;
		if (!texture->loadFromFile("./sprites/first-car.png")) {
			cout << "could not load texture" << endl;
		}

		chasis->setTexture(texture);

		for (int i = 0; i < 4; i++) {
			wheels[i] = nullptr;
		}
	}

	void driveForward();
	void turnLeft(float angle = 45);
	void turnRight(float angle = 45);
	void turbo(float turboPower = 20);
	void brake(float brakeTorque = 100);
	void driveBackward();

	//virtual ~Car();
	void updatePhysics(float dt);

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	Wheel *wheels[4]; // front-left, front-right, bottom-left, bottom-right
	sf::Texture *texture;
	RigidBody *chasis;
};

