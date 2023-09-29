
#include "Menu.h"
#include <time.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <string.h>

struct Player {

	int point = 0;
	int health = 10;
	sf::Sprite sprite;
	int arm = 10;
};

struct Enemy {

	sf::Sprite shape;
	float speed;
};

struct Bullet {

	sf::Sprite bulletSp;
	float speed = 0.4f;
	bool active;
};

struct Help {

	sf::Sprite RefShape; // Drop
	sf::Sprite targetShape; // Block
	int type; // 0 1 2
};

int pageNum = 100;
float playerSpeed = 0.3f;
const int maxBullets = 15;
std::string name;
int score = 0;


void Pname(sf::RenderWindow& window, std::string& name);

void game_Over(sf::RenderWindow& window);

void game_Play(sf::RenderWindow &window);

void His(sf::RenderWindow& window);

int main() {

	srand(static_cast<unsigned>(time(nullptr)));

	sf::RenderWindow window(sf::VideoMode(570, 870), "MAIN MENU", sf::Style::Close | sf::Style::Titlebar);

	Menu mainMenu(window.getSize().x, window.getSize().y);

	sf::Texture leadBg;
	sf::Sprite leaderBg;

	if (!leadBg.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\mainmenu.png")) {

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

						if (events.key.code == sf::Keyboard::S) {

							mainMenu.moveUp();
							break;
						}

						if (events.key.code == sf::Keyboard::W) {

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
	}

	//End of the application
	return 0;
}

void Pname(sf::RenderWindow& window, std::string& name) {

	if (!name.empty()) {

		name.clear();
	}

	sf::Texture backG;
	backG.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\mainmenu.png");
	sf::Sprite bG;
	bG.setTexture(backG);
	bG.setScale(4.5f, 4.5f);
	sf::Font Fontss;
	Fontss.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\Fonts\\DebugFreeTrial-MVdYB.otf");
	sf::Text t1;
	sf::Text t2;
	t1.setFont(Fontss);
	t2.setFont(Fontss);
	t1.setString("Enter your name : ");
	t1.setCharacterSize(50);
	t2.setCharacterSize(50);
	t1.setPosition(20.f, 20.f);
	t2.setPosition(20.f, 100.f);
	t1.setFillColor(sf::Color::Cyan);
	t2.setFillColor(sf::Color::Cyan);

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
		t2.setString(name);
		window.clear();
		window.draw(bG);
		window.draw(t1);
		window.draw(t2);
		window.display();
	}

}

