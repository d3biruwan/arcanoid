#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>	
#include <ctime>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>



using namespace sf;
using namespace std;



class Game_object {
public:
	//lifespan
	Game_object() = default;
	Game_object(float velocity, float angle);
	~Game_object() = default;
	void lose_hp();

	// drawing 
	void set_texture(Texture& texture);
	void set_window(RenderWindow& window);
	virtual	void set_position(float x, float y);
	void set_color(Color);
	virtual void draw();

	// movement
	virtual void update_state()=0;
	void move();

	//get properties
	float get_width();
	float get_height();
	Vector2f get_position();

protected:
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
	// collisions
	screen_collision check_window_collision();
	virtual void solve_window_collision(screen_collision);

	//utility
	static float get_radian_angle(float angle);
	float get_distance_from_point(const Vector2f&);

	//changing properties
	void set_angle(float angle);

	RenderWindow* window = NULL;
	float velocity=0.f;
	float angle = 0.f;
	int hp = 1;
	float x_pos = 0.f, y_pos = 0.f;
	Sprite sprite;

	
};