#pragma once
#include"Game_object.hpp"




class Block :public Game_object {
public:
	//lifespan
	Block()=default;
	Block(int);
	Block(bool,int);

	virtual void lose_hp() override;
	virtual void on_death() override;
	void set_list_position(int);
	void make_accelerating(float, Texture&);
	
	//drawing
	
	//movement
	virtual void update_state() {};

	//properties
	const float get_accelertaion();
	const int get_list_position();
private:
	int list_pos = 0;
	float acceleration = 0.f;
	bool destructible = true;
	bool accelerating = false;
};


class Moving_Block : public Block {
public:
	Moving_Block() = default;
	Moving_Block( float, Game&);
	virtual void on_death() override;
	virtual void update_state() override;

	void set_position();
protected:
	enum rectangle_collision {
		no,
		top,
		right,
		bottom,
		left
	};

	bool check_player_collision();
	void solve_player_collsion(bool);
	rectangle_collision check_moving_blocks_collision();
	void solve_moving_blocks_collision(rectangle_collision);
	//template<typename type>
	rectangle_collision check_blocks_collision();
	void solve_blocks_collision(rectangle_collision);

	Moving_Block* collision_block = NULL;
};