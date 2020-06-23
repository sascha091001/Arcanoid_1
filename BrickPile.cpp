#include "pch.h"
#include "BrickPile.h"
#include <SFML/Graphics.hpp>

using namespace sf;

BrickPile::BrickPile()
{
	_Brick_Pile = new Brick[_amount];

	for (int i = 1; i <= _bricks_x; i++) {
		for (int j = 2; j <= _bricks_y + 1; j++) {
			block[n].setTexture(_Brick_Pile[n].Brick_Pict);
			block[n].setPosition(i * 63, j * 30);
			n++;
		}
	}
}


BrickPile::~BrickPile()
{
	delete[] _Brick_Pile;
}


void BrickPile::Destroy(Puck p) {
	for (int i = 0; i < _amount; i++) {
		if (p._pos_x == _Brick_Pile[i]._pos_x || p._pos_y == _Brick_Pile[i]._pos_y) {
			delete &_Brick_Pile[i];
		}
	}
}