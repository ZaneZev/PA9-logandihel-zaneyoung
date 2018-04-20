#pragma once
#include "testing.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
class collidable : public sf::RectangleShape {
public:
	bool solid;
	collidable(sf::Vector2f size, sf::Vector2f pos, float rot, sf::Color color, bool solid) : RectangleShape(size) {
		this->setPosition(pos);
		this->setRotation(rot);
		this->setFillColor(color);
		this->solid = solid;
	}
};