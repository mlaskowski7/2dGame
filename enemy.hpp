#include "character.hpp"
#include "utilities.hpp"

#include <SFML/Graphics.hpp>

class Enemy : public Character{

    int healthPoints;

public:

    bool killing;

    sf::Clock killingClock;

    Enemy();

    auto setStartingPosition(sf::Sprite const& ground) -> void override;

    auto kill() -> void;

    auto reduceHealthPoint() -> int;
    auto getHealthPoints() -> int;
};
