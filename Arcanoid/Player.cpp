#include "Player.hpp"

Player::Player(float velocity) {
	this->velocity = velocity;
}

void Player::set_position()  {
	x_pos = window->getSize().x / 2;
	y_pos = 0.9 * window->getSize().y;
}


//Движение
void Player::move_left() {
	sprite.move(-velocity, 0.f);
}

void Player::move_right() {
	sprite.move(velocity, 0.f);
}