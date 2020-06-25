#include "Window_.h"
#include "Snake.h"
#include "Fruit.h"

Snake* snake;
Fruit* fruit;

Window_::Window_(Vector2f windowSize, string title, bool fullscreen) {
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	Uint32 *style = new Uint32;
	if (fullscreen) {
		*style = Style::Fullscreen;
	}
	else {
		*style = Style::None;
	}
	this->window.create(VideoMode(windowSize.x, windowSize.y), "title", *style, settings);
	this->window.setVerticalSyncEnabled(true);
	this->window.setFramerateLimit(60);
	this->window.setMouseCursorVisible(false);

	delete style;
	srand(time(NULL));
	snake = new Snake(Vector2f((rand() % 90) * 20, (rand() % 50) * 20));
	fruit = new Fruit(snake);

	ifstream highscoreFile("highscore.txt");
	if (highscoreFile.is_open()) {
		highscoreFile >> highscore;
		highscoreFile.close();
	}
	font.loadFromFile("Super-Mario-Bros--3.ttf");
	highscoreText.setCharacterSize(40);
	highscoreText.setFont(font);
	highscoreText.setPosition(1400, 30);
	highscoreText.setString("highscore\n\t\t  " + to_string(highscore));
}

void Window_::Run() {
	while (this->window.isOpen()) {
		this->Update();
		this->Render();
	}
}

void Window_::Update() {
	gameTime = clock.getElapsedTime();
	Event e;
	this->window.pollEvent(e);
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		this->window.close();
	}

	snake->update(gameTime, Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);
	fruit->respawn(snake);
	fruit->caught(snake);

	if (!snake->alive && !setHighscore && snake->score > highscore) {
		ofstream highscoreFile("highscore.txt");
		if (highscoreFile.is_open()) {
			highscoreFile << snake->score;
		}
		highscoreFile.close();
		setHighscore = true;
	}
}

void Window_::Render() {
	this->window.clear();
	snake->draw(window);
	fruit->draw(window);
	if (snake->v != Vector2f(0, 0)) {
		window.draw(highscoreText);
	}
	this->window.display();
}
