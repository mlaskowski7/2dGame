#include <SFML/Graphics.hpp>

class Bullet {
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;

public:
    Bullet(sf::Vector2f const& heroPosition);
    auto move() -> void;
    auto getSprite() -> sf::Sprite;
};
