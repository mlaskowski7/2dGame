#include <SFML/Graphics.hpp>
#include <vector>

struct Hero{
    float positionX;
    float positionY;
    static const auto movementSpeed = 10;

//    Hero Frames Collection
    std::vector<std::string> frames;
    int currentFrame;

    sf::Sprite heroSprite;
    sf::Texture heroTexture;

//    Clock for animation timing
    sf::Clock clock;


    Hero(float x, float y, std::vector<std::string> const& heroFrames);

    auto draw(sf::RenderWindow& window) -> void;

    auto moveRight() -> void;

    auto moveLeft() -> void;

    auto updateFrame() -> void;

};