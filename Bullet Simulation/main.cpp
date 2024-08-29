#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<random>
#include<chrono>
#include<vector>
#include<iostream>
#include<cmath>
std::mt19937 seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
float get_random_float(float l, float r) {
	return std::uniform_real_distribution<float>(l, r)(seed);
}
const float BULLET_SPEED = 1.5f;
const float PI = 3.14159265f;
int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Bullet Simulation");
	window.setFramerateLimit(240);
	std::vector<sf::RectangleShape>bullets;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				bullets.emplace_back(sf::RectangleShape(sf::Vector2f(40.0f, 10.0f)));
				bullets.back().setRotation(get_random_float(0.0f, 359.9f));
				bullets.back().setPosition(sf::Vector2f(get_random_float(50.0f, 1900.0f), get_random_float(50.0f, 1000.0f)));
			}
		}
		window.clear(sf::Color::Black);
		for (sf::RectangleShape& bullet : bullets) {
			sf::Vector2f direction(1.0f, std::tanf(bullet.getRotation() * PI / 180.0f));
			float currentSpeed = sqrt(direction.x * direction.x + direction.y * direction.y);
			direction.x /= currentSpeed / BULLET_SPEED;
			direction.y /= currentSpeed / BULLET_SPEED;
			bullet.setPosition(bullet.getPosition() + direction);
			window.draw(bullet);
		}
		window.display();
	}
}