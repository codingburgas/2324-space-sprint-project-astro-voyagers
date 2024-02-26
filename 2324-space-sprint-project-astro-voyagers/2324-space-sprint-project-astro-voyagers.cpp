#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Meteor {
public:
    sf::CircleShape shape;

    Meteor(float radius) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Red);
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

void showGameOver(sf::RenderWindow& window, const std::string& message) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Text text(message, font, 50);
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
    bool gameOver = false;
    bool UniversMythAchieved = false;
    bool SunMythAchieved = false;
    bool EarthMythAchived = false;
    bool meteorMythAchieved = false;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture cursorTexture;

    if (!cursorTexture.loadFromFile("RocketCursor.png")) {
        return EXIT_FAILURE;
    }

    sf::Sprite cursor(cursorTexture);
    float scaleFactor = 0.2f;
    cursor.setScale(scaleFactor, scaleFactor);

    // Hide the default mouse cursor
    window.setMouseCursorVisible(false);

    if (!texture.loadFromFile("Space.jpg")) {
        std::cerr << "Failed to load texture." << std::endl;
        return EXIT_FAILURE;
    }

    sprite.setTexture(texture);
    sprite.setScale(
        static_cast<float>(window.getSize().x) / static_cast<float>(texture.getSize().x),
        static_cast<float>(window.getSize().y) / static_cast<float>(texture.getSize().y)
    );

    std::vector<Meteor> meteors;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::Clock clock;
    int score = 0;
    sf::Time scoreUpdateInterval = sf::seconds(1);
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
    scoreText.setPosition(10.f, 10.f);

    while (window.isOpen() && !gameOver) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (rand() % 50 < 2) {
            float radius = static_cast<float>(rand() % 40) + 20;
            Meteor meteor(radius);
            meteor.setPosition(static_cast<float>(rand() % window.getSize().x), -radius);
            meteors.push_back(meteor);
        }

        for (auto it = meteors.begin(); it != meteors.end();) {
            it->shape.move(0, 3);

            if (it->shape.getPosition().y >= window.getSize().y) {
                score += 10;
                it = meteors.erase(it);
            }
            else {
                if (it->getBounds().intersects(cursor.getGlobalBounds())) {
                    showGameOver(window, "Game Over");

                    sf::sleep(sf::seconds(2));
                    gameOver = true;
                }
                else {
                    ++it;
                }
            }
        }

        // Constrain cursor within window bounds
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x < 0) mousePos.x = 0;
        if (mousePos.x >= window.getSize().x) mousePos.x = window.getSize().x - 1;
        if (mousePos.y < 0) mousePos.y = 0;
        if (mousePos.y >= window.getSize().y) mousePos.y = window.getSize().y - 1;
        cursor.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        timeSinceLastScoreUpdate += elapsed;

        if (timeSinceLastScoreUpdate >= scoreUpdateInterval) {
            scoreText.setString("Score: " + std::to_string(score));
            window.clear(sf::Color::White);
            window.draw(sprite);

            for (const auto& meteor : meteors) {
                window.draw(meteor.shape);
            }

            window.draw(cursor);
            window.draw(scoreText);
            window.display();

            timeSinceLastScoreUpdate -= scoreUpdateInterval;
        }
        else {
            window.clear(sf::Color::White);
            window.draw(sprite);

            for (const auto& meteor : meteors) {
                window.draw(meteor.shape);
            }

            window.draw(cursor);
            window.draw(scoreText);
            window.display();
        }

        // Check if score reaches 100
        // Check if score reaches 100
        if (score >= 100 && !meteorMythAchieved) {
            meteorMythAchieved = true;

            // Create a new window for displaying the myth text
            sf::RenderWindow endWindow(sf::VideoMode(800, 600), "End Window");

            // Create the text object for the new myth unlocked message
            sf::Text unlockedText;
            unlockedText.setFont(font);
            unlockedText.setCharacterSize(24);
            unlockedText.setFillColor(sf::Color::White);
            unlockedText.setStyle(sf::Text::Regular);
            unlockedText.setString("New Myth Unlocked: Meteor Myth");
            // Position the new myth unlocked message at the top center of the window
            sf::FloatRect unlockedBounds = unlockedText.getLocalBounds();
            unlockedText.setPosition((endWindow.getSize().x - unlockedBounds.width) / 2.f, 20.f);

            // Create the text object for the myth text
            sf::Text mythText;
            mythText.setFont(font);
            mythText.setCharacterSize(20);
            mythText.setFillColor(sf::Color::White);
            mythText.setStyle(sf::Text::Regular);
            mythText.setString("In the ancient myths, meteors are hailed as celestial messengers, born from the fiery remnants of dying stars. Crafted by the divine hand, these luminous stones traverse the expanse of the cosmos, carrying with them the secrets of creation and the mysteries of the universe. Their radiant glow illuminates the night sky, weaving tales of cosmic wonder and shaping the destiny of worlds with their ethereal presence. In the tapestry of the heavens, meteors are revered as harbingers of divine wisdom, forever etched in the celestial symphony of existence.");

            // Set maximum width for text wrapping
            float maxWidth = 780.f; // Adjust according to your window width
            mythText.setPosition(10.f, 60.f); // Set initial position below the unlocked message

            // Split the text into lines that fit within the maximum width
            std::string originalString = mythText.getString();
            std::string wrappedString;
            sf::Text tempText = mythText;
            unsigned int charCount = 0;
            for (char& c : originalString) {
                tempText.setString(wrappedString + c);
                if (tempText.getLocalBounds().width > maxWidth) {
                    wrappedString += '\n';
                }
                wrappedString += c;
            }
            mythText.setString(wrappedString);

            // Keep the window open until the user closes it
            while (endWindow.isOpen()) {
                sf::Event event;
                while (endWindow.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        endWindow.close();
                    }
                }

                endWindow.clear();
                endWindow.draw(unlockedText); // Draw the new myth unlocked message
                endWindow.draw(mythText); // Draw the myth text below it
                endWindow.display();
            }
        }

        if (score >= 250 && !EarthMythAchived) {
            EarthMythAchived = true;

            // Create a new window for displaying the myth text
            sf::RenderWindow endWindow(sf::VideoMode(800, 600), "End Window");

            // Create the text object for the new myth unlocked message
            sf::Text unlockedText;
            unlockedText.setFont(font);
            unlockedText.setCharacterSize(24);
            unlockedText.setFillColor(sf::Color::White);
            unlockedText.setStyle(sf::Text::Regular);
            unlockedText.setString("New Myth Unlocked: Earth Myth");
            // Position the new myth unlocked message at the top center of the window
            sf::FloatRect unlockedBounds = unlockedText.getLocalBounds();
            unlockedText.setPosition((endWindow.getSize().x - unlockedBounds.width) / 2.f, 20.f);

            // Create the text object for the myth text
            sf::Text mythText;
            mythText.setFont(font);
            mythText.setCharacterSize(20);
            mythText.setFillColor(sf::Color::White);
            mythText.setStyle(sf::Text::Regular);
            mythText.setString("In the dawn of time, when the universe was but a dream, the Earth emerged—a cradle of life, a sanctuary of wonders. From the whispering forests to the roaring oceans, it whispered secrets of existence to those who dared to listen. In its embrace, mortals found purpose, and gods found solace. The Earth, eternal and ever-giving, remains a testament to the beauty and mystery of creation.");

            // Set maximum width for text wrapping
            float maxWidth = 780.f; // Adjust according to your window width
            mythText.setPosition(10.f, 60.f); // Set initial position below the unlocked message

            // Split the text into lines that fit within the maximum width
            std::string originalString = mythText.getString();
            std::string wrappedString;
            sf::Text tempText = mythText;
            unsigned int charCount = 0;
            for (char& c : originalString) {
                tempText.setString(wrappedString + c);
                if (tempText.getLocalBounds().width > maxWidth) {
                    wrappedString += '\n';
                }
                wrappedString += c;
            }
            mythText.setString(wrappedString);

            // Keep the window open until the user closes it
            while (endWindow.isOpen()) {
                sf::Event event;
                while (endWindow.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        endWindow.close();
                    }
                }

                endWindow.clear();
                endWindow.draw(unlockedText); // Draw the new myth unlocked message
                endWindow.draw(mythText); // Draw the myth text below it
                endWindow.display();
            }
        }

        if (score >= 500 && !SunMythAchieved) {
            SunMythAchieved = true;

            // Create a new window for displaying the myth text
            sf::RenderWindow endWindow(sf::VideoMode(800, 600), "End Window");

            // Create the text object for the new myth unlocked message
            sf::Text unlockedText;
            unlockedText.setFont(font);
            unlockedText.setCharacterSize(24);
            unlockedText.setFillColor(sf::Color::White);
            unlockedText.setStyle(sf::Text::Regular);
            unlockedText.setString("New Myth Unlocked: Sun Myth");
            // Position the new myth unlocked message at the top center of the window
            sf::FloatRect unlockedBounds = unlockedText.getLocalBounds();
            unlockedText.setPosition((endWindow.getSize().x - unlockedBounds.width) / 2.f, 20.f);

            // Create the text object for the myth text
            sf::Text mythText;
            mythText.setFont(font);
            mythText.setCharacterSize(20);
            mythText.setFillColor(sf::Color::White);
            mythText.setStyle(sf::Text::Regular);
            mythText.setString("In the vast expanse of the celestial canvas, there blazed a radiant orb—the Sun, a divine ember of life and light. From its fiery core, it cast its golden tendrils across the cosmos, bestowing warmth and vitality upon all. With each dawn, it painted the world in hues of amber and gold, guiding the rhythm of existence with its timeless dance. In its luminous embrace, the Sun was more than a celestial body; it was a symbol of hope, a source of eternal light in the tapestry of the universe.");

            // Set maximum width for text wrapping
            float maxWidth = 780.f; // Adjust according to your window width
            mythText.setPosition(10.f, 60.f); // Set initial position below the unlocked message

            // Split the text into lines that fit within the maximum width
            std::string originalString = mythText.getString();
            std::string wrappedString;
            sf::Text tempText = mythText;
            unsigned int charCount = 0;
            for (char& c : originalString) {
                tempText.setString(wrappedString + c);
                if (tempText.getLocalBounds().width > maxWidth) {
                    wrappedString += '\n';
                }
                wrappedString += c;
            }
            mythText.setString(wrappedString);

            // Keep the window open until the user closes it
            while (endWindow.isOpen()) {
                sf::Event event;
                while (endWindow.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        endWindow.close();
                    }
                }

                endWindow.clear();
                endWindow.draw(unlockedText); // Draw the new myth unlocked message
                endWindow.draw(mythText); // Draw the myth text below it
                endWindow.display();
            }
        }
    }

    std::cout << "Score: " << score << std::endl;
    return 0;
}


    



