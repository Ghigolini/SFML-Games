#include "Window_.h"

struct Unit {
	RectangleShape u;
	void set() {
		Vector2i pos = Mouse::getPosition();
		if (Mouse::isButtonPressed(Mouse::Left) && u.getGlobalBounds().contains(pos.x, pos.y)) {
			alive = true;
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && u.getGlobalBounds().contains(pos.x, pos.y)) {
			alive = false;
		}
		if (alive) {
			u.setFillColor(Color::Black);
		}
		else {
			u.setFillColor(Color::White);
		}
	}
	void update() {
		if (alive) {
			if (near < 2 || near > 3) {
				alive = false;
			}
			else if(near == 2 || near == 3) {
				alive = true;
			}
		}
		else {
			if (near == 3) {
				alive = true;
			}
		}
		if (alive) {
			u.setFillColor(Color::Black);
		}
		else {
			u.setFillColor(Color::White);
		}
		near = 0;
	}
	bool alive = false;
	int near = 0;
}units[96][54];

bool start = false;

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
	this->window.setFramerateLimit(10);

	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 54; j++) {
			units[i][j].u.setPosition(i * 20, j * 20);
			units[i][j].u.setSize(Vector2f(20, 20));
		}
	}

	delete style;
}

void Window_::Run() {
	while (this->window.isOpen()) {
		this->Update();
		this->Render();
	}
}

void Window_::Update() {
	Event e;
	this->window.pollEvent(e);
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		this->window.close();
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		start = true;
	}

	if (!start) {
		for (int i = 0; i < 96; i++) {
			for (int j = 0; j < 54; j++) {
				units[i][j].u.setOutlineColor(Color::Black);
				units[i][j].u.setOutlineThickness(1);
				units[i][j].set();
			}
		}
	}
	else{
		for (int i = 0; i < 96; i++) {
			for (int j = 0; j < 54; j++) {
				units[i][j].u.setOutlineThickness(0);
				if (i > 0) {
					if (j > 0) {
						if (units[i - 1][j - 1].alive) {
							units[i][j].near += 1;
						}
					}
					if (units[i - 1][j].alive) {
						units[i][j].near += 1;
					}
					if (j < 53) {
						if (units[i - 1][j + 1].alive) {
							units[i][j].near += 1;
						}
					}
				}
				if (j > 0) {
					if (units[i][j - 1].alive) {
						units[i][j].near += 1;
					}
				}
				if (j < 53) {
					if (units[i][j + 1].alive) {
						units[i][j].near += 1;
					}
				}
				if (i < 95) {
					if (j > 0) {
						if (units[i + 1][j - 1].alive) {
							units[i][j].near += 1;
						}
					}
					if (units[i + 1][j].alive) {
						units[i][j].near += 1;
					}
					if (j < 53) {
						if (units[i + 1][j + 1].alive) {
							units[i][j].near += 1;
						}
					}
				}
			}
		}
		for (int i = 0; i < 96; i++) {
			for (int j = 0; j < 54; j++) {
				units[i][j].update();
			}
		}
	}
}

void Window_::Render() {
	this->window.clear();
	for (int i = 0; i < 96; i++) {
		for (int j = 0; j < 54; j++) {
			window.draw(units[i][j].u);
		}
	}
	this->window.display();
}