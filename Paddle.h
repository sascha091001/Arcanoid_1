#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Paddle {
public:
	Paddle();
	~Paddle();

	Sprite Paddle1;

	Sprite getPaddle() {
		return Paddle1;
	}

	void Right() {
		Paddle1.move(6, 0);
	}

	void Left() {
		Paddle1.move(-6, 0);
	}

	void break_L() {
		Paddle1.move(-6, 0);
	}

	void break_R() {
		Paddle1.move(6, 0);
	}

private:
	Texture Paddle_Pict;
};
