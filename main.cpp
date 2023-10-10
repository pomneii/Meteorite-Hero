
#include "Menu.h"
#include <time.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

struct Player {

	int point = 0;
	int health = 10;
	sf::Sprite player;
	int arm = 10;
};

struct Enemy {

	sf::Sprite enemy;
	float speed = 0;
};

struct Bullet {

	sf::Sprite bulletSp;
	float speed = 0.45f;
	bool active;
};

struct History {

	std::string namelead;
	int scorelead = 0;
};

int pageNum = 100;
float playerSpeed = 0.5f;
const int maxBullets = 10;
std::string name;
int score = 0;
bool heart = false;
bool armor = false;

bool compareScores(const History& a, const History& b) {
	return a.scorelead > b.scorelead;
}

sf::Vector2f getFloatRectCenter(sf::FloatRect floatrect) {

	return sf::Vector2f(floatrect.width / 2, floatrect.height / 2);
}

void textSetOriginCenter(sf::Text& text) {

	text.setOrigin(getFloatRectCenter(text.getLocalBounds()));
}

void Pname(sf::RenderWindow& window, std::string& name);

void game_Over(sf::RenderWindow& window);

void game_Play(sf::RenderWindow& window);

void His(sf::RenderWindow& window);

void game_Win(sf::RenderWindow& window);

int main() {

	srand(static_cast<unsigned>(time(nullptr)));

	sf::RenderWindow window(sf::VideoMode(570, 870), "METEORITE HERO", sf::Style::Close | sf::Style::Titlebar);

	Menu mainMenu(window.getSize().x, window.getSize().y);

	sf::Texture leadBg;
	sf::Sprite leaderBg;

	if (!leadBg.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\mainmenu.png")) {

		std::cout << "ERROR::GAME::COULD NOT LOAD THE BACKGROUND OF LEADERBOARD" << "\n";
	}

	leaderBg.setTexture(leadBg);
	leaderBg.setScale(4.5f, 4.5f);

	while (true) {

		if (pageNum == 100) {

			while (window.isOpen()) {

				sf::Event events;
				while (window.pollEvent(events)) {

					if (events.type == sf::Event::Closed) {
						window.close();
					}

					if (events.Event::KeyPressed) {

						if (events.key.code == sf::Keyboard::Down) {

							mainMenu.moveUp();
							break;
						}

						if (events.key.code == sf::Keyboard::Up) {

							mainMenu.moveDown();
							break;
						}

						if (events.key.code == sf::Keyboard::Return) {

							if (mainMenu.mainMenuPressed() == 0) {

								pageNum = 0;
							}

							if (mainMenu.mainMenuPressed() == 1) {

								pageNum = 5;
							}

							if (mainMenu.mainMenuPressed() == 2) {

								pageNum = -1;
							}
						}
					}
				}

				window.clear();
				if (pageNum != 100) {

					break;
				}
				window.draw(leaderBg);
				mainMenu.draw(window);
				window.display();
			}
		}

		if (pageNum == -1) {

			window.close();
			break;
		}

		if (pageNum == 0) {

			Pname(window, name);

		}
		if (pageNum == 5) {

			His(window);
		}

		if (pageNum == 3) {

			game_Play(window);
		}

		if (pageNum == 4) {

			game_Over(window);
		}

		if (pageNum == 6) {

			game_Win(window);
		}
	}

	return 0;
}

void Pname(sf::RenderWindow& window, std::string& name) {

	if (!name.empty()) {

		name.clear();
	}

	sf::Texture backG;
	backG.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\mainmenu.png");
	sf::Sprite bG;
	bG.setTexture(backG);
	bG.setScale(4.5f, 4.5f);

	sf::Font Fontss;
	Fontss.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\font\\DebugFreeTrial-MVdYB.otf");

	sf::Text inputName;
	inputName.setFont(Fontss);
	inputName.setString("Enter your name");
	inputName.setCharacterSize(50);
	inputName.setPosition((window.getSize().x / 2.f) - (inputName.getGlobalBounds().width / 2.f), 250.f);
	inputName.setFillColor(sf::Color::Cyan);

	sf::Text nameofPlayer;
	nameofPlayer.setFont(Fontss);
	nameofPlayer.setFillColor(sf::Color::Magenta);
	textSetOriginCenter(nameofPlayer);
	nameofPlayer.setPosition(220.f, 400.f);
	nameofPlayer.setCharacterSize(50);

	sf::Text startGame_Text;
	startGame_Text.setFont(Fontss);
	startGame_Text.setString("Press  Enter  to start the game!");
	startGame_Text.setFillColor(sf::Color::Yellow);
	startGame_Text.setCharacterSize(40);
	startGame_Text.setPosition((window.getSize().x / 2.f) - (startGame_Text.getGlobalBounds().width / 2.f), 700.f);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed()) {

				window.close();
			}

			if (event.type == sf::Event::TextEntered) {

				name += static_cast <char> (event.text.unicode);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && name.size() > 0) {

				name.resize(name.size() - 1);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && name.size() > 1) {

				pageNum = 3;
				return;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

				pageNum = 100;
				return;
			}
		}

		nameofPlayer.setString(name);
		textSetOriginCenter(nameofPlayer);
		nameofPlayer.setPosition(285.f, 400.f);

		window.clear();
		window.draw(bG);
		window.draw(inputName);
		window.draw(startGame_Text);
		window.draw(nameofPlayer);
		window.display();
	}
}

