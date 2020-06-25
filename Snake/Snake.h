#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <windows.h>
#include <string>
using namespace sf;
using namespace std;

class Snake {
public:
	vector<RectangleShape> snake;
	vector<Vector2f> tail;
	Time moveTime;
	unsigned int length = 0;
	Snake(Vector2f position);
	void update(Time gameTime, Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right);
	void draw(RenderWindow& window);
	bool alive = true;
	int score = 0;
	Vector2f v = Vector2f(0, 0);
private:
	Text scoreText;
	Font font;
};

