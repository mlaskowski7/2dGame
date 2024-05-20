#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include <fmt/core.h>

class Character{

protected:
//    sf Sprite
    sf::Sprite sprite;

//    sf Texture
    sf::Texture texture;

//    character's current position
    sf::Vector2f position;

//    character's movement velocity
    sf::Vector2f movementVelocity;

//    animations stuff
    std::string ongoingAnimation = "Non";
    float timer;
    size_t ongoingFrame;
    std::map<std::string, std::vector<std::string>> frames;

//    voids used to reduce repeating boilerplate code
    auto changeFrame(std::string const& framePath) -> void;
    auto updatePosition() -> void;

    Character();

public:
    auto getSprite() const -> sf::Sprite;

    auto updatePosition(sf::Vector2f const& newPosition) -> void;

    auto animation(float const& startTime) -> void;

    auto changeAnimation(std::string const& animKey) -> void;

    virtual auto setStartingPosition(sf::Sprite const& ground) -> void;

};


