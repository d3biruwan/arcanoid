#pragma once
#include"Player.hpp"

#define player_velocity 12.f
#define ball_velocity 12.f
#define block_velocity 12.f


class Game {
public:
	RenderWindow* parent;

	Player player = Player(player_velocity);
	Texture player_texture;
	
	Game( RenderWindow& window);
	~Game() = default;

	void move_objects();
	void move_player(Keyboard::Key key);
	void draw();

	static int run_game();

};