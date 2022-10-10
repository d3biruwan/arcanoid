#pragma once

#include"Player.hpp"
#include"Ball.hpp"

#define player_velocity 15.f
#define ball_velocity 0.4f
#define block_velocity 0.2f
//#define ball_color Color::Cyan


class Game {
public:
	RenderWindow* parent;

	Player player = Player(player_velocity);
	Texture player_texture;

	Ball ball = Ball(ball_velocity);
	Texture ball_texture;
	
	Game( RenderWindow& window);
	~Game() = default;

	void move_objects();
	void move_player(Keyboard::Key key);
	void draw();

	static int run_game();

};