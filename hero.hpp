#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

struct Hero{

    float positionX;
    float positionY;
    static const auto movementSpeed = 10;

    enum framesNames{
        STANDING,
        RUNNING_FORWARD,
        CRAWLING
    };

//    Hero Frames Collection
    static std::map<framesNames, std::string> frames;

    sf::Sprite heroSprite;
    sf::Texture heroTexture;

//    Clock for animation timing
    sf::Clock clock;


    Hero(float x, float y);

    auto draw(sf::RenderWindow& window) -> void;

    auto moveRight() -> void;

    auto moveLeft() -> void;

    auto updateFrame() -> void;

};