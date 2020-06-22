#include "pch.h"
#include "PuckSupply.h"
#include <iostream>
using namespace std;


PuckSupply::PuckSupply(int HP)
{
	_Puck_arr = new Puck[HP];
	_cnt = HP;
}


PuckSupply::~PuckSupply()
{
	delete[] _Puck_arr;
}



