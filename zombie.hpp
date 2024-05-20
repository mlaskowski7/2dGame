#include "character.hpp"


class Zombie : public Character{

    std::string gender;
    bool isDead;
    sf::Clock clock;
    bool clockRestarted;

public:
//    Default constructor
    Zombie(std::string const& gender);

    auto move() -> void;

    auto setStartingPosition(sf::Sprite const& ground) -> void override;

    auto getIsDead() const -> bool;


    auto restartZombieClock() -> void;
};