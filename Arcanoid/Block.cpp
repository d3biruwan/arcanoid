#include"Block.hpp"

//lifespan
Block::Block(int pos) {
	set_list_position(pos);
}

Block::Block(const vector <Color>& vec,int pos) {
	set_colors_vec(vec);
	set_list_position(pos);
}

Block::Block(bool destructible, int pos){
	this->destructible = destructible;
	set_list_position(pos);
}

void Block::set_list_position(int pos) {
	list_pos = pos;
}

void Block::set_blocks(list<Block>& blocks) {
	this->blocks = &blocks;
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
	set_color(colors->at(hp-1));
}

void Block::on_death() {
	for (Block& block : *blocks) {
		if (get_list_position() < block.get_list_position()) {
			block.set_list_position(block.get_list_position() - 1);
		}
	}
	auto iter = blocks->begin();
	for (int i = 0; i < get_list_position(); i++, ++iter);
	auto temp_iter = iter++;
	blocks->erase(temp_iter);
}

//void Block::set_hp(int hp) {
//	Game_object::set_hp(hp);
//
//}

//drawing
void Block::set_colors_vec(const vector<Color>& vec) {
	colors = &vec;
}

//properties
const int Block::get_list_position() {
	return list_pos;
}