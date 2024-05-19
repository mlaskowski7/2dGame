#include "character.hpp"


class Hero : public Character{

    int score;

//    Vectors storing values of velocities for each movement

    sf::Vector2f gravityVelocity = sf::Vector2f(0,0.02f);
    sf::Vector2f jumpingVelocity = sf::Vector2f(0.0f,-0.02f);
    sf::Vector2f slideVelocity = sf::Vector2f(0.02f,0.02f);


//    public methods used by main
    public:
//        Default constructor
        Hero();

//        Score getter
        auto getScore() const -> int;

//        Score setter
        auto setScore(int const& newScore ) -> void;

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

//        Starting position void override
        auto setStartingPosition(sf::Sprite const& ground) -> void override;








};