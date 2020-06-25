#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Puck
{
public:
	float dx_Puck = 0;
	float dy_Puck = 0;

	Sprite Puck1;

	Puck();
	~Puck();

	Sprite get() {
		return Puck1;
	}

	void Ball_up();

	inline void move_x() {	Puck1.move(dx_Puck, 0);}

	inline void move_y() {Puck1.move(0, dy_Puck);}


	friend class BrickPile;
private:

	Texture Puck_Pict;

	int _pos_x;
	int _pos_y;
};
