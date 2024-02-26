#pragma once
#include "Game.h"

int loadTextures(sf::Texture& cursorTexture, sf::Sprite& cursor, sf::Texture& texture, sf::Sprite& sprite, sf::RenderWindow& window);
int initializeMeteors(std::vector<Meteor>& meteors, sf::Texture& meteorTexture);
void initializeGameVariables(sf::Clock& clock, int& score, sf::Time& scoreUpdateInterval, sf::Time& timeSinceLastScoreUpdate);
int loadFont(sf::Font& font);