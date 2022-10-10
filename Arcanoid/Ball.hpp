#pragma once
#include"Game_object.hpp"
#include"Player.hpp"

class Ball : public Game_object {
public:
	//lifespan
	Ball(float velocity);
	~Ball() = default;
	void set_player(Player& player);

	//drawing
	virtual void set_position();
	
	//movement
	virtual void update_state();
protected:
	//collisions
	virtual void window_collision_solve(screen_collision state) override;
	
	Player* player=NULL;
};