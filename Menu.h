
#include <map>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define MAX_MAIN_MENU 3

#pragma once

class Menu {

public:

	Menu(float width, float height);

	void draw(sf::RenderWindow& windows);

	void moveUp();

	void moveDown();

	void setSelected(int n);

	int mainMenuPressed() {

		return mainMenuSelected;
	}

	~Menu();

private:

	// Menu Window
	sf::RenderWindow* menuWindows; // make new window for menu

	// Font
	sf::Font fonts;
	sf::Font fontss;
	sf::Text meteorite;
	sf::Text myName;
	sf::Text mainMenu[MAX_MAIN_MENU];

	//Background
	sf::Texture backgroundTexs;
	sf::Sprite backgrounds;

	//Logo
	sf::Texture logoTexs;
	sf::Sprite logos;

	int mainMenuSelected;



};

