#pragma once

#include "character.hpp"
#include "utilities.hpp"
#include "robotBullet.hpp"

class Robot : public Character{
    int healthPoints;

    std::unique_ptr<RobotBullet> bulletPointer;

public:

    bool killing;

    sf::Clock killingClock;

    Robot();

    auto setStartingPosition(sf::Sprite const& ground) -> void override;

    auto kill() -> void;

    auto reduceHealthPoint() -> int;
    auto getHealthPoints() -> int;

//        Bullet pointer getter
    auto getBulletSprite() -> sf::Sprite;
    auto getIsBulletInitialized() -> bool;

//        void used to display bullet
    auto drawBullet(sf::RenderWindow& window) -> void;

//        void used to initialize bullet after firing it
    auto initBullet() -> void;
    auto deleteBullet() -> void;
    auto moveBullet(int const& currentLevel) -> void;

};
