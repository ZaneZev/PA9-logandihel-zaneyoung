#pragma once
#include "testing.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Car.h"
#include <cmath>
#define PI 3.141592654
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Player : public sf::Drawable {
public:
	Player(string name = "") : sf::Drawable() { 
		this->name.setString(name);
		this->name.setOutlineColor(sf::Color::White);
		car = new Car(*(new sf::Vector2f(100, 100)), sf::Color::Yellow, *(new sf::Vector2f(30, 60)));
		this->name.setPosition(car->getPosition());
	}

	virtual ~Player();
	void update(float dt);

	void nudgeLeft();
	void nudgeRight();
	void nudgeUp();
	void nudgeDown();
	void stop();
	void rotateLeft();
	void rotateRight();

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	sf::Text name;
	Car *car;
};