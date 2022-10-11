#include "Game_object.hpp"

//lifespan
Game_object::Game_object(float velocity, float angle) {
	this->velocity = velocity;
	set_angle(get_radian_angle(angle));
	//this->angle = get_radian_angle(angle);
}

void Game_object::lose_hp() {
	--hp;
}

//drawing
void Game_object:: set_window(RenderWindow& window) {
	this->window = &window;
}

void Game_object::set_position(float x, float y) {
	x_pos = x;
	y_pos = y;
}

void Game_object::set_texture(Texture& texture) {
	sprite.setTexture(texture);
	//sprite.setScale(0.75, 0.75);
	float width = get_width();
	float height = get_height();
	sprite.setOrigin(width / 2.f, height / 2.f);
	sprite.setPosition(x_pos, y_pos);
}

void Game_object::set_color(Color color) {
	sprite.setColor(color);
}

void Game_object::draw() {
	window->draw(sprite);
}

//movement

void Game_object::move() {
	sprite.move(cos(angle) * velocity, sin(angle) * velocity);
}

//properties
float Game_object:: get_width() {
	return sprite.getLocalBounds().width;
}

float Game_object::get_height() {
	return sprite.getLocalBounds().height;
}

Vector2f Game_object::get_position() {
	return sprite.getPosition();
}

//Коллизии 
//Экран

Game_object::screen_collision Game_object::check_window_collision() {
	float left_boundary = -get_width() / 2.f + get_position().x;
	float top_boundary = -get_height() / 2.f + get_position().y;
	float right_boundary = get_width() / 2.f + get_position().x;
	float bottom_boundary = get_height() / 2.f + get_position().y;

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

void Game_object::solve_window_collision(screen_collision state) {
	switch (state)
	{
	case screen_collision::no:
		break;
	case top:
		set_angle(2 * M_PI - angle);
		//angle = 2 * M_PI - angle;
		break;
	case screen_collision::right:
		set_angle(3 * M_PI - angle);
		//angle = 3 * M_PI - angle;
		break;
	case screen_collision::bottom:
		set_angle(2 * M_PI - angle);
		//angle = 2 * M_PI - angle;
		break;
	case screen_collision::left:
		set_angle(3 * M_PI - angle);
		//angle = 3 * M_PI - angle;
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
float Game_object::get_radian_angle(float angle) {
	return angle * M_PI / 180.0;
}

float Game_object::get_distance_from_point(const Vector2f& point) {
	return sqrt(pow(get_position().x-point.x, 2.f) + pow(get_position().y-point.y,2.f));
}

//changing properties
void Game_object::set_angle(float angle) {
	this->angle = angle;
}