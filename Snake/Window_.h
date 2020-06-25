#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

class Window_ {
public:
	RenderWindow window;
	Window_(Vector2f windowSize, string title, bool fullscreen);
	void Run();
private:
	void Update();
	void Render();
	Vector2f windowSize = Vector2f(0, 0);
	Time gameTime;
	Clock clock;
	bool setHighscore = false;
	int highscore;
	Text highscoreText;
	Font font;
};

