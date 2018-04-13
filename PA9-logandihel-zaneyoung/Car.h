#pragma once
#include <SFML/Graphics.hpp>
#include "testing.h"
#include "RigidBody.h"

#define PI 3.141592645

//https://www.gamedev.net/forums/topic/470497-2d-car-physics-tutorial/
class Car : public sf::Drawable {
public:
	Car(sf::Vector2f &pos, sf::Color color, sf::Vector2f &size)
	{

		chasis = new RigidBody(pos, size);
		//chasis->setFillColor(sf::Color::Yellow);

		texture = new sf::Texture;
		if (!texture->loadFromFile("./sprites/deborean.png")) {
			cout << "could not load texture" << endl;
		}

		chasis->setTexture(texture);
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
	sf::Texture *texture;
	RigidBody *chasis;
};

