#include "hero.hpp"
#include "utitlities.hpp"

// Using fmt for debugging purposes
#include <fmt/core.h>
#include <fmt/ranges.h>


// Loading hero frames
std::map<std::string,std::vector<std::string>> Hero::frames = getFramesMap();

auto Hero::changeAnimation(std::string const& animKey) -> void{
    if(ongoingAnimation != animKey){
        timer = 0.0f;
        ongoingAnimation = animKey;
        ongoingFrame = 0;
        changeFrame(frames[ongoingAnimation][ongoingFrame]);
        fmt::println("Changed animation to: {}", animKey);
    }

}

auto Hero::animation(float const& startTime) -> void{
    auto nextFrame = (ongoingFrame + 1) % frames[ongoingAnimation].size();
    timer += startTime;
    if(timer >= 0.1f){
        timer = 0.0f;
        ongoingFrame = nextFrame;
        changeFrame(frames[ongoingAnimation][ongoingFrame]);
    }

}

auto Hero::updatePosition(sf::Vector2f const& newPosition) -> void{
    position = newPosition;
    heroSprite.setPosition(position);
}

auto Hero::updatePosition() -> void {
    heroSprite.setPosition(position);
}

auto Hero::changeFrame(std::string const& framePath) -> void {
    heroTexture.loadFromFile(framePath);
    heroSprite.setTexture(heroTexture);
    heroSprite.setTextureRect(sf::IntRect(0,0, heroTexture.getSize().x, heroTexture.getSize().y));
    fmt::println("Successfully changed frame to {}", framePath);
}

Hero::Hero(){
    changeAnimation("Idle");
    isSliding = false;
    heroSprite.setScale(0.3,0.3);
    fmt::println("Hero initialized successfully");
}

auto Hero::setStartingPosition(sf::Sprite const& ground) -> void {
    updatePosition(sf::Vector2f(1,ground.getPosition().y - 2*ground.getTexture()->getSize().y));
    fmt::println("Hero starting position set to x = {}, y = {}", heroSprite.getPosition().x, heroSprite.getPosition().y);
}

auto Hero::getHeroSprite() -> sf::Sprite {
    return heroSprite;
}


// TODO: frames animation while moving right
auto Hero::moveRight() -> void{
    position += movementVelocity;
    updatePosition();
}

auto Hero::moveLeft() -> void{
    position -= movementVelocity;
    updatePosition();
}

auto Hero::jump() -> void {
    position += jumpingVelocity;
    updatePosition();
}

auto Hero::slide() -> void{
    position += slideVelocity;
    position += movementVelocity;
    updatePosition();
}

auto Hero::backFromSliding(sf::Sprite const& ground) -> void{
    auto newPosition = sf::Vector2f(heroSprite.getPosition().x, ground.getPosition().y - 2*ground.getTexture()->getSize().y);
    position = newPosition;
    updatePosition();
}

auto Hero::gravityEffect() -> void{
    position += gravityVelocity;
    updatePosition();
}