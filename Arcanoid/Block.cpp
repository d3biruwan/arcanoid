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
	if (hp == 0) {
		on_death();
		return;
	}
	set_color(game->block_colors.at(hp-1));
}

void Block::on_death() {
	for (auto& block : game->blocks) {
		if (get_list_position() < block->get_list_position()) {
			block->set_list_position(block->get_list_position() - 1);
		}
	}

	auto bonus = make_unique<Bonus_item>(*(this->game), this->game->bonus_texture, get_position().x, get_position().y, block_velocity);
	game->bonuses.push_back(std::move(bonus));
	
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