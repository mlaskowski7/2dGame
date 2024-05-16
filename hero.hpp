#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

struct Hero{

    sf::Vector2f position;

    sf::Vector2f movementVelocity = sf::Vector2f(0.02f,0);
    sf::Vector2f gravityVelocity = sf::Vector2f(0,0.02f);
    sf::Vector2f jumpingVelocity = sf::Vector2f(0,-0.02f);


//    Hero Frames Collection
    static std::map<std::string, std::vector<std::string>> frames;

    sf::Sprite heroSprite;
    sf::Texture heroTexture;

//    Default constructor
    Hero();

//    Animations stuff
    std::string ongoingAnimation;
    float timer = 0.0f;
    size_t ongoingFrame = 0;
    auto changeAnimation(std::string const& animKey) -> void;
    auto animation(float const& startTime) -> void;






//    Void used to set starting point for the hero at the beginning of the game and maybe also after changing the floor
    auto setStartingPosition(sf::Sprite const& ground) -> void;

//    Functions used to not repeat boilerplate code
    auto changeFrame(std::string const& framePath) -> void;
    auto updatePosition(sf::Vector2f const& newPosition) -> void;
    auto updatePosition() -> void;



//    Hero gravity
    auto gravityEffect() -> void;

//    Hero Controls
    auto moveRight() -> void;

    auto moveLeft() -> void;

    auto jump() -> void;




};