#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Paddle {
public:
	Paddle();
	~Paddle();

	Sprite getPaddle() {
		return Paddle1;
	}
	Sprite Paddle1;

	inline void Right() {Paddle1.move(6, 0);}

	inline void Left() {Paddle1.move(-6, 0);}

	inline void break_L() {Paddle1.move(-6, 0);}

	inline void break_R() {Paddle1.move(6, 0);}

private:
	Texture Paddle_Pict;
	
};
