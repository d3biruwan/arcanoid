#include"Bonus_item.hpp"
#include"Game.hpp"

//lifespan
Bonus_item::Bonus_item(Game& game, Texture& texture, float x, float y, float velocity) {
	set_game(game);
	set_velocity(velocity);
	set_angle(get_radian_angle(90.f));
	set_position(x, y);
	set_texture(texture);
	if (this->game->bonuses.empty() == true) {
		set_vec_position(0);
	}
	else {
		set_vec_position(this->game->bonuses.size());
	}
}

void Bonus_item::on_death() {
	for (auto& bonus : game->bonuses) {
		if (bonus->get_vec_position() > get_vec_position()) {
			bonus->set_vec_position(bonus->get_vec_position() - 1);
		}
	}
	game->bonuses.erase(game->bonuses.cbegin()+ get_vec_position());
}

// movement
void Bonus_item::update_state() {
	bool pl_col = check_player_collision();
	solve_player_collision(check_player_collision());
	if (pl_col) {
		return;
	}
	solve_window_collision(check_window_collision());
}


//collisions
void Bonus_item::solve_window_collision(screen_collision state) {
	switch (state)
	{
	case Game_object::bottom:
		on_death();
		break;
	default:
		break;
	}
}

bool Bonus_item::check_player_collision() {
	float left_boundary = -get_width() / 2.f + get_position().x;
	float top_boundary = -get_height() / 2.f + get_position().y;
	float right_boundary = get_width() / 2.f + get_position().x;
	float bottom_boundary = get_height() / 2.f + get_position().y;

	float p_left_boundary = -game->player->get_width() / 2.f + game->player->get_position().x;
	float p_top_boundary = -game->player->get_height() / 2.f + game->player->get_position().y;
	float p_right_boundary = game->player->get_width() / 2.f + game->player->get_position().x;
	float p_bottom_boundary = game->player->get_height() / 2.f + game->player->get_position().y;

	if ((top_boundary<=p_bottom_boundary)&&(bottom_boundary>=p_top_boundary)) {
		if ((right_boundary >= p_left_boundary) && (left_boundary <= p_right_boundary)) {
			return true;
		}
	}
	else {
		return false;
	}


	/*if (get_global_bounds().intersects(game->player->get_global_bounds())==true) {
		return true;
	}
	else {
		return false;
	}*/
}

void Bonus_item::solve_player_collision(bool state) {
	if (state == true) {
		game->add_bonus();
		on_death();
	}
}

//properties

const int Bonus_item::get_vec_position() {
	return vec_pos;
}

void Bonus_item::set_vec_position(const int pos) {
	vec_pos = pos;
}
