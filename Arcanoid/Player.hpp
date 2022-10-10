#include"Game_object.hpp"

class Player : public Game_object {
public:
	Player(float velocity);
	~Player()=default;

	virtual void set_position();
	void move_right();
	void move_left();

};