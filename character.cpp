#include "character.hpp"

Character::Character() : deadTimeClock(){
    sprite.setScale(0.3,0.3);
    timer = 0.0f;
    ongoingFrame = 0;
    isDead = false;
    fmt::println("Character initialized successfully");
}

auto Character::getIsDead() const -> bool{
    return isDead;
}

auto Character::setIsDead(bool const& value) -> void {
    isDead = value;
}

auto Character::getDeadTimeClock() const -> sf::Clock{
    return deadTimeClock;
}

auto Character::changeAnimation(std::string const& animKey) -> void{
    if(ongoingAnimation != animKey){
        timer = 0.0f;
        ongoingAnimation = animKey;
        ongoingFrame = 0;
        changeFrame(frames[ongoingAnimation][ongoingFrame]);
//        fmt::println("Changed animation to: {}", animKey);
    }

}

auto Character::animation(float const& startTime) -> void{
    auto nextFrame = (ongoingFrame + 1) % frames[ongoingAnimation].size();
    timer += startTime;
    if(timer >= 0.1f){
        timer = 0.0f;
        ongoingFrame = nextFrame;
        changeFrame(frames[ongoingAnimation][ongoingFrame]);
    }

}

auto Character::changeFrame(std::string const& framePath) -> void {
    texture.loadFromFile(framePath);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0, texture.getSize().x, texture.getSize().y));
}

auto Character::updatePosition(sf::Vector2f const& newPosition) -> void{
    position = newPosition;
    sprite.setPosition(position);
}

auto Character::updatePosition() -> void {
    sprite.setPosition(position);
}

auto Character::getSprite() const -> sf::Sprite {
    return sprite;
}

auto Character::getOngoingAnimation() const -> std::string {
    return ongoingAnimation;
}

auto Character::setStartingPosition(const sf::Sprite &ground) -> void {

}

auto Character::updateVelocity(sf::Vector2f const& newVelocity) -> bool {
    if(movementVelocity != newVelocity){
        movementVelocity = newVelocity;
        return true;
    }
    return false;

}
