#include "Fruit.h"

Fruit::Fruit(Snake* snake) {
	srand(time(NULL));
	bool ok = false;
	do {
		Vector2f pos = Vector2f(((rand() % 90) + 1) * 20 + 60, ((rand() % 50) + 1) * 20 + 60);
		if (pos != snake->snake[0].getPosition()) {
			fruit.setPosition(pos);
			ok = true;
		}
	} while (!ok);
	fruit.setRadius(10);
	fruit.setPointCount(4);
	fruit.setFillColor(Color::Color(255, 153, 0));
}

void Fruit::respawn(Snake* snake) {
	if (isCaught) {
		bool ok = false;
		do {
			Vector2f pos = Vector2f(((rand() % 90) + 1) * 20 + 60, ((rand() % 50) + 1) * 20 + 60);
			for (int i = 0; i < snake->snake.size(); i++) {
				if (pos != snake->snake[i].getPosition()) {
					fruit.setPosition(pos);
					ok = true;
				}
				else {
					ok = false;
				}
			}
		} while (!ok);
		isCaught = false;
	}
}

void Fruit::caught(Snake* snake) {
	if (snake->snake[0].getPosition() == this->fruit.getPosition() || Keyboard::isKeyPressed(Keyboard::P)) {
		snake->snake.push_back(RectangleShape());
		snake->length++;
		snake->tail.push_back(snake->tail[snake->length - 1]);
		snake->snake[snake->length].setPosition(3000, 3000);
		snake->snake[snake->length].setSize(Vector2f(20, 20));
		snake->snake[snake->length].setFillColor(Color::Green);
		snake->score += 1;
		this->isCaught = true;
	}
}

void Fruit::draw(RenderWindow& window) {
	window.draw(fruit);
}
