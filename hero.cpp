#include "hero.hpp"
#include "utilities.hpp"


// Default constructor implementation
Hero::Hero() : Character(){
    frames = getFramesMap("../assets/hero");
    changeAnimation("Idle");
    movementVelocity = sf::Vector2f(10,0);
    score = 0;
    isSliding = false;
}

// Score getter implementation
auto Hero::getScore() const -> int {
    return score;
}

// Score setter implementation
auto Hero::setScore(int const& newScore ) -> void{
    score = newScore;
}

// Hero controls implementation
auto Hero::moveRight() -> void{
    position += movementVelocity;
    score += 1;
    updatePosition();
}

auto Hero::moveLeft() -> void{
    position -= movementVelocity;
    score -= 1;
    updatePosition();
}

auto Hero::jump() -> void {
    position += jumpingVelocity;
    updatePosition();
}

auto Hero::slide() -> void{
    position += slideVelocity;
    updatePosition();
}

auto Hero::backFromSliding(sf::Sprite const& ground) -> void{
    auto newPosition = sf::Vector2f(sprite.getPosition().x, ground.getPosition().y - 2*ground.getTexture()->getSize().y);
    position = newPosition;
    updatePosition();
}

auto Hero::gravityEffect() -> void{
    position += gravityVelocity;
    updatePosition();
}

auto Hero::setStartingPosition(sf::Sprite const& ground) -> void {
    updatePosition(sf::Vector2f(1,ground.getPosition().y - 2*ground.getTexture()->getSize().y));
    fmt::println("Hero starting position set to x = {}, y = {}", sprite.getPosition().x, sprite.getPosition().y);
}