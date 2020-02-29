#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

void Player() {
	sf::Texture texture;
	texture.loadFromFile("smile.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(100, 100);
	sprite.setColor(sf::Color::Green);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setScale(1.7f, 1.7f);
}