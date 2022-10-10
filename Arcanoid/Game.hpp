#pragma once
#include"Player.hpp"

#define player_velocity 12.f

class Game {
public:
	RenderWindow* parent;

	Player player = Player(player_velocity);
	Texture player_texture;
	
	Game( RenderWindow& window);

	void move_player(Keyboard::Key key);
	void draw();

	static int run_game();

};