void game_Play(sf::RenderWindow& window) {

	sf::Texture gameBg_Tex;
	gameBg_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\background.png");
	sf::Sprite gameBg_Sprite;
	gameBg_Sprite.setTexture(gameBg_Tex);

	sf::Texture worldBg_Tex;
	worldBg_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\world.png");
	sf::Sprite worldBg_Sprite;
	worldBg_Sprite.setTexture(worldBg_Tex);
	worldBg_Sprite.setScale(sf::Vector2f(0.5f, 0.5f));
	worldBg_Sprite.setPosition(147.f, 696.f);

	sf::Texture player_Tex;
	player_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\ship.png");
	Player player1;
	player1.player.setTexture(player_Tex);
	player1.player.setScale(2.f, 2.f);
	player1.player.setPosition(250.f, 480.f);
	
	sf::Texture bullet_Tex;
	bullet_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\bullet.png");
	Bullet bullets[15];

	for (int i = 0; i < 10; i++) {

		bullets[i].active = false;
		bullets[i].bulletSp.setTexture(bullet_Tex);
		bullets[i].bulletSp.setScale(0.7f, 0.7f);
		bullets[i].bulletSp.setPosition(-20.f, -20.f);
	}

	sf::Texture asteriod_Tex;
	asteriod_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\asteroid.png");
	Enemy enemy[7];

	for (int i = 0; i < 7; i++) {

		enemy[i].enemy.setTexture(asteriod_Tex);
		enemy[i].speed = (rand() % 2 + 1) / 7.0;
		enemy[i].enemy.setScale(i * 0.3, i * 0.3);
		int x = (rand() % 460) + 15;
		enemy[i].enemy.setPosition(x, 0.f);
	}

	sf::Texture heart_Tex;
	heart_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\heart.png");
	sf::Sprite heart_Sprite;
	heart_Sprite.setTexture(heart_Tex);
	heart_Sprite.setScale(0.085f, 0.085f);
	heart_Sprite.setPosition(5.f, 15.f);

	sf::Texture arm_Tex;
	arm_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\armor.png");
	sf::Sprite arm_Sprite;
	arm_Sprite.setTexture(arm_Tex);
	arm_Sprite.setScale(0.3f, 0.3f);
	arm_Sprite.setPosition(5.f, 55.f);
	
	sf::Texture healthhelp_Tex;
	healthhelp_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\heart.png");
	sf::Sprite healthhelp_Sprite;
	healthhelp_Sprite.setTexture(healthhelp_Tex);
	healthhelp_Sprite.setScale(0.1f, 0.1f);

	sf::Texture armorhelp_Tex;
	armorhelp_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\armor.png");
	sf::Sprite armorhelp_Sprite;
	armorhelp_Sprite.setTexture(armorhelp_Tex);
	armorhelp_Sprite.setScale(0.3f, 0.3f);

	sf::Font font;
	font.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\font\\Valorax-lg25V.otf");
	sf::Text health_Text;
	sf::String health_String = std::to_string(player1.health);
	health_Text.setFont(font);
	health_Text.setString("Health : " + health_String);
	health_Text.setFillColor(sf::Color::Red);
	health_Text.setPosition(45.f, 15.f);
	health_Text.setScale(0.9f, 0.9f);

	sf::Text point_Text;
	sf::String point_String = std::to_string(player1.point);
	point_Text.setFont(font);
	point_Text.setString("Points : " + point_String);
	point_Text.setFillColor(sf::Color::Green);
	point_Text.setPosition(345.f, 15.f);
	point_Text.setScale(0.9f, 0.9f);

	sf::Text arm_Text;
	sf::String arm_String = std::to_string(player1.arm);
	arm_Text.setFont(font);
	arm_Text.setString("Armor : " + arm_String);
	arm_Text.setFillColor(sf::Color::Cyan);
	arm_Text.setPosition(45.f, 55.f);
	arm_Text.setScale(0.9f, 0.9f);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

				window.close();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				std::cout << mousePos.x << " " << mousePos.y << "\n";
			}
		}

		// width and height of this window
		float windowWidth = static_cast<float>(window.getSize().x);
		float windowHeight = static_cast<float>(window.getSize().y);

		// width and height of player
		float playerWidth = player1.player.getGlobalBounds().width;
		float playerHeight = player1.player.getGlobalBounds().height;
		
		if (player1.player.getPosition().x < 0) {
			player1.player.setPosition(0, player1.player.getPosition().y);
		}
		if (player1.player.getPosition().x + playerWidth > windowWidth) {
			player1.player.setPosition(windowWidth - playerWidth, player1.player.getPosition().y);
		}
		if (player1.player.getPosition().y < 0) {
			player1.player.setPosition(player1.player.getPosition().x, 0);
		}
		if (player1.player.getPosition().y + playerHeight > windowHeight) {
			player1.player.setPosition(player1.player.getPosition().x, windowHeight - playerHeight);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player1.player.move(-playerSpeed, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player1.player.move(playerSpeed, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player1.player.move(0.f, -playerSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player1.player.move(0.f, playerSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			
			for (int i = 0; i < maxBullets; i++) {
				if (!bullets[i].active) {
					bullets[i].active = true;
					bullets[i].bulletSp.setPosition(player1.player.getPosition().x + playerWidth / 2, player1.player.getPosition().y);
					break;  
				}
			}
		}

		for (int i = 0; i < maxBullets; i++) {
			if (bullets[i].active) {
				bullets[i].bulletSp.move(0.f, -bullets[i].speed);
				
				if (bullets[i].bulletSp.getPosition().y < -25) {
					bullets[i].active = false;
				}
			}
		}

		for (int i = 0; i < maxBullets; i++) {
			if (bullets[i].active) {
				for (int j = 0; j < 7; j++) {
					if (bullets[i].bulletSp.getGlobalBounds().intersects(enemy[j].enemy.getGlobalBounds())) {
						bullets[i].active = false;
						player1.point += 2;

						bullets[i].bulletSp.setPosition(-100.f, -100.f);

						int x = (rand() % 551) + 5;
						enemy[j].enemy.setPosition(x, 0.f);
						enemy[j].speed = (rand() % 2 + 1) / 7.0;
					}
				}
			}
		}

		for (int i = 0; i < 7; i++) {

			enemy[i].enemy.move(0.f, enemy[i].speed);

			if (enemy[i].enemy.getPosition().y > 870) {

				int x = (rand() % 460) + 15;
				enemy[i].enemy.setPosition(x, 0.f);
				enemy[i].speed = (rand() % 2 + 1) / 7.0;
				player1.arm--;
			}

			if (player1.player.getGlobalBounds().intersects(enemy[i].enemy.getGlobalBounds())) {

				int x = (rand() % 460) + 15;
				enemy[i].enemy.setPosition(x, 0.f);
				enemy[i].speed = (rand() % 2 + 1) / 7.0;
				player1.health--;
			}
		}

		health_String = std::to_string(player1.health);
		health_Text.setString("Health : " + health_String);

		point_String = std::to_string(player1.point);
		point_Text.setString("Points : " + point_String);

		arm_String = std::to_string(player1.arm);
		arm_Text.setString("Armor : " + arm_String);

		if (player1.health <= 0 || player1.arm <= 0) {

			score = player1.point;
			std::ofstream offile;
			offile.open("history.txt", std::ios::app);
			offile << name << "," << player1.point << std::endl;
			offile.close();
			pageNum = 4;
			return;
		}

		if (player1.point >= 1000) {

			score = player1.point;
			std::ofstream offile;
			offile.open("history.txt", std::ios::app);
			offile << name << "," << player1.point << std::endl;
			offile.close();
			pageNum = 6;
			return;
		}

		if (player1.point > 0 && player1.point % 100 == 0 && heart == false) {

			healthhelp_Sprite.setPosition((rand() % 415) + 65, (rand() % 470) + 200);
			heart = true;
		}
		
		if (player1.point > 0 && player1.point % 200 == 0 && armor == false) {

			armorhelp_Sprite.setPosition((rand() % 415) + 65, (rand() % 470) + 200);
			armor = true;
		}

		if (player1.point >= 300 && player1.point < 500) {

			playerSpeed = 0.45f;
		}

		if (player1.point >= 500 && player1.point < 700) {

			playerSpeed = 0.4f;
		}

		if (player1.player.getGlobalBounds().intersects(healthhelp_Sprite.getGlobalBounds())) {

			player1.health += 1;

			if (player1.health > 10) {

				player1.health = 10;
			}

			heart = false;
		}

		if (player1.player.getGlobalBounds().intersects(armorhelp_Sprite.getGlobalBounds())) {

			player1.arm += 1;

			if (player1.arm > 10) {

				player1.arm = 10;
			}
			armor = false;
		}

		window.clear();
		window.draw(gameBg_Sprite);
		window.draw(worldBg_Sprite);
		window.draw(heart_Sprite);
		window.draw(arm_Sprite);
		
		if (heart == true) {

			window.draw(healthhelp_Sprite);
		}

		if (armor == true) {
		
			window.draw(armorhelp_Sprite);
		}
		for (int i = 0; i < 7; i++) {

			window.draw(enemy[i].enemy);
		}
		
		for (int i = 0 ; i < 15 ; i++) {
			if (bullets[i].active) {
				window.draw(bullets[i].bulletSp);
			}
		}
		
		window.draw(bullets->bulletSp);
		window.draw(health_Text);
		window.draw(point_Text);
		window.draw(arm_Text);
		window.draw(player1.player);
		window.display();
	}
}

void His(sf::RenderWindow& window) {

	sf::Texture His_Tex;
	His_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\mainmenu.png");
	sf::Sprite His_Sprite;
	His_Sprite.setTexture(His_Tex);
	His_Sprite.setScale(4.5f, 4.5f);

	sf::Font fonts;
	fonts.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\font\\Chainwhacks-vm72E.ttf");

	sf::Text leaderBorad_Text;
	leaderBorad_Text.setFont(fonts);
	leaderBorad_Text.setString("Leaderboard");
	leaderBorad_Text.setFillColor(sf::Color::Green);
	leaderBorad_Text.setCharacterSize(45);
	leaderBorad_Text.setPosition((window.getSize().x / 2.f) - (leaderBorad_Text.getGlobalBounds().width / 2.f), 80.f);

	sf::Text backToMenu_Text;
	backToMenu_Text.setFont(fonts);
	backToMenu_Text.setString("Press  Esc  Back to Menu");
	backToMenu_Text.setFillColor(sf::Color::Yellow);
	backToMenu_Text.setCharacterSize(35);
	backToMenu_Text.setPosition((window.getSize().x / 2.f) - (backToMenu_Text.getGlobalBounds().width / 2.f), 715.f);

	sf::Text text[100];
	for (int i = 0; i < 55; i++) {

		text[i].setFont(fonts);
		text[i].setCharacterSize(35);
		text[i].setFillColor(sf::Color::Green);
	}

	std::vector <History> scores;

	std::ifstream scorefile("history.txt");

	if (scorefile.is_open()) {
		std::string line;
		while (std::getline(scorefile, line)) {
			size_t commaPos = line.find(",");
			if (commaPos != std::string::npos) {
				History hisData;
				hisData.namelead = line.substr(0, commaPos);
				hisData.scorelead = std::stoi(line.substr(commaPos + 1));
				scores.push_back(hisData);
			}
		}
		scorefile.close();
	}
	else {
		std::cout << "ERROR: Could not open scores.txt for reading." << std::endl;
	}

	std::sort(scores.begin(), scores.end(), compareScores);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

				pageNum = 100;
				return;
			}
		}

		window.clear();
		window.draw(His_Sprite);
		window.draw(leaderBorad_Text);

		sf::Text scoreText_name("", fonts, 50);
		sf::Text scoreText_score("", fonts, 50);
		for (int i = 0; i < std::min(5, static_cast<int>(scores.size())); ++i) {
			scoreText_name.setString(scores[i].namelead);
			scoreText_score.setString(std::to_string(scores[i].scorelead));
			scoreText_name.setFillColor(sf::Color::White);
			scoreText_score.setFillColor(sf::Color::White);
			scoreText_name.setPosition(90, 200 + i*90);
			scoreText_score.setPosition(400, 200 + i*90);
			window.draw(scoreText_name);
			window.draw(scoreText_score);
		}
		window.draw(backToMenu_Text);
		window.display();
	}
}

