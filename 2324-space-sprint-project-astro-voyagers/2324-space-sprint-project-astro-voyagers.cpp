#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test window");
    window.setFramerateLimit(60);

    sf::Sprite sprite;
    sf::Texture texture;

    // Load the texture from the file
    if (!texture.loadFromFile("stars.jpg")) {
        std::cerr << "Failed to load texture." << std::endl;
        return 1; // Return an error code
    }

    // Set the texture for the sprite
    sprite.setTexture(texture);

    // Scale the sprite to fill the window
    sprite.setScale(
        static_cast<float>(window.getSize().x) / static_cast<float>(texture.getSize().x),
        static_cast<float>(window.getSize().y) / static_cast<float>(texture.getSize().y)
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}