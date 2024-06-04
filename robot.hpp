#pragma once

#include "character.hpp"
#include "utilities.hpp"

class Robot : public Character{
    int healthPoints;

public:
    Robot();

    auto setStartingPosition(sf::Sprite const& ground) -> void override;

    auto kill() -> void;

    auto reduceHealthPoint() -> int;
    auto getHealthPoints() -> int;
};
