#pragma once
#include "collidable.h"
#include "map.h"
#include "LocalPlayer.h"

class collisionHandler {
public:
	collisionHandler(map * map, std::vector<Player *> players) {
		this->map = map;
		this->players = players;
	}
	void handleCollisions() {
		for (Player * p : players) {
			for (collidable * c : map->collidables) {
				for (int i = 0; i < 4; i++) {
					if (c->getGlobalBounds().intersects(p->getCar()->getRigidBody()->getGlobalBounds())) {
						p->getCar()->getRigidBody()->addForce(sf::Vector2f(-10000000.0f, 0.0f));
						std::cout << "I HIT THE THING!" << std::endl;
					}
				}
			}
		}
	}
private:
	map *map;
	std::vector<Player *> players;

};