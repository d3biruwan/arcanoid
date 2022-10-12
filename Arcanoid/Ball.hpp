#pragma once
#include"Game_object.hpp"
#include"Player.hpp"
#include"Block.hpp"



class Ball : public Game_object {
public:
	//lifespan
	Ball(float velocity);
	~Ball() = default;
	void set_player(Player&);
	void set_blocks(list<Block>&);
	virtual void lose_hp();
	virtual void on_death();

	//drawing
	virtual void set_position();
	
	//movement
	virtual void update_state();
protected:
	//collisions
	enum rectangle_collision {
		no,
		top,
		right,
		bottom,
		left
	};

	virtual void solve_window_collision(screen_collision) override;
	bool check_player_collision();
	void solve_player_collision(bool player_collision_state);
	rectangle_collision check_block_collision();
	void solve_blocks_collision(rectangle_collision);
	void reset_collision();
	void set_last_collison(rectangle_collision);
	
	rectangle_collision last_collison = no;
	Player* player=NULL;
	list<Block>* blocks = NULL;
};