#include "pch.h"
#include "GameTable.h"
#include "BrickPile.h"
#include "Paddle.h"
#include <vector>
#include <windows.h>

using namespace sf;
using namespace std;

int _HP = 0;

GameTable::GameTable()
{
	RenderWindow app(VideoMode(800, 600), "Arkanoid");
	menu(app);
}


void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("C:/Users/yurin/source/repos/PROJECT_1/Images/images/start.png");
	menuTexture2.loadFromFile("C:/Users/yurin/source/repos/PROJECT_1/Images/images/about.png");
	menuTexture3.loadFromFile("C:/Users/yurin/source/repos/PROJECT_1/Images/images/exit.png");
	aboutTexture.loadFromFile("C:/Users/yurin/source/repos/PROJECT_1/Images/images/i.jpg");
	menuBackground.loadFromFile("C:/Users/yurin/source/repos/PROJECT_1/Images/images/menu.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(40, 120);
	menu2.setPosition(40, 450);
	menu3.setPosition(40, 500);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(40, 120, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(40, 450, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(40, 500, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				isMenu = false;
				window.close();
				getHP();
			}

			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
}

bool isCollide(Sprite s1, Sprite s2) {
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}


void GameRun() {
	_HP--;
	int Score = 0;
	PuckSupply PS(_HP);//кол-во шариков-хр
	BrickPile BP; //Стена
	Paddle puddle1;//Телега
	Puck Puck1;   //Шайба1
	RenderWindow app(VideoMode(800, 600), "Arkanoid!");
	app.setFramerateLimit(60);
	Texture	BG;
	BG.loadFromFile("C:/Users/yurin/source/repos/PROJECT_1/Images/images/background.jpg");

	Sprite background(BG);

	float dx_Paddle = 6;
	bool pusk = true;
	//float dx_Puck = 6;
	//float dy_Puck = 0;

	int n1 = BP.n;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}
		}


		Puck1.move_x();
		for (int i = 0; i <= BP.n; i++) {
			if (isCollide(BP.block[i], Puck1.get())) {
				BP.block[i].setPosition(-100, 0);
				Puck1.dx_Puck = -Puck1.dx_Puck;
				Score = Score + 100;
				cout << "Score: " << Score << endl;
				--n1;

			}
		}

		Puck1.move_y();
		for (int i = 0; i <= BP.n; i++) {
			if (isCollide(BP.block[i], Puck1.get())) {
				BP.block[i].setPosition(-100, 0);
				Puck1.dy_Puck = -Puck1.dy_Puck;
				Score = Score + 100;
				cout << "Score: " << Score << endl;
				--n1;
			}
		}

		Vector2f a = Puck1.get().getPosition();

		if (a.x < 0 || a.x > 770) Puck1.dx_Puck = -Puck1.dx_Puck;   //Пофиксили
		if (a.y < 0 || a.y > 560) Puck1.dy_Puck = -Puck1.dy_Puck;

		Vector2f b = puddle1.getPaddle().getPosition();

		if (n1 == 0) { app.close(); GameWin(); }
		if (a.y > 560)
		{
			if (_HP < 1)
			{
				app.close();
				GameLose();
			}

			_HP--;
			Puck1.dx_Puck = 0;
			Puck1.dy_Puck = 0;
			Puck1.Puck1.setPosition(330, 540);
			puddle1.Paddle1.setPosition(300, 580);
			pusk = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) puddle1.Right();
		if (Keyboard::isKeyPressed(Keyboard::Left)) puddle1.Left();
		if (Keyboard::isKeyPressed(Keyboard::Space)) Sleep(2000);


		if ((pusk == true) and (Keyboard::isKeyPressed(Keyboard::Up))) //Правим
		{
			Puck1.Ball_up();
			pusk = false;
		}

		if ((pusk == true) and (Keyboard::isKeyPressed(Keyboard::Right))) //Чтобы мяч вбок не уходил
		{
			if (a.x < 760) {
				Puck1.Puck1.move(dx_Paddle, 0);
			}
		}

		if ((pusk == true) and (Keyboard::isKeyPressed(Keyboard::Left)))
		{
			if (a.x > 0) {
				Puck1.Puck1.move(-dx_Paddle, 0);
			}
		}

		if (b.x > 705) {    //Попроавили
			puddle1.break_L();
		}

		if (b.x < 0) {    //Поправили
			puddle1.break_R();
		}

		if (isCollide(puddle1.getPaddle(), Puck1.get())) { //Поправили
			Puck1.dy_Puck = -Puck1.dy_Puck;
			//dy_Puck = -dy_Puck;
		}

		app.clear();
		app.draw(background);
		app.draw(Puck1.get());
		app.draw(puddle1.getPaddle());

		for (int i = 0; i < BP.n; i++) {
			app.draw(BP.block[i]);
		}

		app.display();
	}
}

void GameWin() {
	RenderWindow app(VideoMode(800, 600), "You win!");
	Texture BG;

	BG.loadFromFile("C:/Users/yurin/source/repos/PROJECT_1/Images/images/win.jpg");

	Sprite Background(BG);

	while (app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}
		}

		app.clear();
		app.draw(Background);
		app.display();
	}
}


void GameLose() {
	RenderWindow app(VideoMode(800, 600), "You lose!");
	Texture BG;

	BG.loadFromFile("C:/Users/yurin/source/repos/PROJECT_1/Images/images/lose.jpg");

	Sprite Background(BG);

	while (app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}
		}

		app.clear();
		app.draw(Background);
		app.display();
	}
}




GameTable::~GameTable()
{
}

