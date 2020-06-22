#include "pch.h"
#include "Puck.h"



Puck::Puck()
{
	Puck_Pict.loadFromFile("C:\Users\Анастасия\Desktop\Arcanoid_project\puck.png");
	Puck1.setTexture(Puck_Pict);
	Puck1.setPosition(330, 540);
}


Puck::~Puck()
{
}

