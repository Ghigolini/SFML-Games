#include "Ball.h"

Ball::Ball(Vector2f position, Color color) {
	ball.setPosition(position);
	ball.setRadius(20);
	ball.setFillColor(color);
	this->position = position;
	srand(time(NULL));
}

void Ball::update(Time gameTime, Pad* player1, Pad* player2) {
	if (started) {
		ball.move(v);
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && !ended) {
		started = true;
	}
	if (!started) {
		if ((rand() % 20) - 10 >= 0) {
			v.x = startSpeed;
		}
		else {
			v.x = -startSpeed;
		}
		v.y = (rand() % 20) - 10;
	}
	if (ball.getPosition().y < 0 || ball.getPosition().y > 1080 - 2 * ball.getRadius()) {
		v.y *= -1;
	}
	if (ball.getGlobalBounds().intersects(player1->u.getGlobalBounds()) || ball.getGlobalBounds().intersects(player1->d.getGlobalBounds())) {
		if (gameTime - collided > milliseconds(100)) {
			v.y *= -1;
			collided = gameTime;
		}
	}
	else if (ball.getGlobalBounds().intersects(player1->l.getGlobalBounds()) || ball.getGlobalBounds().intersects(player1->r.getGlobalBounds())) {
		if (gameTime - collided > milliseconds(100)) {
			if (v.x < 0) {
				v.x -= 1;
			}
			else {
				v.x += 1;
			}
			v.x *= -1;
			v.y = (rand() % 20) - 10;
			player1->pad.setSize(Vector2f(player1->pad.getSize().x, player1->pad.getSize().y - 1));
			collided = gameTime;
		}
	}
	if (ball.getGlobalBounds().intersects(player2->u.getGlobalBounds()) || ball.getGlobalBounds().intersects(player2->d.getGlobalBounds())) {
		if (gameTime - collided > milliseconds(100)) {
			v.y *= -1;
			collided = gameTime;
		}
	}
	else if (ball.getGlobalBounds().intersects(player2->l.getGlobalBounds()) || ball.getGlobalBounds().intersects(player2->r.getGlobalBounds())) {
		if (gameTime - collided > milliseconds(100)) {
			if (v.x < 0) {
				v.x -= 1;
			}
			else {
				v.x += 1;
			}
			v.x *= -1;
			v.y = (rand() % 20) - 10;
			player2->pad.setSize(Vector2f(player2->pad.getSize().x, player2->pad.getSize().y - 1));
			collided = gameTime;
		}
	}
	if (ball.getPosition().x < 0) {
		Sleep(500); 
		player2->score += 1;
		ball.setPosition(position);
		started = false;
	}
	else if (ball.getPosition().x > 1920 - 2 * ball.getRadius()) {
		Sleep(500);
		player1->score += 1;
		ball.setPosition(position);
		started = false;
	}
	if (player2->score >= 10) {
		player1->scoreText.setPosition(460 - 75, player1->scoreText.getPosition().y);
		player2->scoreText.setPosition(1420 - 275, player2->scoreText.getPosition().y);
		player2->scoreText.setString("player 2 ha vinto");
		player1->scoreText.setString("fai schifo");
		if (!ended) {
			player1->winTime = gameTime;
			player2->winTime = gameTime;
		}
		ended = true;
	}
	else if (player1->score >= 10) {
		player1->scoreText.setPosition(460 - 275, player1->scoreText.getPosition().y);
		player2->scoreText.setPosition(1420 - 75, player2->scoreText.getPosition().y);
		player1->scoreText.setString("player 1 ha vinto");
		player2->scoreText.setString("fai schifo");
		if (!ended) {
			player1->winTime = gameTime;
			player2->winTime = gameTime;
		}
		ended = true;
	}
	if (ended && (gameTime - player1->winTime > seconds(5) || gameTime - player2->winTime > seconds(5))) {
		ended = false;
		player1->score = 0;
		player2->score = 0;
	}
}

void Ball::draw(RenderWindow& window) {
	window.draw(ball);
}
