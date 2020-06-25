#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
using namespace sf;

class Fruit {
public:
	CircleShape fruit;
	bool isCaught = false;
	Fruit(Snake* snake);
	void respawn(Snake* snake);
	void caught(Snake* snake);
	void draw(RenderWindow& window);
};

