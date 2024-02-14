#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test window");
    window.setFramerateLimit(60);

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture cursorTexture;

    if (!cursorTexture.loadFromFile("RocketCursor.png")) {
        return EXIT_FAILURE;
    }

    // Create a sprite for the cursor
    sf::Sprite cursor(cursorTexture);

    // Adjust the size of the cursor image
    float scaleFactor = 0.3f; // Change this value to adjust the size
    cursor.setScale(scaleFactor, scaleFactor);

    // Hide the default mouse cursor
    window.setMouseCursorVisible(false);

    // Load the texture from the file
    if (!texture.loadFromFile("Space.jpg")) {
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

        cursor.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        window.clear(sf::Color::White);

        // Draw your game objects here
        window.draw(sprite);

        // Draw the custom cursor
        window.draw(cursor);

        window.display();
    }

    return 0;
}