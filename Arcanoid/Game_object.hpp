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

float distance_between(float, float, float, float);
float distance_between(const Vector2f&, const Vector2f&);

class Game;

class Game_object {
public:
	//lifespan
	Game_object() = default;
	Game_object(float, float);
	~Game_object() = default;
	virtual void lose_hp();
	virtual void on_death() {};
	void set_game(Game&);
	virtual void set_hp(int);

	// drawing 
	void set_texture(Texture&);
	virtual	void set_position(float, float);
	void set_color(const Color&);
	virtual void draw();
	void change_opacity();
	void set_velocity(float);
	void increase_velocity(float);
	void decrease_velocity(float);

	// movement
	virtual void update_state()=0;
	void move();

	//get properties
	const float get_velocity();
	const Color& get_color();
	const int get_hp();
	const float get_width();
	const float get_height();
	const Vector2f& get_position();
	const FloatRect& get_global_bounds();

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
	static float get_radian_angle(float);
	float get_distance_from_point(const Vector2f&);
	float get_distance_from_point(float , float);

	//changing properties
	void set_angle(float);

	Game* game=NULL;
	float velocity=0.f;
	float angle = 0.f;
	int hp = 1;
	float x_pos = 0.f, y_pos = 0.f;
	Sprite sprite;
};