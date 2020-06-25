#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Pad.h"
using namespace sf;

class Ball {
public:
	CircleShape ball;
	Ball(Vector2f position, Color color);
	void update(Time gameTime, Pad* player1, Pad* player2);
	void draw(RenderWindow& window);
private:
	Vector2f v = Vector2f(0, 0);
	int startSpeed = 10;
	bool started = false, ended = false;
	int initialVy = 0;
	Time collided = seconds(0);
	Vector2f position = Vector2f(0, 0);
};

