#include "character.hpp"


class Hero : public Character{

    int score;

//    Vectors storing values of velocities for each movement

    sf::Vector2f gravityVelocity = sf::Vector2f(0,3);
    sf::Vector2f jumpingVelocity = sf::Vector2f(0.0f,-100);
    sf::Vector2f slideVelocity = sf::Vector2f(7,30);

    sf::Clock deadTimeClock;

    bool isDead;


//    public methods used by main
    public:
//        Default constructor
        Hero();

//        New game hero init
        auto newGame(sf::Sprite const& ground) -> void;

//        Score getter
        auto getScore() const -> int;

//        Score setter
        auto setScore(int const& newScore ) -> void;

        auto getIsDead() const -> bool;

        auto getDeadTimeClock() const -> sf::Clock;

//      void used to kill hero
        auto kill() -> void;

//        Hero gravity (fall when not touching ground)
        auto gravityEffect() -> void;

//        Hero Controls
        auto moveRight() -> void;
        auto moveLeft() -> void;
        auto jump() -> void;
        auto slide() -> void;

        auto backToIdle(sf::Sprite const& ground) -> void;

//        Void used to return hero from sliding position
        auto backFromSliding(sf::Sprite const& ground) -> void;
//        Boolean used to determine whether hero is sliding
        bool isSliding;

//        Starting position void override
        auto setStartingPosition(sf::Sprite const& ground) -> void override;








};