#pragma once
class Velocity
{
public:
	Velocity();
	~Velocity();
	float Change_Dir(float speed);
	friend class GameTable;
private:
	float _speed;
};