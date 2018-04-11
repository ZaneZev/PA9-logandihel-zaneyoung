#pragma once
#include <SFML/Graphics.hpp>
#include "testing.h"
#include "RigidBody.h"

class Car : public RigidBody {
public:
	Car(sf::Vector2f &pos, sf::Color color, sf::Vector2f &size)
		: RigidBody(pos, color, size) {}
};