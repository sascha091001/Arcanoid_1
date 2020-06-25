#include "pch.h"
#include "Velocity.h"

Velocity::Velocity()
{
}


Velocity::~Velocity()
{
}

float Velocity::Change_Dir(float speed)
{
	_speed = -speed;
	return _speed;
}