void game_Over(sf::RenderWindow& window) {

	sf::Texture His_Tex;
	His_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\mainmenu.png");
	sf::Sprite His_Sprite;
	His_Sprite.setTexture(His_Tex);
	His_Sprite.setScale(4.5f, 4.5f);

	sf::Font fonts;
	fonts.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\font\\Chainwhacks-vm72E.ttf");

	sf::Text GameOver_Text;
	GameOver_Text.setFont(fonts);
	GameOver_Text.setString("Game Over!");
	GameOver_Text.setPosition(130.f, 230.f);
	GameOver_Text.setScale(2.f, 2.f);
	GameOver_Text.setFillColor(sf::Color::Red);

	sf::Font fontzz;
	fontzz.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\font\\Chainwhacks-vm72E.ttf");

	sf::Text GameOverScore_Text;
	sf::String ScoreString = std::to_string(score);
	GameOverScore_Text.setFont(fontzz);
	GameOverScore_Text.setString("Your Score");
	GameOverScore_Text.setPosition((window.getSize().x / 2.f) - 145, 435.f);
	GameOverScore_Text.setScale(1.8f, 1.8f);
	GameOverScore_Text.setFillColor(sf::Color::Green);

	sf::Text Score_Text;
	sf::String Score_String = ScoreString;
	Score_Text.setFont(fontzz);
	Score_Text.setString(Score_String);
	Score_Text.setPosition((window.getSize().x / 2.f) - (Score_Text.getGlobalBounds().width / 2.f), 555);
	Score_Text.setScale(1.6f, 1.6f);
	Score_Text.setFillColor(sf::Color::Cyan);

	sf::Text seeLead_Text;
	seeLead_Text.setFont(fontzz);
	seeLead_Text.setString("Press    Enter    to  see  Leaderboard");
	seeLead_Text.setScale(0.9f, 0.9f);
	seeLead_Text.setPosition((window.getSize().x / 2.f) - (seeLead_Text.getGlobalBounds().width / 2.f), 700);
	seeLead_Text.setFillColor(sf::Color::Yellow);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed()) {

				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

				pageNum = 100;
				return;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

				pageNum = 5;
				return;
			}
		}
		
		window.clear();
		window.draw(His_Sprite);
		window.draw(GameOverScore_Text);
		window.draw(GameOver_Text);
		window.draw(Score_Text);
		window.draw(seeLead_Text);
		window.display();
	}
}

