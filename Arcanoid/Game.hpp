#pragma once


#include"Player.hpp"
#include"Ball.hpp"
#include"Block.hpp"

#define player_velocity 1.3f
#define ball_velocity 0.7f
#define block_velocity 0.2f
#define block_acceleration 0.1f

#define rows 5
#define columns 10

#define border_x 100.f
#define border_y 50.f


class Game {
public:
	unique_ptr<RenderWindow> window;

	unique_ptr<Player> player = make_unique<Player>(player_velocity);
	Texture player_texture;

	//Ball ball = Ball(ball_velocity);
	Texture ball_texture;
	vector<unique_ptr<Ball>> balls;

	list<Block> blocks;
	Texture block_texture;
	Texture accelerating_block_texture;
	vector <Color> block_colors{ Color::Red,Color::Yellow,Color(255,255,255,0) };
	
	Game( unique_ptr<RenderWindow> window);
	~Game() = default;

	void add_bonus();
	void update_objects();
	void move_player(Keyboard::Key key);
	void draw();

	static int run_game();

};