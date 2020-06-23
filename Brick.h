#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Brick
{
public:
	Brick();
	~Brick();
	
	friend class BrickPile;

private:
	int _size_x;
	int _size_y;
	
	Texture Brick_Pict;

	int _pos_x;
	int _pos_y;
};

