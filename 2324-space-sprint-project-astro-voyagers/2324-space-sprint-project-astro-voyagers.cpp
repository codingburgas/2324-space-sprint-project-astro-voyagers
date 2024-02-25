#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding random number generator

class Meteor {
public:
    sf::CircleShape shape;

    Meteor(float radius) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Red); // Adjust color as needed
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

void showGameOver(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Text text("YOU LOSE!", font, 50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2, window.getSize().y / 2 - text.getGlobalBounds().height / 2);

    window.clear(sf::Color::White);
    window.draw(text);
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test window");
    window.setFramerateLimit(60);
    bool meteorMythAchieved = false;
    bool gameOver = false;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture cursorTexture;

    if (!cursorTexture.loadFromFile("RocketCursor.png")) {
        return EXIT_FAILURE;
    }

    // Create a sprite for the cursor
    sf::Sprite cursor(cursorTexture);

    // Adjust the size of the cursor image
    float scaleFactor = 0.2f; // Change this value to adjust the size
    cursor.setScale(scaleFactor, scaleFactor);

    // Hide the default mouse cursor
    window.setMouseCursorVisible(false);

    // Load the texture from the file
    if (!texture.loadFromFile("Space.jpg")) {
        std::cerr << "Failed to load texture." << std::endl;
        return EXIT_FAILURE;
    }

    // Set the texture for the sprite
    sprite.setTexture(texture);

    // Scale the sprite to fill the window
    sprite.setScale(
        static_cast<float>(window.getSize().x) / static_cast<float>(texture.getSize().x),
        static_cast<float>(window.getSize().y) / static_cast<float>(texture.getSize().y)
    );

    std::vector<Meteor> meteors; // Vector to store meteor objects

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::Clock clock;
    int score = 0;
    sf::Time scoreUpdateInterval = sf::seconds(1); // Update score every second
    sf::Time timeSinceLastScoreUpdate = sf::Time::Zero;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f); // Position on the left side of the window

    while (window.isOpen() && !gameOver) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Spawn meteors at random positions on the top of the screen
        if (rand() % 50 < 2) { // Adjust this probability to control meteor spawning frequency
            float radius = static_cast<float>(rand() % 40) + 20; // Random radius between 20 and 60
            Meteor meteor(radius);
            meteor.setPosition(static_cast<float>(rand() % window.getSize().x), -radius);
            meteors.push_back(meteor);
        }

        // Move meteors downwards
        for (auto it = meteors.begin(); it != meteors.end();) {
            it->shape.move(0, 3); // Adjust the meteor speed as needed

            // Check if the meteor is dodged
            if (it->shape.getPosition().y >= window.getSize().y) {
                score += 10; // Increment score by 10 for each dodged meteor
                it = meteors.erase(it); // Remove the dodged meteor from the vector
            }
            else {
                // Check collision with cursor
                if (it->getBounds().intersects(cursor.getGlobalBounds())) {
                    showGameOver(window);
                    // Wait for a moment to let the player see the lose screen before closing
                    sf::sleep(sf::seconds(2));
                    gameOver = true;
                    // window.close(); // Remove this line
                }
                else {
                    ++it;
                }
            }
        }

        // Move spaceship with cursor position
        cursor.setPosition(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));

        // Update time since last score update
        timeSinceLastScoreUpdate += elapsed;

        // Check if it's time to update the score
        if (timeSinceLastScoreUpdate >= scoreUpdateInterval) {
            // Update and draw the score
            scoreText.setString("Score: " + std::to_string(score));
            window.clear(sf::Color::White);
            window.draw(sprite);

            // Draw meteors
            for (const auto& meteor : meteors) {
                window.draw(meteor.shape);
            }

            // Draw the custom cursor
            window.draw(cursor);
            window.draw(scoreText);
            window.display();

            timeSinceLastScoreUpdate -= scoreUpdateInterval; // Reset time since last update
        }
        else {
            window.clear(sf::Color::White);

            // Draw your game objects here
            window.draw(sprite);

            // Draw meteors
            for (const auto& meteor : meteors) {
                window.draw(meteor.shape);
            }

            // Draw the custom cursor
            window.draw(cursor);
            window.draw(scoreText);
            window.display();
        }

        // Check if score reaches 100
        if (score >= 100 && !meteorMythAchieved) {
            meteorMythAchieved = true;

            // Display the message
            sf::Text mythText("You achieved the Meteor Myth", font, 30);
            mythText.setFillColor(sf::Color::Green);
            mythText.setStyle(sf::Text::Italic);
            mythText.setPosition(window.getSize().x / 2 - mythText.getGlobalBounds().width / 2, 50);

            // Adjust Y-coordinate to avoid overlap
            float textY = mythText.getPosition().y + mythText.getGlobalBounds().height + 50; // Increased spacing

            // Display the longer text below the first message
            std::string longTextString = "In the ancient myth of meteor formation, celestial artisans forged these luminous stones from the remnants of dying stars, infusing them with cosmic energy. Guided by the hand of fate, these ethereal messengers traverse the vast expanse of space, carrying the secrets of creation and the mysteries of the universe. As they journey, meteors illuminate the night sky, weaving tales of celestial wonder and shaping the destiny of worlds with their radiant presence.";
            sf::Text longText;
            longText.setFont(font);
            longText.setCharacterSize(12);
            longText.setFillColor(sf::Color::White);
            longText.setStyle(sf::Text::Regular);
            longText.setString(longTextString);

            // Calculate position for the longer text
            float textX = 20; // X-coordinate
            longText.setPosition(textX, textY);

            // Wrap the long text
            sf::FloatRect textRect = longText.getLocalBounds();
            float maxWidth = window.getSize().x - 2 * textX;
            if (textRect.width > maxWidth) {
                std::string textString = longText.getString();
                std::size_t pos = textString.find_last_of(" ", static_cast<std::size_t>(maxWidth));
                if (pos != std::string::npos) {
                    textString.insert(pos + 1, "\n");
                    longText.setString(textString);
                }
            }

            window.clear(sf::Color::Black); // Clear the window
            window.draw(mythText); // Draw the first message
            window.draw(longText); // Draw the longer text
            window.display();
            sf::sleep(sf::seconds(2)); // Pause for 2 seconds
            // continue; // Remove the continue statement
        }
    }

    std::cout << "Score: " << score << std::endl;
    return 0;
}
