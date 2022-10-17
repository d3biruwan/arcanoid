#pragma once
#include"Game_object.hpp"


class Bonus_item: public Game_object {
public:
	//lifespan
	Bonus_item() = default;
	Bonus_item(Game&, Texture&, float, float, float);
	~Bonus_item() = default;
	virtual void on_death() override;

	// movement
	virtual void update_state() override;
	
	//properties
	const int get_vec_position();
protected:
	void set_vec_position(const int);
	//collisions
	bool check_player_collision();
	void solve_player_collision(bool);
	virtual void solve_window_collision(screen_collision) override;

private:
	int vec_pos = 0;
};