#include "character.hpp"


class Zombie : public Character{

    std::string gender;

public:
//    Default constructor
    Zombie(std::string const& gender);

//    auto move() -> void;

    auto setStartingPosition(sf::Sprite const& ground) -> void override;
};