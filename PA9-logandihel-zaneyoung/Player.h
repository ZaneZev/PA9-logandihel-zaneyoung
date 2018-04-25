#ifndef PLAYER_H
#define PLAYER_H

#include "testing.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Car.h"
#include <cmath>
#define PI 3.141592654
#include <iostream>
#include "collidable.h"

using std::cout;
using std::endl;
using std::string;

class Player : public sf::Drawable {
public:
	Player(sf::Vector2f &pos,string carPath ,string name = "" ) : sf::Drawable() { 
		this->name = name;
		car = new Car(pos, sf::Color::Yellow, *(new sf::Vector2f(16, 32)),carPath);
		nextCheckpoint = nullptr;
		checkpointsHit = 0;
	}

	virtual ~Player();
	virtual void update() = 0;
	virtual void updatePhysics(float dt) = 0;

	int getCheckpointsHit() { return checkpointsHit; }
	void setCheckpointsHit(int cph) { checkpointsHit = cph; }
	void incCheckpointsHit() { ++checkpointsHit; }

	Car * getCar() { return car; }
	marker *nextCheckpoint;

	string name;

protected:
	Car *car;
	
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
	int checkpointsHit;
};
#endif