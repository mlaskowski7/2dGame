#include "character.hpp"


class Zombie : public Character{

    std::string gender;
    sf::Clock clock;

public:
    Zombie(std::string const& gender);

    auto move() -> void;

    auto getGender() const -> std::string;

    auto setStartingPosition(sf::Sprite const& ground) -> void override;

    auto restartZombieClock() -> void;
};