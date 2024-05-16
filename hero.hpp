#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Hero{

//    Hero Sprite and hero Texture
    sf::Sprite heroSprite;
    sf::Texture heroTexture;

//    Vector holding current hero position
    sf::Vector2f position;

//    Vectors storing values of velocities for each movement
    sf::Vector2f movementVelocity = sf::Vector2f(0.02f,0);
    sf::Vector2f gravityVelocity = sf::Vector2f(0,0.02f);
    sf::Vector2f jumpingVelocity = sf::Vector2f(0.008f,-0.02f);
    sf::Vector2f slideVelocity = sf::Vector2f(0.02f,0.02f);

//    Animations stuff
    std::string ongoingAnimation;
    float timer = 0.0f;
    size_t ongoingFrame = 0;
//    Hero Frames Map (on keys has name of animation and on values has collection of paths for each frame in an animation)
    static std::map<std::string, std::vector<std::string>> frames;

//    Functions used to not repeat boilerplate code
    auto changeFrame(std::string const& framePath) -> void;
    auto updatePosition(sf::Vector2f const& newPosition) -> void;
    auto updatePosition() -> void;

//    public methods used by main
    public:
//        Default constructor
        Hero();

//        Void used to set starting point for the hero at the beginning of the game and maybe also after changing the floor
        auto setStartingPosition(sf::Sprite const& ground) -> void;

//        HeroSprite getter
        auto getHeroSprite() -> sf::Sprite;

//        Void that is conducting animations
        auto animation(float const& startTime) -> void;
//        Void changing ongoing hero animation
        auto changeAnimation(std::string const& animKey) -> void;

//        Hero gravity (fall when not touching ground)
        auto gravityEffect() -> void;

//        Hero Controls
        auto moveRight() -> void;
        auto moveLeft() -> void;
        auto jump() -> void;
        auto slide() -> void;

//        Void used to return hero from sliding position
        auto backFromSliding(sf::Sprite const& ground) -> void;
//        Boolean used to determine whether hero is sliding
        bool isSliding;








};