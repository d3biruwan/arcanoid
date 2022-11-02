#include"Block.hpp"
#include"Game.hpp"

//lifespan
Block::Block(int pos) {
	set_list_position(pos);
}

Block::Block(bool destructible, int pos){
	this->destructible = destructible;
	set_list_position(pos);
}

void Block::set_list_position(int pos) {
	list_pos = pos;
}

void Block::lose_hp() {
	if (!destructible) {
		return;
	}
	--hp;
	game->increase_score();
	if (hp == 0) {
		on_death();
		return;
	}
	set_color(game->block_colors.at(hp - 1));
}

void Block::on_death() {
	for (auto& block : game->blocks) {
		if (get_list_position() < block->get_list_position()) {
			block->set_list_position(block->get_list_position() - 1);
		}
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 10);

	if ((dist(gen) > 4)&&(game->balls.size()+game->moving_blocks.size()+game->bonuses.size()<max_balls_count + max_moving_blocks + 1)) {
		auto bonus = make_unique<Bonus_item>(*(this->game), this->game->bonus_texture, get_position().x, get_position().y, block_velocity);
		game->bonuses.push_back(std::move(bonus));
	}
	
	
	auto iter = game->blocks.cbegin();
	for (int i = 0; i < get_list_position(); i++, ++iter);
	auto temp_iter = iter++;
	game->blocks.erase(temp_iter);	
}

void Block::make_accelerating(float acceleration, Texture& new_texture) {
	set_texture(new_texture);
	this->acceleration = acceleration;
}

//drawing


//properties
const float Block::get_accelertaion() {
	return acceleration;
}

const int Block::get_list_position() {
	return list_pos;
}


Moving_Block::Moving_Block(float velocity,Game& game) {
	set_game(game);
	set_velocity(velocity);

	//set_angle(M_PI + (rand() % 101) / 100 * M_PI);

	set_angle(-M_PI/2.f);
	if (this->game->moving_blocks.empty() == true) {
		set_list_position(0);
	}
	else {
		set_list_position((this->game->moving_blocks.end() - 1)->get()->get_list_position() + 1);
	}
}

void Moving_Block::on_death() {
	for (auto& block : game->moving_blocks) {
		if (get_list_position() < block->get_list_position()) {
			block->set_list_position(block->get_list_position() - 1);
		}
	}
	game->moving_blocks.erase(game->moving_blocks.cbegin() + get_list_position());
}

void Moving_Block::set_position() {
	x_pos = game->window->getSize().x / 2.0;
	y_pos = game->window->getSize().y / 2.0;
	sprite.setPosition(x_pos, y_pos);
}

void Moving_Block::update_state() {
	solve_window_collision(check_window_collision());
	solve_blocks_collision(check_blocks_collision());
	solve_moving_blocks_collision(check_moving_blocks_collision());
	solve_player_collsion(check_player_collision());
}

Moving_Block::rectangle_collision Moving_Block::check_blocks_collision() {
	float V_x = cos(get_angle()) * get_velocity();
	float V_y = sin(get_angle()) * get_velocity();
	/*float V_x = 0;
	float V_y = 0;*/

	float pos_x = get_position().x + V_x;
	float pos_y = get_position().y + V_y;
	
	float left = get_global_bounds().left + V_x;
	float right = get_global_bounds().width +left;
	float top = get_global_bounds().top + V_y;
	float bottom = top + get_global_bounds().height;


	for (auto& block : game->blocks) {
		if (block->get_velocity() != 0) {
			if (block->get_list_position() <= get_list_position()) {
				continue;
			}
		}
		float block_left = block->get_global_bounds().left ;
		float block_right = block->get_global_bounds().width + block_left;
		float block_top = block->get_global_bounds().top;
		float block_bottom = block_top + block->get_global_bounds().height;
		
		float right_collision_distance = 0.f;
		float left_collision_distance = 0.f;
		float top_collision_distance = 0.f;
		float bottom_collision_distance = 0.f;

		float min = 0.f;

	
		if ((bottom >= block_top) && (top <= block_bottom)) {
			if ((right >= block_left) && (right <= block_right)) {
				left_collision_distance = fabs(right - block_left);
				min = left_collision_distance;
				//return Moving_Block::rectangle_collision::left;
			}
			if ((left <= block_right) && (left >= block_left)) {
				right_collision_distance = fabs(left - block_right);
				if ((min > right_collision_distance) || (min == 0.f)) {
					min = right_collision_distance;
				}
				//return Moving_Block::rectangle_collision::right;
			}
		}
		if ((right >= block_left) && (left <= block_right)) {
			if ((top <= block_bottom) && (top >= block_top)) {
				bottom_collision_distance = fabs(top - block_bottom);
				if ((min > bottom_collision_distance) || (min == 0.f)) {
					min = bottom_collision_distance;
				}
				//return Moving_Block::rectangle_collision::bottom;
			}
			if ((bottom >= block_top) && (bottom <= block_bottom)) {
				top_collision_distance = fabs(bottom - block_top);
				if ((min > top_collision_distance) || (min == 0.f)) {
					min = top_collision_distance;
				}
				//return Moving_Block::rectangle_collision::top;
			}
		}

		if (min == 0.f) {
			continue;
		}
		if (left_collision_distance == min) {
			return Moving_Block::rectangle_collision::left;
		}
		if (top_collision_distance == min) {
			return Moving_Block::rectangle_collision::top;
		}
		if (bottom_collision_distance == min) {
			return Moving_Block::rectangle_collision::bottom;
		}
		if (right_collision_distance == min) {
			return Moving_Block::rectangle_collision::right;
		}
	}
	return no;
}

