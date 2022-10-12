#pragma once
#include"Game_object.hpp"

class Block :public Game_object {
public:
	//lifespan
	explicit Block()=default;
	Block(int);
	Block(bool,int);
	Block(const vector <Color>&,int);
	virtual void lose_hp();
	virtual void on_death();
	void set_blocks(list<Block>&);
	void set_list_position(int);
	//virtual void set_hp(int) override;

	//drawing
	void set_colors_vec(const vector<Color>&);

	//movement
	virtual void update_state() final {};

	//properties
	const int get_list_position();
private:
	int list_pos = 0;
	bool destructible = true;
	const vector <Color>* colors;
	list<Block>* blocks = NULL;
};
