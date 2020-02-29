#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>

using namespace std;

string s[4] = {"Sprites/carEnBlue.png","Sprites/carEnYellow.png", "Sprites/carEnRed.png", "Sprites/carEnGreen.png" };

sf::CircleShape Draw() {
	sf::CircleShape circle(30,4);
	circle.setFillColor(sf::Color::Blue);
	return circle;

}

struct Car {
	string color;
	sf::Sprite obj;
	sf::Texture texture;
	int speed;
};

Car getCar()
{
	Car car;
	car.color = s[rand() % 4];
	car.speed = rand() % 10 + 5;
	car.texture.loadFromFile(car.color);
	//car.obj.setTexture(car.texture);
	return car;
}

bool Gran(unsigned int x,unsigned int y) {
	if (x >= 0 && x <= 722 && y>=0 && y <=650)
		return true;
	else
		return false;
}


void main() {

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	window.setFramerateLimit(120);
	bool alive = true;
	

	sf::Music music;//создаем объект музыки
	music.openFromFile("Audio/Wasted.wav");//загружаем файл

	sf::Music carmus;//создаем объект музыки
	carmus.openFromFile("Audio/cars.wav");//загружаем файл
	carmus.play();


	sf::Texture texture;
	texture.loadFromFile("Sprites/wasted1.png");
	sf::Texture roadTexture;
	roadTexture.loadFromFile("Sprites/Road.png");
	sf::Texture carTexture;
	carTexture.loadFromFile("Sprites/carWhite.png");
	sf::Texture explosion;
	explosion.loadFromFile("Sprites/exp3.png");
	sf::Sprite expS(explosion);

	sf::Sprite died(texture);
	sf::Sprite road1(roadTexture);
	sf::Sprite road2(roadTexture);
	sf::Sprite sprite(carTexture);

	road2.setPosition(0, -800);

	int speed[4] = { rand() % 10 + 5,rand() % 10 + 5 ,rand() % 10 + 5 ,rand() % 10 + 5 };


	sprite.setPosition(400, 649);
	//sprite.setColor(sf::Color::Green);
	//sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	//sprite.setScale(1.7f, 1.7f);
	Car cars[4];
	for (int i = 0; i < 4; i++) {
		cars[i] = getCar();
		cars[i].obj.setTexture(cars[i].texture);
		cars[i].obj.setPosition(50 + 200 * i, -150);
	}
	bool key = true;
	int count = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && Gran(sprite.getPosition().x, sprite.getPosition().y) && alive) {
				switch (event.key.code) {
				case sf::Keyboard::Key::Left:
					sprite.move(-10, 0);
					break;
				case sf::Keyboard::Key::Right:
					sprite.move(10, 0);
					break;
				case sf::Keyboard::Key::Up:
					sprite.move(0, -10);
					break;
				case sf::Keyboard::Key::Down:
					sprite.move(0, 10);
					break;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			cars[i].obj.move(0.f, 0.5f * cars[i].speed);
		}
		road1.move(0.f, 2.f);
		road2.move(0.f, 2.f);
		window.clear();

		window.draw(road1);
		window.draw(road2);

		window.draw(sprite);
		window.draw(Draw());

		for (int i = 0; i < 4; i++) {
			window.draw(cars[i].obj);
		}

		if (road1.getPosition().y >= 800) {
			road1.setPosition(0, -800);
		}
		if (road2.getPosition().y >= 800) {
			road2.setPosition(0, -800);
		}
		for (int i = 0; i < 4; i++) {
			if (cars[i].obj.getPosition().y > 800)
			{
				cars[i] = getCar();
				cars[i].obj.setTexture(cars[i].texture);
				cars[i].obj.setPosition(50 + 200 * i, -150);
			}
		}
		if (sprite.getPosition().y > 650) {
			sprite.setPosition(sprite.getPosition().x, 650);
		}
		if (sprite.getPosition().y < 0) {
			sprite.setPosition(sprite.getPosition().x, 0);
		}
		if (sprite.getPosition().x > 722) {
			sprite.setPosition(722, sprite.getPosition().y);
		}
		if (sprite.getPosition().y < 0) {
			sprite.setPosition(0, sprite.getPosition().y);
		}
		for (int i = 0; i < 4; i++) {
			if (sprite.getGlobalBounds().intersects(cars[i].obj.getGlobalBounds())) {
				alive = false;
				window.setFramerateLimit(10);
				break;
			}
		}
		if (!alive) {
			count++;
			//cout << count;
			expS.setPosition(sprite.getPosition().x-20, sprite.getPosition().y);
		}
		if(count>10)
			window.draw(expS);
		if (count > 20) {
			sf::Texture expS2;
			expS2.loadFromFile("Sprites/exp2.png");
			explosion.update(expS2);
			expS.setTexture(explosion);
			window.draw(expS);
		}
		if (count > 30) {
			sf::Texture expS2;
			expS2.loadFromFile("Sprites/exp1.png");
			explosion.update(expS2);
			expS.setTexture(explosion);
			window.draw(expS);
		}
		if (!alive && key) {
			music.play();
			key = false;
		}
		if(!alive && count>26) {
			window.draw(died);
		}
		if (count == 70)
			break;
		window.display();
	}
}