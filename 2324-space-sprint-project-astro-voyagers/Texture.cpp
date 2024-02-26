#include "Texture.h"


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

int initializeMeteors(std::vector<Meteor>& meteors, sf::Texture& meteorTexture) {
    if (!meteorTexture.loadFromFile("MeteorTexture.png")) {
        std::cerr << "Failed to load meteor texture." << std::endl;
        return EXIT_FAILURE;
    }
    srand(static_cast<unsigned int>(std::time(nullptr)));
    return EXIT_SUCCESS;
}

void initializeGameVariables(sf::Clock& clock, int& score, sf::Time& scoreUpdateInterval, sf::Time& timeSinceLastScoreUpdate) {
    clock.restart();
    score = 0;
    scoreUpdateInterval = sf::seconds(1);
    timeSinceLastScoreUpdate = sf::Time::Zero;
}

int loadFont(sf::Font& font) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}