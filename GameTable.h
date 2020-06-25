#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "BrickPile.h"
#include "PuckSupply.h"
#include "Paddle.h"
#include "Puck.h"

using namespace sf;

class GameTable
{
public:
	GameTable();
	~GameTable();

	void menu(RenderWindow & window);
	void GameRun();
	void GameWin();
	void GameLose();
	void getHP();

private:

};


