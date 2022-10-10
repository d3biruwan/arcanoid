#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>	
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>



using namespace sf;
using namespace std;


class Game_object {
public:
	Game_object() = default;
	Game_object(float velocity, double angle);
	~Game_object() = default;

	// Отрисовка 
	void set_texture(Texture& texture);
	void set_window(RenderWindow& window);
	virtual	void set_position(double x, double y);
	void draw();

	// Движение
	void move();

protected:
	RenderWindow* window;
	float velocity=0.0;
	double angle = 0.0;
	int hp = 1;
	double x_pos = 0, y_pos = 0;
	Sprite sprite;

	double get_radian_angle(double angle);
};