Moving_Block::rectangle_collision Moving_Block::check_moving_blocks_collision() {
	float V_x = cos(get_angle()) * get_velocity();
	float V_y = sin(get_angle()) * get_velocity();
	/*float V_x = 0;
	float V_y = 0;*/

	float pos_x = get_position().x + V_x;
	float pos_y = get_position().y + V_y;

	float left = get_global_bounds().left + V_x;
	float right = get_global_bounds().width + left;
	float top = get_global_bounds().top + V_y;
	float bottom = top + get_global_bounds().height;


	for (auto& block : game->moving_blocks) {
		if (block->get_list_position() <= get_list_position()) {
			continue;
		}
		float block_left = block->get_global_bounds().left;
		float block_right = block->get_global_bounds().width + block_left;
		float block_top = block->get_global_bounds().top;
		float block_bottom = block_top + block->get_global_bounds().height;

		float right_collision_distance = 0.f;
		float left_collision_distance = 0.f;
		float top_collision_distance = 0.f;
		float bottom_collision_distance = 0.f;

		float min = 0.f;


		if ((bottom >= block_top) && (top <= block_bottom)) {
			if ((right >= block_left) && (right <= block_right)) {
				left_collision_distance = fabs(right - block_left);
				min = left_collision_distance;
				//return Moving_Block::rectangle_collision::left;
			}
			if ((left <= block_right) && (left >= block_left)) {
				right_collision_distance = fabs(left - block_right);
				if ((min > right_collision_distance) || (min == 0.f)) {
					min = right_collision_distance;
				}
				//return Moving_Block::rectangle_collision::right;
			}
		}
		if ((right >= block_left) && (left <= block_right)) {
			if ((top <= block_bottom) && (top >= block_top)) {
				bottom_collision_distance = fabs(top - block_bottom);
				if ((min > bottom_collision_distance) || (min == 0.f)) {
					min = bottom_collision_distance;
				}
				//return Moving_Block::rectangle_collision::bottom;
			}
			if ((bottom >= block_top) && (bottom <= block_bottom)) {
				top_collision_distance = fabs(bottom - block_top);
				if ((min > top_collision_distance) || (min == 0.f)) {
					min = top_collision_distance;
				}
				//return Moving_Block::rectangle_collision::top;
			}
		}

		if (min == 0.f) {
			continue;
		}
		if (left_collision_distance == min) {
			collision_block = block.get();
			return Moving_Block::rectangle_collision::left;
		}
		if (top_collision_distance == min) {
			collision_block = block.get();
			return Moving_Block::rectangle_collision::top;
		}
		if (bottom_collision_distance == min) {
			collision_block = block.get();
			return Moving_Block::rectangle_collision::bottom;
		}
		if (right_collision_distance == min) {
			collision_block = block.get();
			return Moving_Block::rectangle_collision::right;
		}
	}
	return no;
}

void Moving_Block::solve_moving_blocks_collision(rectangle_collision state) {
	if (state == no) {
		return;
	}
	set_angle(get_angle() + M_PI);
	collision_block->set_angle(collision_block->get_angle() + M_PI);
	collision_block = NULL;
}


void Moving_Block::solve_blocks_collision(rectangle_collision state) {
	random_device rd;  
	mt19937 gen(rd());  
	uniform_int_distribution<> dist(0, 100);
	switch (state)
	{
	case Moving_Block::no:
		return;
	case Moving_Block::top:
		set_angle(M_PI+dist(gen)/100.f * M_PI);
		return;
	case Moving_Block::right:
		set_angle(-M_PI/2.f + dist(gen) / 100.f * M_PI);
		return;
	case Moving_Block::bottom:
		set_angle(dist(gen) / 100.f * M_PI);
		return;
	case Moving_Block::left:
		set_angle(M_PI / 2.f + dist(gen) / 100.f * M_PI);
		return;
	default:
		break;
	}
}

bool Moving_Block::check_player_collision() {
	if (get_position().y + 3.f * game->player->get_height() > game->player->get_position().y) {
		return true;
	}
	return false;
}

void Moving_Block::solve_player_collsion(bool state) {
	if (state == false) {
		return;
	}
	set_angle(-get_angle());
}