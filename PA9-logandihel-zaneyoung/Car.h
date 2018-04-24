#pragma once
#include <SFML/Graphics.hpp>
#include "testing.h"
#include "RigidBody2.h"
#include "RigidBody.h"

#define PI 3.141592645

//https://www.gamedev.net/forums/topic/470497-2d-car-physics-tutorial/
class Car : public sf::Drawable {
public:
	Car(sf::Vector2f &pos, sf::Color color, sf::Vector2f &size,std::string carPath)
	{
		chasis = new RigidBody2(sf::Vector2f(size.x - 8, size.y - 8), pos);
		//chasis = new RigidBody(pos, size);
		//chasis->setFillColor(sf::Color::Yellow);
		carBody = new sf::RectangleShape(size);

		texture = new sf::Texture;
		if (!texture->loadFromFile(carPath)) {
			cout << "could not load texture" << endl;
		}

		carBody->setTexture(texture);
		carBody->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	}

	void driveForward();
	void turnLeft(float angle = 45);
	void turnRight(float angle = 45);
	void turbo(float turboPower = 20);
	void brake(float brakeTorque = 100);
	void driveBackward();

	sf::Vector2f getPosition() { return chasis->getPosition(); }

	//virtual ~Car();
	void updatePhysics(float dt);
	void start_drift();
	void stop_drift();
	RigidBody2 * getRigidBody() {
		return chasis;
	}
	sf::RectangleShape* GetcarBody() { return carBody; }
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	sf::RectangleShape *carBody;
	sf::Texture *texture;
	RigidBody2 *chasis;
};

