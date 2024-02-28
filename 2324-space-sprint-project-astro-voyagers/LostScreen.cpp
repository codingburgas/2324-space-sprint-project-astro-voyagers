#include "Game.h"

//Check if font loads
void showGameOver(sf::RenderWindow& window, const std::string& message) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }
    //Applies font
    sf::Text text(message, font, 50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2, window.getSize().y / 2 - text.getGlobalBounds().height / 2);

    window.clear(sf::Color::White);
    window.draw(text);
    window.display();
}