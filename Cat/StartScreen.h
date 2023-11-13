#pragma once
#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <SFML/Graphics.hpp>

class StartScreen {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text startText;
    sf::RectangleShape startButton;
    bool isButtonHovered;

public:
    StartScreen();
    void handleInput(sf::RenderWindow& window);
    void update(sf::Time dt);
    void render(sf::RenderWindow& window);
};

#endif // START_SCREEN_H