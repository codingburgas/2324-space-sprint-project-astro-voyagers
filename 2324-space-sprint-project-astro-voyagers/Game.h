#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Meteor {
public:
    sf::CircleShape shape;

    Meteor(float radius, const sf::Texture& texture) {
        shape.setRadius(radius);
        shape.setTexture(&texture); // Apply texture to the meteor's shape
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

void showGameOver(sf::RenderWindow& window, const std::string& message);