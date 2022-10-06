#pragma once
#include"Player.hpp"

#define player_velocity 5.f

class Game {
public:
	RenderWindow* parent;

	Player player = Player(player_velocity);
	Texture player_texture;
	
	Game( RenderWindow& window);
	void draw();

	static int run_game();

};