#include "character.hpp"


class Zombie : public Character{

    std::string gender;
    sf::Clock clock;
    int zombieIndex;

public:
    Zombie(std::string const& gender);

    auto setZombieIndex(int const& index) -> void;

    auto move() -> void;

    auto setStartingPosition(sf::Sprite const& ground) -> void override;

    auto restartZombieClock() -> void;
};