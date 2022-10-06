#include "Player.hpp"

Player::Player(double velocity) {
	this->velocity = velocity;
	//this->size = size;
}

void Player::set_position(RenderWindow& window) {
	x_pos = window.getSize().x / 2;
	y_pos = 0.9 * window.getSize().y;
}

void Player::set_texture(Texture& texture) {
	sprite.setTexture(texture);
	sprite.setScale(0.75, 0.75);
	double width = sprite.getLocalBounds().width;
	double height = sprite.getLocalBounds().height;
	sprite.setOrigin(width / 2, height / 2);
	sprite.setPosition(x_pos, y_pos);
}

void Player::draw(RenderWindow& window) {
	window.draw(sprite);
}