#include "pch.h"
#include "GameTable.h"
#include "BrickPile.h"
#include <vector>
#include <windows.h>

using namespace sf;
using namespace std;

int _HP = 0;

GameTable::GameTable()
{
	RenderWindow app(VideoMode(800, 600), "Gorshkonoid!");
	menu(app);
}


void GameTable::menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("E:/pictures/start.png");
	menuTexture2.loadFromFile("E:/pictures/about.png");
	menuTexture3.loadFromFile("E:/pictures/exit.png");
	aboutTexture.loadFromFile("E:/pictures/aboutBackground.png");
	menuBackground.loadFromFile("E:/pictures/menu.png");
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
			//	GameRun();
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


void GameTable::GameRun() {
	_HP--;
	int Score = 0;
	bool pause = false;
	PuckSupply PS(_HP);
	BrickPile BP; 
	Paddle puddle1;
	Puck Puck1;   
	RenderWindow app(VideoMode(800, 600), "Gorshkonoid!");
	app.setFramerateLimit(60);
	Texture	BG;
	BG.loadFromFile("E:/pictures/background.jpg");

	Sprite background(BG);

	float dx_Paddle = 6;
	bool pusk = true;

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

			if (a.x < 0 || a.x > 770) Puck1.dx_Puck = -Puck1.dx_Puck;  
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
			if (Keyboard::isKeyPressed(Keyboard::Space)) 
			{
				pause = true;
				while (pause == true)
				{
					Sleep(2000);
					if (Keyboard::isKeyPressed(Keyboard::P))
					{
						pause = false;
						break;
					}
				}

			}


			if ((pusk == true) and (Keyboard::isKeyPressed(Keyboard::Up))) 
			{
				Puck1.Ball_up();
				pusk = false;
			}

			if ((pusk == true) and (Keyboard::isKeyPressed(Keyboard::Right)))
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

			if (b.x > 705) {    
				puddle1.break_L();
			}

			if (b.x < 0) {    
				puddle1.break_R();
			}

			if (isCollide(puddle1.getPaddle(), Puck1.get())) { 
				Puck1.dy_Puck = -Puck1.dy_Puck;
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


void GameTable::GameWin() {
	RenderWindow app(VideoMode(800, 600), "You win!");
	Texture BG;

	BG.loadFromFile("E:/pictures/win.png");

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


void GameTable::GameLose() {
	RenderWindow app(VideoMode(800, 600), "You lose!");
	Texture BG;

	BG.loadFromFile("E:/pictures/lose.png");

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

void GameTable::getHP() {
	RenderWindow app(VideoMode(800, 600), "Choose a HP amount");
	Texture BG;
	Texture B1, B2, B3, B4, B5;
	B1.loadFromFile("E:/pictures/1hp.png");
	B2.loadFromFile("E:/pictures/2hp.png");
	B3.loadFromFile("E:/pictures/3hp.png");
	B4.loadFromFile("E:/pictures/4hp.png");
	B5.loadFromFile("E:/pictures/5hp.png");
	BG.loadFromFile("E:/pictures/backgroundHP.jpg");
	Sprite But1(B1), But2(B2), But3(B3), But4(B4), But5(B5), Back(BG);
	bool isMenu = 1;
	int butNum = 0;
	But1.setPosition(40, 400);
	But2.setPosition(200, 400);
	But3.setPosition(360, 400);
	But4.setPosition(520, 400);
	But5.setPosition(680, 400);

	while (isMenu)
	{
		But1.setColor(Color::White);
		But2.setColor(Color::White);
		But3.setColor(Color::White);
		But4.setColor(Color::White);
		But5.setColor(Color::White);
		butNum = 0;
		app.clear(Color(129, 181, 221));

		if (IntRect(40, 400, 70, 70).contains(Mouse::getPosition(app))) { But1.setColor(Color::Blue); butNum = 1; }
		if (IntRect(200, 400, 70, 70).contains(Mouse::getPosition(app))) { But2.setColor(Color::Blue); butNum = 2; }
		if (IntRect(360, 400, 70, 70).contains(Mouse::getPosition(app))) { But3.setColor(Color::Blue); butNum = 3; }
		if (IntRect(520, 400, 70, 70).contains(Mouse::getPosition(app))) { But4.setColor(Color::Blue); butNum = 4; }
		if (IntRect(680, 400, 70, 70).contains(Mouse::getPosition(app))) { But5.setColor(Color::Blue); butNum = 5; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (butNum == 1) {
				isMenu = false;
				app.close();
				_HP = 1;
				GameRun();
			}

			if (butNum == 2) {
				isMenu = false;
				app.close();
				_HP = 2;
				GameRun();
			}
			if (butNum == 3) {
				isMenu = false;
				app.close();
				_HP = 3;
				GameRun();
			}
			if (butNum == 4) {
				isMenu = false;
				app.close();
				_HP = 4;
				GameRun();
			}
			if (butNum == 5) {
				isMenu = false;
				app.close();
				_HP = 5;
				GameRun();
			}
		}

		app.draw(Back);
		app.draw(But1);
		app.draw(But2);
		app.draw(But3);
		app.draw(But4);
		app.draw(But5);
		app.display();
	}
}


GameTable::~GameTable()
{
}

