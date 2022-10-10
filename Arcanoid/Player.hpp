#pragma once
#include"Game_object.hpp"

class Player : public Game_object {
public:
	Player(float velocity);
	~Player()=default;

	virtual void set_position();
	virtual void update_state();
	void move_right();
	void move_left();
protected:
	bool can_move_right = true;
	bool can_move_left = true;
};