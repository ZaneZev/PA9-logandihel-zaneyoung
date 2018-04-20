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
		//for (Player * p : players) {
		for(int i = 0; i<players.size();i++){
			Player *p = players[i];
			for (collidable * c : map->collidables) {
				if (c->getGlobalBounds().intersects(p->getCar()->getRigidBody()->getGlobalBounds())) {
					if (c->solid) {
						p->getCar()->getRigidBody()->velocity.x = -5.0f;
						//std::cout << "I HIT THE BIG BLUE BOX O' DOOOOOOOOM!" << std::endl;
					}
					else {
						//std::cout << "I HIT THE ETHERIAL THING OF THE GODS!" << endl;
					}
				}
			}
			
			for (int j = 0; j < players.size();j++) {
				if (j != i) {
					Player *op = players[j];
					if (op->getCar()->getRigidBody()->getGlobalBounds().intersects(p->getCar()->getRigidBody()->getGlobalBounds())) {
						p->getCar()->getRigidBody()->velocity.x = -5.0f;
						std::cout << "I HIT ANOTHER DAMN CAR!" << std::endl;
					}
				}
			}
		}
	}
private:
	map *map;
	std::vector<Player *> players;

};