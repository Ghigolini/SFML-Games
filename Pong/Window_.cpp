#include "Window_.h"

Pad* player1, * player2;
Ball* ball;
RectangleShape half;

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
	delete style;

	player1 = new Pad(Vector2f(20, 440), Color::White);
	player2 = new Pad(Vector2f(1860, 440), Color::White);

	ball = new Ball(Vector2f(940, 530), Color::White);

	half.setPosition(955, 0);
	half.setSize(Vector2f(10, 1080));
	half.setFillColor(Color::White);
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
	player1->update(gameTime, Keyboard::W, Keyboard::S);
	player2->update(gameTime, Keyboard::Up, Keyboard::Down);
	ball->update(gameTime, player1, player2);
}

void Window_::Render() {
	this->window.clear();
	window.draw(half);
	player1->draw(window);
	player2->draw(window);
	ball->draw(window);
	this->window.display();
}
