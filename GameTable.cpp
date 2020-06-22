#include "pch.h"
#include "GameTable.h"
#include "BrickPile.h"
#include <vector>
#include <windows.h>

using namespace sf;
using namespace std;

GameTable::GameTable()
{
	RenderWindow app(VideoMode(800, 600), "Alex!");
	menu(app);
}

void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/start.png");
	menuTexture2.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/about.png");
	menuTexture3.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/exit.png");
	aboutTexture.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/i.jpg");
	menuBackground.loadFromFile("C:/Users/Alex/source/repos/Arcanoid_Project/Arcanoid_Project/images/menu.png");
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