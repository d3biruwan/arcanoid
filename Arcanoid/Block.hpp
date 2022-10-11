#pragma once
#include"Game_object.hpp"

class Block :public Game_object {
public:
	Block() = default;
	virtual void update_state() final {};
private:
	bool destructible = true;
};
