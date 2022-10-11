#include"Ball.hpp"

//lifespan
Ball::Ball(float velocity) {
	this->velocity = velocity;
	set_angle(get_radian_angle(90.f));
	//angle = get_radian_angle(90.f);
}

void Ball::set_player(Player& player) {
	this->player = &player;
}

void Ball::set_blocks(list<Block>& blocks) {
	this->blocks = &blocks;
}

//drawing

void Ball::set_position() {
	x_pos = window->getSize().x / 2.0;
	y_pos = window->getSize().y / 2.0;
}

//movement
void Ball::update_state() {
	//Vector2f next_position (get_position().x+ cos(angle) * velocity, get_position().y+ sin(angle) * velocity);
	//screen collision
	screen_collision window_collision_state = check_window_collision();
	solve_window_collision(window_collision_state);
	//player_collision
	solve_player_collision(check_player_collision());
	//blocks collision
	solve_blocks_collision(check_block_collision());
}

//collisions
void Ball::solve_window_collision(screen_collision state) {
	Game_object::solve_window_collision(state);
	if ((state == screen_collision::bottom) || (state == screen_collision::bottom_left) || (state == screen_collision::bottom_right)) {
		player->lose_hp();
	}
}

bool Ball::check_player_collision() {
	float player_width = player->get_width();
	float player_height = player->get_height();
	Vector2f player_position = player->get_position();
	float radius = this->get_height()/2.f;
	Vector2f ball_position = this->get_position();

	if (ball_position.y + radius >= player_position.y - player_height/2.f) {
		if ((ball_position.x >= player_position.x - player_width/2.f) && (ball_position.x <= player_position.x + player_width/2.f)){
			return true;
		}
	}
	return false;
}

void Ball::solve_player_collision(bool player_collision_state) {
	if (player_collision_state == false) {
		return;
	}
	float player_width = player->get_width();
	float player_left_bound = player->get_position().x - player_width / 2.0;
	float ball_position_x = this->get_position().x;
	
	this->set_angle(get_radian_angle((ball_position_x - player_left_bound) / player_width * 140.f + 180.f));
	
}

Ball::rectangle_collision Ball::check_block_collision() {
	float left_boundary = -get_width() / 2.f + get_position().x;
	float top_boundary = -get_height() / 2.f + get_position().y;
	float right_boundary = get_width() / 2.f + get_position().x;
	float bottom_boundary = get_height() / 2.f + get_position().y;


	for (Block block : (* blocks)) {
		float block_left_boundary = -block.get_width() / 2.f + block.get_position().x;
		float block_top_boundary = -block.get_height() / 2.f + block.get_position().y;
		float block_right_boundary = block.get_width() / 2.f + block.get_position().x;
		float block_bottom_boundary = block.get_height() / 2.f + block.get_position().y;
		if ((get_position().y >= block_top_boundary) && (get_position().y <= block_bottom_boundary)) {
			if ((right_boundary >= block_left_boundary)&&(right_boundary<=block_right_boundary)) {
				return Ball::rectangle_collision::left;
			}
			if ((left_boundary<=block_right_boundary)&&(left_boundary>=block_left_boundary)) {
				return Ball::rectangle_collision::right;
			}
		}
		if ((get_position().x >= block_left_boundary) && (get_position().x <= block_right_boundary)) {
			if ((top_boundary<=block_bottom_boundary)&&(top_boundary>=block_top_boundary)) {
				return Ball::rectangle_collision::bottom;
			}
			if ((bottom_boundary>=block_top_boundary)&&(bottom_boundary<=block_bottom_boundary)) {
				return Ball::rectangle_collision::top;
			}
		}

	}
	return Ball::rectangle_collision::no;
}

void Ball::solve_blocks_collision(rectangle_collision state) {
	switch (state)
	{
	case Ball::no:
		break;
	case Ball::top:
		set_angle(2 * M_PI - angle);
		break;
	case Ball::right:
		set_angle(3 * M_PI - angle);
		break;
	case Ball::bottom:
		set_angle(2 * M_PI - angle);
		break;
	case Ball::left:
		set_angle(3 * M_PI - angle);
		break;
	default:
		break;
	}
}

//changing properties