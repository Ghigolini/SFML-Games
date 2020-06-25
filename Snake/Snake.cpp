#include "Snake.h"

Snake::Snake(Vector2f position) {
	snake.push_back(RectangleShape());
	snake[0].setPosition(position);
	snake[0].setSize(Vector2f(20, 20));
	snake[0].setFillColor(Color::Red);
	tail.push_back(position);
	font.loadFromFile("Super-Mario-Bros--3.ttf");
	scoreText.setCharacterSize(40);
	scoreText.setFont(font);
	scoreText.setPosition(400, 30);
	scoreText.setString("premi una freccetta per iniziare");
}

void Snake::update(Time gameTime, Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right) {
	if (alive) {
		if (gameTime - moveTime > milliseconds(100)) {
			snake[0].move(v);
			if (length == tail.size() - 1) {
				for (int i = 0; i < snake.size() - 1; i++) {
					tail[i] = tail[i + 1];
				}
			}
			tail[snake.size() - 1] = snake[0].getPosition();
			for (int i = 1; i < snake.size(); i++) {
				snake[i].setPosition(tail[i - 1]);
			}
			moveTime = gameTime;
			if (Keyboard::isKeyPressed(up)) {
				if (v.y <= 0) {
					v.y = -20;
					v.x = 0;
				}
			}
			else if (Keyboard::isKeyPressed(down)) {
				if (v.y >= 0) {
					v.y = 20;
					v.x = 0;
				}
			}
			else if (Keyboard::isKeyPressed(right)) {
				if (v.x >= 0) {
					v.x = 20;
					v.y = 0;
				}
			}
			else if (Keyboard::isKeyPressed(left)) {
				if (v.x <= 0) {
					v.x = -20;
					v.y = 0;
				}
			}
		}
	}
	for (unsigned int i = 1; i < snake.size(); i++) {
		if (snake[0].getPosition() == snake[i].getPosition()) {
			alive = false;
		}
	}
	if (snake[0].getPosition().x < 0 || snake[0].getPosition().x > 1900 || snake[0].getPosition().y < 0 || snake[0].getPosition().y > 1060) {
		alive = false;
	}
	if (!alive) {
		for (int i = 0; i < snake.size(); i++) {
			snake[i].setFillColor(Color::Red);
		}
	}
	if (v != Vector2f(0, 0)) {
		if (scoreText.getPosition() != Vector2f(955, 30)) {
			scoreText.setPosition(955, 30);
		}
		scoreText.setString(to_string(score));
	}
}

void Snake::draw(RenderWindow& window) {
	for (int i = 0; i < snake.size(); i++) {
		window.draw(snake[i]);
	}
	window.draw(scoreText);
}
