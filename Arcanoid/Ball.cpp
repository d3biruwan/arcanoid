#include"Ball.hpp"

Ball::Ball(float velocity) {
	this->velocity = velocity;
	angle = get_radian_angle(90.0);
}

void Ball::set_position() {
	x_pos = window->getSize().x / 2.0;
	y_pos = window->getSize().y / 2.0;
}

//void Ball::set_color(const Color& color) {
//	shape.setFillColor(color);
//}

//void Ball::draw() {
//	window->draw(shape);
//}