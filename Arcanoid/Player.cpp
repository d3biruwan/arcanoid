#include "Player.hpp"
#include"Game.hpp"

Player::Player(float velocity) {
	this->velocity = velocity;
	hp = player_hp;
}

void Player::set_position()  {
	x_pos = game->window->getSize().x / 2;
	y_pos = 0.9 * game->window->getSize().y;
	sprite.setPosition(x_pos, y_pos);
}


//Движение
void Player::move_left() {
	if (can_move_left == true) {
		sprite.move(-velocity, 0.f);
	}
}

void Player::move_right() {
	if (can_move_right == true) {
		sprite.move(velocity, 0.f);
	}
}

//коллизии

void Player::update_state(){
	screen_collision window_collision_state = check_window_collision();
	if (window_collision_state == screen_collision::right) {
		can_move_right = false;
	}
	else if(window_collision_state == screen_collision::left) {
		can_move_left = false;
	}
	else {
		can_move_left = true;
		can_move_right = true;
	}
}