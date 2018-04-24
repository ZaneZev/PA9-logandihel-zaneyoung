#pragma once
#include "testing.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Car.h"
#include <cmath>
#include "collidable.h"
#include "map.h"
#define PI 3.141592654
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Player : public sf::Drawable {
public:
	Player(sf::Vector2f &pos, string name = "") : sf::Drawable() { 
		this->name.setString(name);
		this->name.setOutlineColor(sf::Color::White);
		car = new Car(pos, sf::Color::Yellow, *(new sf::Vector2f(16, 32)));
		checkpoints = 0;
		pNextMarker = nullptr;
		pMap = nullptr;
	}

	virtual ~Player();
	virtual void update() = 0;
	virtual void updatePhysics(float dt) = 0;

	int getCheckpoints() { return checkpoints; }
	void addCheckpoint() { checkpoints++; }

	marker* getNextMarker() { return pNextMarker; }
	void setNextMarker(marker *next) { pNextMarker = next; }

	Car * getCar() { return car; }
	map * pMap;

protected:
	Car *car;

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	sf::Text name;
	int checkpoints;
	marker *pNextMarker;
};