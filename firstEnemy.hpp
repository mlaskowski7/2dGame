#include "character.hpp"
#include "utilities.hpp"

#include <SFML/Graphics.hpp>

class FirstEnemy : public Character{

    int healthPoints = 5;

public:
    FirstEnemy();

    auto setStartingPosition(sf::Sprite const& ground) -> void override;
};
