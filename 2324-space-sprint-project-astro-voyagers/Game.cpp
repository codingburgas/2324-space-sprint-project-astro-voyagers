#include "game.h"

int loadTextures(sf::Texture& cursorTexture, sf::Sprite& cursor, sf::Texture& texture, sf::Sprite& sprite, sf::RenderWindow& window) {
    if (!cursorTexture.loadFromFile("RocketCursor.png")) {
        return EXIT_FAILURE;
    }

    cursor.setTexture(cursorTexture);
    float scaleFactor = 0.2f;
    cursor.setScale(scaleFactor, scaleFactor);

    window.setMouseCursorVisible(false);

    if (!texture.loadFromFile("Background.png")) {
        std::cerr << "Failed to load texture." << std::endl;
        return EXIT_FAILURE;
    }

    sprite.setTexture(texture);
    sprite.setScale(
        static_cast<float>(window.getSize().x) / static_cast<float>(texture.getSize().x),
        static_cast<float>(window.getSize().y) / static_cast<float>(texture.getSize().y)
    );

    return EXIT_SUCCESS;
}