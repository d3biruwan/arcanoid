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
	Player(double velocity);
	void set_texture(Texture& texture);
	void set_position(RenderWindow& window);
	~Player() = default;
	void draw(RenderWindow& window);

};