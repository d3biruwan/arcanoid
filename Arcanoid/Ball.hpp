#pragma once
#include"Game_object.hpp"
#include"Player.hpp"
#include"Block.hpp"



class Ball : public Game_object {
public:
	//lifespan
	Ball(float, Game&);
	~Ball() = default;
	virtual void lose_hp();
	virtual void on_death();

	//drawing
	virtual void set_position();
	void flash_animation();

	//movement
	virtual void update_state();

	//properties
	const int get_list_position();
protected:
	//collisions
	enum rectangle_collision {
		no,
		top,
		right,
		bottom,
		left
	};

	struct speed_boost{
		Clock timer;
		float acceleration;
	};

	virtual void solve_window_collision(screen_collision) override;
	bool check_player_collision();
	void solve_player_collision(bool player_collision_state);
	template<typename T>
	rectangle_collision check_block_collision(vector<T>&);
	void solve_blocks_collision(rectangle_collision);
	bool check_balls_collision();
	void solve_balls_collsion(bool);
	void reset_collision();
	void set_last_collison(rectangle_collision);
	void get_speed_boost(float);
	void clear_boosts();
	
	void set_list_position(const int);
	int list_position;
	rectangle_collision last_collison = no;

	Ball* collision_ball = NULL;

	Block* collision_block = NULL;
	vector<speed_boost> boosts;
};