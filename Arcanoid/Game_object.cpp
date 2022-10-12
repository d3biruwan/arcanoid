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

void Game_object::set_hp(int hp) {
	this->hp = hp;
}

void Game_object::set_game(Game& game) {
	this->game = &game;
}

//drawing
void Game_object::change_opacity() {
	Color color = get_color();
	if (color.a == 255) {
		color.a = 0;
	}
	else {
		color.a = 255;
	}
	set_color(Color(color.r, color.g, color.b, color.a));
}

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
const Color& Game_object::get_color() {
	return sprite.getColor();
}

const int Game_object::get_hp() {
	return hp;
}

const float Game_object:: get_width() {
	return sprite.getLocalBounds().width;
}

const float Game_object::get_height() {
	return sprite.getLocalBounds().height;
}

const Vector2f& Game_object::get_position() {
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
		return;
	case top:
		set_position(get_position().x,get_height()/2.f);
		set_angle(2 * M_PI - angle);
		//angle = 2 * M_PI - angle;
		break;
	case screen_collision::right:
		set_position(window->getSize().x - get_width() / 2.f, get_position().y);
		set_angle(3 * M_PI - angle);
		//angle = 3 * M_PI - angle;
		break;
	case screen_collision::bottom:
		set_position(get_position().x, window->getSize().y-get_height() / 2.f);
		set_angle(2 * M_PI - angle);
		//angle = 2 * M_PI - angle;
		break;
	case screen_collision::left:
		set_position(get_width() / 2.f, get_position().y);
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

float distance_between(float x_1, float y_1, float x_2, float y_2) {
	return sqrt(pow(x_1 - x_2, 2.f) + pow(y_1 - y_2, 2.f));
}

float distance_between(const Vector2f& point_1, const Vector2f& point_2) {
	return distance_between(point_1.x, point_1.y, point_2.x, point_2.y);
}

float Game_object::get_distance_from_point(const Vector2f& point) {
	return distance_between(get_position().x, get_position().y, point.x, point.y);
}

float Game_object::get_distance_from_point(float x, float y) {
	return distance_between(get_position().x, get_position().y, x, y);
}

//changing properties
void Game_object::set_angle(float angle) {
	this->angle = angle;
}