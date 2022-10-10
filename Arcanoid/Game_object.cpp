#include "Game_object.hpp"

double Game_object::get_radian_angle(double angle) {
	return angle * M_PI / 180.0;
}

Game_object::Game_object(float velocity, double angle) {
	this->velocity = velocity;
	this->angle = get_radian_angle(angle);
}

void Game_object:: set_window(RenderWindow& window) {
	this->window = &window;
}


void Game_object::set_position(double x, double y) {
	x_pos = x;
	y_pos = y;
}

void Game_object::set_texture(Texture& texture) {
	sprite.setTexture(texture);
	sprite.setScale(0.75, 0.75);
	double width = sprite.getLocalBounds().width;
	double height = sprite.getLocalBounds().height;
	sprite.setOrigin(width / 2, height / 2);
	sprite.setPosition(x_pos, y_pos);
}

void Game_object::draw() {
	window->draw(sprite);
}

//Движение
void Game_object::move() {
	sprite.move(cos(angle) * velocity, sin(angle) * velocity);
}