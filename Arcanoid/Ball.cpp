#include"Ball.hpp"

Ball::Ball(float velocity) {
	this->velocity = velocity;
	angle = get_radian_angle(30.0);
}

void Ball::set_player(Player& player) {
	this->player = &player;
}

void Ball::set_position() {
	x_pos = window->getSize().x / 2.0;
	y_pos = window->getSize().y / 2.0;
}

//движение
void Ball::update_state() {
	//Vector2f next_position (sprite.getPosition().x+ cos(angle) * velocity, sprite.getPosition().y+ sin(angle) * velocity);

	screen_collision window_collision_state = check_window_collision();
	window_collision_solve(window_collision_state);

}

//коллизии
void Ball::window_collision_solve(screen_collision state) {
	Game_object::window_collision_solve(state);
	if ((state == screen_collision::bottom) || (state == screen_collision::bottom_left) || (state == screen_collision::bottom_right)) {
		player->lose_hp();
	}
}