void game_Win(sf::RenderWindow& window) {

	sf::Texture win_Tex;
	win_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\image\\mainmenu.png");
	sf::Sprite win_Sprite;
	win_Sprite.setTexture(win_Tex);
	win_Sprite.setScale(4.5f, 4.5f);

	sf::Font fonts;
	fonts.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\font\\Chainwhacks-vm72E.ttf");

	sf::Text GameWin_Text;
	GameWin_Text.setFont(fonts);
	GameWin_Text.setString("Congratulations!!!");
	GameWin_Text.setCharacterSize(45);
	GameWin_Text.setPosition((window.getSize().x / 2.f) - (GameWin_Text.getGlobalBounds().width / 2.f), 230.f);
	GameWin_Text.setFillColor(sf::Color::Green);

	sf::Font fontzz;
	fontzz.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_V3_Final\\font\\Chainwhacks-vm72E.ttf");

	sf::Text congrat_Text;
	congrat_Text.setFont(fontzz);
	congrat_Text.setString("You save the world!");
	congrat_Text.setScale(1.5f, 1.5f);
	congrat_Text.setPosition((window.getSize().x / 2.f) - (congrat_Text.getGlobalBounds().width / 2.f), 450.f);
	congrat_Text.setFillColor(sf::Color::Cyan);

	sf::Text backToMenu_Text;
	backToMenu_Text.setFont(fonts);
	backToMenu_Text.setString("Press  Esc  Back to Menu");
	backToMenu_Text.setFillColor(sf::Color::Yellow);
	backToMenu_Text.setCharacterSize(35);
	backToMenu_Text.setPosition((window.getSize().x / 2.f) - (backToMenu_Text.getGlobalBounds().width / 2.f), 715.f);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed()) {

				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

				pageNum = 100;
				return;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

				pageNum = 5;
				return;
			}
		}

		window.clear();
		window.draw(win_Sprite);
		window.draw(GameWin_Text);
		window.draw(congrat_Text);
		window.draw(backToMenu_Text);
		window.display();
	}
}

