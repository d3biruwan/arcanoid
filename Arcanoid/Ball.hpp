#pragma once
#include"Game_object.hpp"

class Ball : public Game_object {
public:
	Ball(float velocity);
	~Ball() = default;

	virtual void set_position();
	//virtual void draw() override;

};