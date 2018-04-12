#pragma once
#include <SFML/Graphics.hpp>
#include "testing.h"
#include "RigidBody.h"

class Wheel;

//https://www.gamedev.net/forums/topic/470497-2d-car-physics-tutorial/
class Car : public RigidBody {
public:
	Car(sf::Vector2f &pos, sf::Color color, sf::Vector2f &size)
		: RigidBody(pos, color, size) 
	{
		texture = new sf::Texture();
		texture->loadFromFile("./sprites/first-car.png");
		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		sprite->setScale(10, 10);
		sprite->setPosition(getPosition());
	}

	//virtual ~Car();
	//void updatePhysics(float dt);

private:
	//void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	Wheel *wheels[4]; // front-left, front-right, bottom-left, bottom-right
	sf::Texture *texture;
	sf::Sprite *sprite;
};

class Wheel : public sf::Drawable {

	friend class Car;

public:
	Wheel(sf::Vector2f &position, float radius)
		: sf::Drawable() {}

	void setSteeringAngle(float angle);
	void addTransmissionTorque(float torque);
	float getWheelSpeed();
	sf::Vector2f getAttachPoint();
	sf::Vector2f calculateForce(sf::Vector2f &relativeGroundSpeed, float dt);

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	sf::Vector2f forwardAxis;
	sf::Vector2f sideAxis;
	sf::Vector2f position;

	float torque;
	float speed;
	float inertia;
	float radius;
};
