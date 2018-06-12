#include "Player.h"

Player::~Player() {}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(*car, states);
}