#include "character.hpp"
#include "utilities.hpp"

#include <SFML/Graphics.hpp>

class FirstEnemy : public Character{

    int healthPoints;

public:

    bool killing;

    sf::Clock killingClock;

    FirstEnemy();

    auto setStartingPosition(sf::Sprite const& ground) -> void override;

    auto kill() -> void;

    auto reduceHealthPoint() -> int;
    auto getHealthPoints() -> int;
};
