#pragma once
#include"Game_object.hpp"

class Block :public Game_object {
public:
	//lifespan
	explicit Block()=default;
	Block(int);
	Block(bool,int);
	virtual void lose_hp();
	virtual void on_death();
	void set_list_position(int);
	void make_accelerating(float, Texture&);
	
	//drawing

	//movement
	virtual void update_state() final {};

	//properties
	const float get_accelertaion();
	const int get_list_position();
private:
	int list_pos = 0;
	float acceleration = 0.f;
	bool destructible = true;
	bool accelerating = false;
	const vector <Color>* colors;
};
