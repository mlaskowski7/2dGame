#pragma once

#include <SFML/Graphics.hpp>

class Bullet {
    sf::Texture texture;

protected:
    sf::Vector2f position;
    sf::Sprite sprite;
public:
    Bullet(sf::Vector2f const& heroPosition, bool const& isHero);
    virtual auto move() -> void;
    auto getSprite() -> sf::Sprite;
};
