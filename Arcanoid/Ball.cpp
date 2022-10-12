#include"Ball.hpp"
#include"Game.hpp"

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

void Ball::lose_hp() {
	hp--;
	if (get_hp() == 0) {
		on_death();
	}
}

void Ball::on_death() {
	int counter = 0;
	Clock clock;
	while (counter < 4) {
		float elapsed = clock.getElapsedTime().asSeconds();
		if (elapsed > 0.5) {
			change_opacity();
			window->clear();
			game->draw();
			window->display();
			++counter;
			clock.restart();
		}
	}
	set_hp(1);
	set_angle(get_radian_angle(90.f));
	set_position();
	player->set_position();
	//sprite.setPosition(x_pos, y_pos);
}

//drawing

void Ball::set_position() {
	x_pos = window->getSize().x / 2.0;
	y_pos = window->getSize().y / 2.0;
	sprite.setPosition(x_pos, y_pos);
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
	if (state == no) {
		return;
	}
	if ((state == screen_collision::bottom) || (state == screen_collision::bottom_left) || (state == screen_collision::bottom_right)) {
		player->lose_hp();
		lose_hp();
	}
	reset_collision();
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
	
	this->set_angle(get_radian_angle((ball_position_x - player_left_bound) / player_width * 140.f + 200.f));
	reset_collision();
}

Ball::rectangle_collision Ball::check_block_collision()
{
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
		//top left corner collision
		if (get_distance_from_point(block_left_boundary, block_top_boundary) <= get_width() / 2.f) {
			float bottom_dist = distance_between(get_position().x, bottom_boundary, block_left_boundary, block_top_boundary);
			float right_dist = distance_between(right_boundary, get_position().y, block_left_boundary, block_top_boundary);
			if (bottom_dist>right_dist) {
				return Ball::rectangle_collision::left;
			}
			else {
				return Ball::rectangle_collision::top;
			}
		}
		//top right corner collsion
		if (get_distance_from_point(block_right_boundary, block_top_boundary) <= get_width() / 2.f) {
			float bottom_dist = distance_between(get_position().x, bottom_boundary, block_right_boundary, block_top_boundary);
			float left_dist = distance_between(left_boundary, get_position().y, block_right_boundary, block_top_boundary);
			if (bottom_dist > left_dist) {
				return Ball::rectangle_collision::right;
			}
			else {
				return Ball::rectangle_collision::top;
			}
		}
		//bottom right collision
		if (get_distance_from_point(block_right_boundary, block_bottom_boundary) <= get_width() / 2.f) {
			float top_dist = distance_between(get_position().x, top_boundary, block_right_boundary, block_bottom_boundary);
			float left_dist = distance_between(left_boundary, get_position().y, block_right_boundary, block_bottom_boundary);
			if (top_dist > left_dist) {
				return Ball::rectangle_collision::right;
			}
			else {
				return Ball::rectangle_collision::bottom;
			}
		}
		//bottom left collison
		if (get_distance_from_point(block_left_boundary, block_bottom_boundary) <= get_width() / 2.f) {
			float top_dist = distance_between(get_position().x, top_boundary, block_left_boundary, block_bottom_boundary);
			float right_dist = distance_between(right_boundary, get_position().y, block_left_boundary, block_bottom_boundary);
			if (top_dist > right_dist) {
				return Ball::rectangle_collision::left;
			}
			else {
				return Ball::rectangle_collision::bottom;
			}
		}
	}
	return Ball::rectangle_collision::no;
}

void Ball::solve_blocks_collision(rectangle_collision state) {
	if (last_collison == state) {
		return;
	}
	switch (state)
	{
	case Ball::no:
		return;
	case Ball::top:
		set_angle(2 * M_PI - angle);
		break;
	case Ball::right:
		set_angle(M_PI - angle);
		break;
	case Ball::bottom:
		set_angle(2 * M_PI - angle);
		break;
	case Ball::left:
		set_angle(M_PI - angle);
		break;
	default:
		break;
	}
	set_last_collison(state);
}

void Ball::reset_collision() {
	last_collison = no;
}

void Ball::set_last_collison(rectangle_collision state) {
	last_collison = state;
}

//changing properties