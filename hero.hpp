#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

struct Hero{

    float positionX;
    float positionY;
    static const auto MOVEMENT_SPEED = 10;
    static const auto GRAVITY = 10;
    static const auto JUMPING_SPEED = 20;

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

//    Functions used to not repeat boilerplate code
    auto changeFrame(framesNames const& frameName) -> void;
    auto updatePositionX(float x) -> void;
    auto updatePositionY(float y) -> void;

//    Hero gravity
    auto gravityEffect() -> void;

//    Hero Controls
    auto moveRight() -> void;

    auto moveLeft() -> void;

    auto jump() -> void;




};