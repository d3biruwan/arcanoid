#pragma once
#include"Game_object.hpp"

class Block :public Game_object {
public:
	//lifespan
	Block() = default;
	virtual void on_death() {};

	//movement
	virtual void update_state() final {};
private:
	bool destructible = true;
};
