#pragma once
#include <SFML/Graphics.hpp>
#include "testing.h"

class Car : public sf::Drawable {
	friend class Player;
public:
	Car(float width = 30, float height = 60) 
		: sf::Drawable() {
		rect.setFillColor(sf::Color::Yellow);
		rect.setSize(sf::Vector2f(width, height));
		rect.setOrigin(sf::Vector2f(width / 2, height / 2));
	}

	void setAcceleration(sf::Vector2f &acceleration);
	void setVelocity(sf::Vector2f &velocity);
	void setPosition(sf::Vector2f &position);

	sf::Vector2f getAcceleration();
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();

	// runs every game loop
	// updates the position, velocity
	void update();

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::RectangleShape rect;
	float mass;
};