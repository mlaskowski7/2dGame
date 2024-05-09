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

//    Default hero constructor for two arguments initializing positionX and positionY
    Hero(float x, float y);

//    Void used to set starting point for the hero at the beginning of the game and maybe also after changing the floor
    auto setStartingPosition(sf::Sprite const& ground) -> void;

    /*auto draw(sf::RenderWindow& window) -> void;

    auto moveRight() -> void;

    auto moveLeft() -> void;

    auto updateFrame() -> void;*/

};