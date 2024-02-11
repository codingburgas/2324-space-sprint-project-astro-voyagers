#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
	
	sf::Window window(sf::VideoMode(800, 600), "Test window");
	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
	}
}