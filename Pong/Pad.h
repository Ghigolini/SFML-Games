#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Pad {
public:
	RectangleShape pad, u, r, d, l;
	int score = 0;
	Text scoreText;
	Time winTime = seconds(0);
	Pad(Vector2f position, Color color);
	void update(Time gameTime, Keyboard::Key up, Keyboard::Key down);
	void draw(RenderWindow& window);
private:
	float vy = 0;
	int a = 1, maxSpeed = 10;
	Font font;
};
