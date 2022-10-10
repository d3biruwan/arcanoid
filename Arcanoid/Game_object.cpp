#include "Game_object.hpp"

//lifespan
Game_object::Game_object(float velocity, double angle) {
	this->velocity = velocity;
	this->angle = get_radian_angle(angle);
}

void Game_object::lose_hp() {
	--hp;
}

//drawing
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

//movement

void Game_object::move() {
	sprite.move(cos(angle) * velocity, sin(angle) * velocity);
}

//Коллизии 
//Экран

screen_collision Game_object::check_window_collision() {
	double left_boundary = -sprite.getLocalBounds().width / 2.0 + sprite.getPosition().x;
	double top_boundary = -sprite.getLocalBounds().height / 2.0 + sprite.getPosition().y;
	double right_boundary = sprite.getLocalBounds().width / 2.0 + sprite.getPosition().x;
	double bottom_boundary = sprite.getLocalBounds().height / 2.0 + sprite.getPosition().y;

	if (right_boundary >= window->getSize().x) {
		if (bottom_boundary >= window->getSize().y) {
			return screen_collision::bottom_right;
		}
		if (top_boundary <= 0.0) {
			return screen_collision::top_right;
		}
		return screen_collision::right;
	}
	if (left_boundary <= 0) {
		if (bottom_boundary >= window->getSize().y) {
			return screen_collision::bottom_left;
		}
		if (top_boundary <= 0) {
			return screen_collision::top_left;
		}
		return screen_collision::left;
	}
	if (top_boundary <= 0) {
		return screen_collision::top;
	}
	if (bottom_boundary >= window->getSize().y) {
		return screen_collision::bottom;
	}
	return screen_collision::no;
}

void Game_object::window_collision_solve(screen_collision state) {
	switch (state)
	{
	case screen_collision::no:
		break;
	case top:
		angle = 2 * M_PI - angle;
		break;
	case screen_collision::right:
		angle = 3 * M_PI - angle;
		break;
	case screen_collision::bottom:
		angle = 2 * M_PI - angle;
		break;
	case screen_collision::left:
		angle = 3 * M_PI - angle;
		break;
		/*case screen_collision::top_right:
			break;
		case screen_collision::bottom_right:
			break;
		case screen_collision::bottom_left:
			break;
		case screen_collision::top_left:
			break;*/
	default:
		angle = M_PI + angle;
		break;
	}

}

//utility
double Game_object::get_radian_angle(double angle) {
	return angle * M_PI / 180.0;
}