void game_Play(sf::RenderWindow& window) {

	sf::Clock timerAdd, timerDelete;

	sf::Texture gameBg_Tex;
	gameBg_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\background.png");
	sf::Sprite gameBg_Sprite;
	gameBg_Sprite.setTexture(gameBg_Tex);

	sf::Texture worldBg_Tex;
	worldBg_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\world.png");
	sf::Sprite worldBg_Sprite;
	worldBg_Sprite.setTexture(worldBg_Tex);
	worldBg_Sprite.setScale(sf::Vector2f(0.5f, 0.5f));
	worldBg_Sprite.setPosition(147.f, 696.f);


	sf::Texture player_Tex;
	player_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\ship.png");
	Player player1;
	player1.sprite.setTexture(player_Tex);
	player1.sprite.setScale(2.f, 2.f);
	player1.sprite.setPosition(250.f, 480.f);
	
	sf::Texture bullet_Tex;
	bullet_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\bullet.png");
	Bullet bullets[15];
	for (int i = 0; i < 10; i++) {

		bullets[i].active = false;
		bullets[i].bulletSp.setTexture(bullet_Tex);
		bullets[i].bulletSp.setScale(0.7f, 0.7f);
	}
	sf::Texture asteriod_Tex;
	asteriod_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\spaceship.png");
	Enemy enemy[7];

	for (int i = 0; i < 7; i++) {

		enemy[i].shape.setTexture(asteriod_Tex);
		enemy[i].speed = (rand() % 2 + 1) / 6.0;
		enemy[i].shape.setScale(i * 0.3, i * 0.3);
		int x = (rand() % 551) + 5;
		enemy[i].shape.setPosition(x, 0.f);
	}

	sf::Texture heart_Tex;
	heart_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\heart.png");
	sf::Sprite heart_Sprite;
	heart_Sprite.setTexture(heart_Tex);
	heart_Sprite.setScale(0.085f, 0.085f);
	heart_Sprite.setPosition(5.f, 15.f);

	sf::Font font;
	font.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\Fonts\\Valorax-lg25V.otf");
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
		float playerWidth = player1.sprite.getGlobalBounds().width;
		float playerHeight = player1.sprite.getGlobalBounds().height;

		
		if (player1.sprite.getPosition().x < 0) {
			player1.sprite.setPosition(0, player1.sprite.getPosition().y);
		}
		if (player1.sprite.getPosition().x + playerWidth > windowWidth) {
			player1.sprite.setPosition(windowWidth - playerWidth, player1.sprite.getPosition().y);
		}
		if (player1.sprite.getPosition().y < 0) {
			player1.sprite.setPosition(player1.sprite.getPosition().x, 0);
		}
		if (player1.sprite.getPosition().y + playerHeight > windowHeight) {
			player1.sprite.setPosition(player1.sprite.getPosition().x, windowHeight - playerHeight);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player1.sprite.move(-playerSpeed, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player1.sprite.move(playerSpeed, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player1.sprite.move(0.f, -playerSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player1.sprite.move(0.f, playerSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			
			for (int i = 0; i < maxBullets; i++) {
				if (!bullets[i].active) {
					bullets[i].active = true;
					bullets[i].bulletSp.setPosition(player1.sprite.getPosition().x + playerWidth / 2, player1.sprite.getPosition().y);
					break;  
				}
			}
		}

		for (int i = 0; i < maxBullets; i++) {
			if (bullets[i].active) {
				bullets[i].bulletSp.move(0.f, -bullets[i].speed);
				
				if (bullets[i].bulletSp.getPosition().y < 0) {
					bullets[i].active = false;
				}
			}
		}

		for (int i = 0; i < maxBullets; i++) {
			if (bullets[i].active) {
				for (int j = 0; j < 7; j++) {
					if (bullets[i].bulletSp.getGlobalBounds().intersects(enemy[j].shape.getGlobalBounds())) {
						bullets[i].active = false;
						player1.point++;

						
						bullets[i].bulletSp.setPosition(-100.f, -100.f);

						int x = (rand() % 551) + 5;
						enemy[j].shape.setPosition(x, 0.f);
						enemy[j].speed = (rand() % 2 + 1) / 6.0;
					}
				}
			}
		}

		for (int i = 0; i < 7; i++) {

			enemy[i].shape.move(0.f, enemy[i].speed);

			if (enemy[i].shape.getPosition().y > 870) {

				int x = (rand() % 551) + 5;
				enemy[i].shape.setPosition(x, 0.f);
				enemy[i].speed = (rand() % 2 + 1) / 6.0;
				player1.arm--;
				
			}

			if (player1.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds())) {

				int x = (rand() % 551) + 5;
				enemy[i].shape.setPosition(x, 0.f);
				enemy[i].speed = (rand() % 2 + 1) / 6.0;
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
			offile << name << "                  " << player1.point << "*" << std::endl;
			player1.point = 0;
			pageNum = 4;
			return;
		}

		window.clear();
		window.draw(gameBg_Sprite);
		window.draw(worldBg_Sprite);
		window.draw(heart_Sprite);
		for (int i = 0; i < 7; i++) {

			window.draw(enemy[i].shape);
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
		window.draw(player1.sprite);
		window.display();
	}
}

void His(sf::RenderWindow& window) {

	sf::Texture His_Tex;
	His_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\mainmenu.png");
	sf::Sprite His_Sprite;
	His_Sprite.setTexture(His_Tex);
	His_Sprite.setScale(4.5f, 4.5f);

	sf::Font fonts;
	fonts.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\Fonts\\Chainwhacks-vm72E.ttf");

	sf::Text text[100];
	for (int i = 0; i < 55; i++) {

		text[i].setFont(fonts);
		text[i].setCharacterSize(40);
		text[i].setFillColor(sf::Color::Green);
	}

	std::ifstream infile;
	infile.open("history.txt", std::ios::in);

	std::vector <std::string> lines;
	std::string line;
	while (std::getline(infile, line, '*')) {

		lines.push_back(line);
	}

	for (int i = 0 ; i < lines.size(); i++) {

		text[i].setString(lines[i]);
		text[i].setPosition(50.f, 100.f * i);
	}

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				pageNum = 100;
				return;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

				if (text[0].getPosition().y <= 5) {
					for (int i = 0; i < lines.size() * 10; i++) {
						text[i].move(0.f, 20.f);
					}
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (text[(lines.size()) - 1].getPosition().y >= window.getPosition().y + 1000) {
					for (int i = 0 ; i < lines.size() + 10 ; i++) {
						text[i].move(0.f, -20.f);
					}
				}
			}
			std::cout << lines.size() << "\n";
		}
	}

	window.clear();
	window.draw(His_Sprite);
	for (int i = 0; i < lines.size(); i++) {
		window.draw(text[i]);
	}
	window.display();
}

void game_Over(sf::RenderWindow& window) {

	sf::Texture His_Tex;
	His_Tex.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\mainmenu.png");
	sf::Sprite His_Sprite;
	His_Sprite.setTexture(His_Tex);
	His_Sprite.setScale(4.5f, 4.5f);

	sf::Font fonts;
	fonts.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\Fonts\\Chainwhacks-vm72E.ttf");

	sf::Text GameOver_Text;
	GameOver_Text.setFont(fonts);
	GameOver_Text.setString("Game Over!");
	GameOver_Text.setPosition(130.f, 230.f);
	GameOver_Text.setScale(2.f, 2.f);
	GameOver_Text.setFillColor(sf::Color::Red);

	sf::Font fontzz;
	fontzz.loadFromFile("C:\\KMITL\\1D\\semester_1\\propro\\Meteorite_Hero\\Fonts\\Chainwhacks-vm72E.ttf");

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
		}
		
		window.clear();
		window.draw(His_Sprite);
		window.draw(GameOverScore_Text);
		window.draw(GameOver_Text);
		window.draw(Score_Text);
		window.display();
	}
}

/*

	Problems : cannot run the leaderboard

*/




