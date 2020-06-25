#pragma once
#include "Brick.h"
#include <vector>
#include "Puck.h"

class BrickPile
{
public:
	BrickPile();
	~BrickPile();


	friend class GameTable;   

	Sprite getBlocks() {
		return *block;
	}

private:
	int n = 0;

	Sprite block[1000];

	Brick *_Brick_Pile;
	int _amount = 50; 
	int _bricks_x = 10;
	int _bricks_y = 5;
};