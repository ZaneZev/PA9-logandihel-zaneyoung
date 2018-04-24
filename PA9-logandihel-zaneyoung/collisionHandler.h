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

			bool collided = false;
			RigidBody2 *rb2 = p->getCar()->getRigidBody();
			float bounce = rb2->velocity.x * 1;


			for (collidable * c : map->collidables) {
				if (c->getGlobalBounds().intersects(p->getCar()->getRigidBody()->getGlobalBounds())) {

					if (c->solid) {
						if (rb2->velocity.x < 0) {
							rb2->velocity.x = -bounce;
						}
						else {
							rb2->velocity.x = -20.f;
						}
						
					}
					else {
						// we hit marker
						//cout << "hit marker" << endl;
						if (p->nextCheckpoint == c) {
							p->nextCheckpoint = (dynamic_cast<marker *>(c))->pNextMarker;
							p->incCheckpointsHit();
						}
					}
					/*
					if (c->solid) {
						collided = true;
						// is it going forwards?
						if (rb2->velocity.x >= 0) {
							// was it in the block?
							if (rb2->wasInBlock) {
								rb2->velocity.x = bounce;
							}
							else {
								rb2->velocity.x = -bounce;
							}
						}
						else {
							// was it in the block?
							if (rb2->wasInBlock) {
								rb2->velocity.x = -bounce;
							}
							else {
								rb2->velocity.x = bounce;
							}
						}
					}
					else {
						// not a solid block
					}
					*/
				}
			}
			/*
			rb2->wasInBlock = collided;
			*/
			
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