#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>	
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>



using namespace sf;
using namespace std;


enum screen_collision {
	no,
	top,
	right,
	bottom,
	left,
	top_right,
	bottom_right,
	bottom_left,
	top_left
};

class Game_object {
public:
	//lifespan
	Game_object() = default;
	Game_object(float velocity, double angle);
	~Game_object() = default;
	void lose_hp();

	// drawing 
	void set_texture(Texture& texture);
	void set_window(RenderWindow& window);
	virtual	void set_position(double x, double y);
	virtual void draw();

	// movement
	virtual void update_state()=0;
	void move();

protected:
	// collisions
	screen_collision check_window_collision();
	virtual void window_collision_solve(screen_collision state);

	//utility
	double get_radian_angle(double angle);

	RenderWindow* window;
	float velocity=0.0;
	double angle = 0.0;
	int hp = 1;
	double x_pos = 0, y_pos = 0;
	Sprite sprite;

	
};