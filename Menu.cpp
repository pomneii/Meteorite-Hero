
#include "Menu.h"

Menu::Menu(float width, float height) {

	//Load fonts
	if (!this->fonts.loadFromFile("font/Valorax-lg25V.otf")) {

		std::cout << "ERROR::GAME::Failed to load fonts" << "\n";

	}

	//Load fontss
	if (!this->fontss.loadFromFile("font/Chainwhacks-vm72E.ttf")) {

		std::cout << "ERROR::GAME::Failed to load fontss" << "\n";
	}

	// Background mainmenu
	if (!backgroundTexs.loadFromFile("image/mainmenu.png")) {

		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	backgrounds.setTexture(backgroundTexs);
	backgrounds.setScale(4.5f, 4.5f);

	// Logo mainmenu
	if (!logoTexs.loadFromFile("image/logo.png")) {

		std::cout << "ERROR::GAME::COULD MOT LOAD LOGO TEXTURE" << "\n";
	}

	logos.setTexture(logoTexs);
	logos.setScale(sf::Vector2f(3.5f, 3.5f));
	logos.setPosition(237.f, 267.f);

	// METEORITE HERO
	this->meteorite.setPosition(102.f, 100.f);
	this->meteorite.setFont(this->fontss);
	this->meteorite.setCharacterSize(50);
	this->meteorite.setFillColor(sf::Color::White);
	this->meteorite.setString("METEORITE HERO");

	// PLAY
	this->mainMenu[0].setPosition(223.f, 500.f);
	this->mainMenu[0].setFont(this->fonts);
	this->mainMenu[0].setCharacterSize(40);
	this->mainMenu[0].setFillColor(sf::Color::White);
	this->mainMenu[0].setString("PLAY");

	// LEADERBOARD
	this->mainMenu[1].setPosition(106.f, 600.f);
	this->mainMenu[1].setFont(this->fonts);
	this->mainMenu[1].setCharacterSize(40);
	this->mainMenu[1].setFillColor(sf::Color::White);
	this->mainMenu[1].setString("LEADERBOARD");

	//EXIT
	this->mainMenu[2].setPosition(236.f, 700.f);
	this->mainMenu[2].setFont(this->fonts);
	this->mainMenu[2].setCharacterSize(40);
	this->mainMenu[2].setFillColor(sf::Color::White);
	this->mainMenu[2].setString("EXIT");

	// My Name
	this->myName.setPosition(105.f, 800.f);
	this->myName.setFont(this->fontss);
	this->myName.setCharacterSize(22);
	this->myName.setFillColor(sf::Color::Cyan);
	this->myName.setString("66010733   Woranuch  Pluengnuch");

	mainMenuSelected = 0;
}

Menu::~Menu() {


}

void Menu::draw(sf::RenderWindow& windows) {

	windows.draw(backgrounds);

	windows.draw(logos);

	windows.draw(meteorite);

	for (int i = 0; i < MAX_MAIN_MENU; ++i) {

		windows.draw(mainMenu[i]);
	}

	windows.draw(myName);
}

void Menu::moveUp() {

	if (this->mainMenuSelected - 1 >= -1) {

		this->mainMenu[this->mainMenuSelected].setFillColor(sf::Color::White);

		mainMenuSelected--;

		if (this->mainMenuSelected == -1) {
			this->mainMenuSelected = 2;
		}

		this->mainMenu[this->mainMenuSelected].setFillColor(sf::Color::Green);
	}
}

void Menu::moveDown() {

	if (this->mainMenuSelected + 1 <= MAX_MAIN_MENU) {

		this->mainMenu[this->mainMenuSelected].setFillColor(sf::Color::White);

		mainMenuSelected++;

		if (this->mainMenuSelected == 3) {

			this->mainMenuSelected = 0;
		}

		this->mainMenu[this->mainMenuSelected].setFillColor(sf::Color::Green);
	}
}

void Menu::setSelected(int n) {

	mainMenuSelected = n;
}
