#pragma once

#include "character.hpp"
#include "bullet.hpp"
#include "movementEnum.hpp"

class Hero : public Character{

    std::string gender;
    int score;

//    bullet
    std::unique_ptr<Bullet> bulletPointer;

//    slowing hero func
    bool isSlowed;
    sf::Clock slowedClock;

//    Vectors storing values of velocities for each movement

    sf::Vector2f gravityVelocity = sf::Vector2f(0,3);
    sf::Vector2f jumpingVelocity = sf::Vector2f(0.0f,-40);
    sf::Vector2f slideVelocity = sf::Vector2f(5,30);

//    where hero is moving (2 for right, -2 for left, -1 for up, 1 for down, 0 for no movement)
     Movement moving;

//    public methods used by main
    public:
        Hero();

//        getter and setter movement
        auto setMoving(Movement const& value) -> void;
        auto getMoving() const -> Movement;

//        New game hero init
        auto newGame(sf::Sprite const& ground) -> void;

//        Bullet pointer getter
        auto getBulletSprite() -> sf::Sprite;
        auto getIsBulletInitialized() -> bool;

//        void used to display bullet
        auto drawBullet(sf::RenderWindow& window) -> void;

//        void used to initialize bullet after firing it
        auto initBullet() -> void;
        auto deleteBullet() -> void;
        auto moveBullet() -> void;

//        Score getter
        auto getScore() const -> int;

//        Score setter
        auto setScore(int const& newScore ) -> void;

//      void used to kill hero
        auto kill(sf::Sprite const& ground) -> void;

//        void used to slow hero when hittitng bush
        auto slow() -> void;

//        void used to undo slowing
        auto unslow() -> bool;

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
//        Boolean used to determine whether throwing ability is unlocked
        bool canThrow;

//        Starting position void override
        auto setStartingPosition(sf::Sprite const& ground) -> void override;








};