#include "Pad.h"

Pad::Pad(Vector2f position, Color color) {
	pad.setPosition(position);
	pad.setSize(Vector2f(30, 200));
	pad.setFillColor(color);

	u.setPosition(pad.getPosition());
	u.setSize(Vector2f(pad.getSize().x, 1));
	u.setFillColor(Color::Red);

	d.setPosition(pad.getPosition().x , pad.getPosition().y + pad.getSize().y);
	d.setSize(Vector2f(pad.getSize().x, 1));
	d.setFillColor(Color::Red);

	r.setPosition(pad.getPosition().x + pad.getSize().x, pad.getPosition().y);
	r.setSize(Vector2f(1, pad.getSize().y));
	r.setFillColor(Color::Red);

	l.setPosition(pad.getPosition());
	l.setSize(Vector2f(1, pad.getSize().y));
	l.setFillColor(Color::Red);

	font.loadFromFile("Super-Mario-Bros--3.ttf");

	scoreText.setCharacterSize(40);
	scoreText.setFont(font);
	scoreText.setString(std::to_string(score));
	if (position.x < 960) {
		scoreText.setPosition(460, 50);
	}
	else {
		scoreText.setPosition(1420, 50);
	}
}

void Pad::update(Time gameTime, Keyboard::Key up, Keyboard::Key down) {
	pad.move(0, vy);

	u.setPosition(pad.getPosition());
	u.setSize(Vector2f(pad.getSize().x, 1));
	u.setFillColor(Color::Red);

	d.setPosition(pad.getPosition().x, pad.getPosition().y + pad.getSize().y);
	d.setSize(Vector2f(pad.getSize().x, 1));
	d.setFillColor(Color::Red);

	r.setPosition(pad.getPosition().x + pad.getSize().x, pad.getPosition().y);
	r.setSize(Vector2f(1, pad.getSize().y));
	r.setFillColor(Color::Red);

	l.setPosition(pad.getPosition());
	l.setSize(Vector2f(1, pad.getSize().y));
	l.setFillColor(Color::Red);

	if (Keyboard::isKeyPressed(up)) {
		if (vy > -maxSpeed) {
			vy -= a;
		}
		else {
			vy = -maxSpeed;
		}
	}
	else if (Keyboard::isKeyPressed(down)) {
		if (vy < maxSpeed) {
			vy += a;
		}
		else {
			vy = maxSpeed;
		}
	}
	else {
		if (vy > a) {
			vy -= a;
		}
		else if (vy < -a) {
			vy += a;
		}
		else {
			vy = 0;
		}
	}
	if (pad.getPosition().y < -50) {
		pad.setPosition(pad.getPosition().x, -50);
		vy = 0;
	}
	else if (pad.getPosition().y + pad.getSize().y > 1130) {
		pad.setPosition(pad.getPosition().x, 1130 - pad.getSize().y);
		vy = 0;
	}
	if (gameTime - winTime > seconds(5) || winTime == seconds(0)) {
		scoreText.setString(std::to_string(score));
		if (pad.getPosition().x < 960) {
			scoreText.setPosition(460, 50);
		}
		else {
			scoreText.setPosition(1420, 50);
		}
	}
}

void Pad::draw(RenderWindow& window) {
	window.draw(pad);
	/*window.draw(u);
	window.draw(d);
	window.draw(l);
	window.draw(r);*/
	window.draw(scoreText);
}
