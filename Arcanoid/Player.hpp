#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player {
public:
	double velocity;
	//double size;
	int hp = 3;
	double x_pos, y_pos;
	Sprite sprite;

	//Player(double velocity, double size, RenderWindow& window, Texture& texture);
	Player(float velocity);
	~Player() = default;

	// Отрисовка 
	void set_texture(Texture& texture);
	void set_position(RenderWindow& window);
	void draw(RenderWindow& window);

	// Движение
	void move_left();
	void move_right();

};