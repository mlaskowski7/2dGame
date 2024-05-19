#include "character.hpp"

Character::Character() {
    sprite.setScale(0.3,0.3);
    timer = 0.0f;
    ongoingFrame = 0;
    fmt::println("Character initialized successfully");
}

auto Character::changeAnimation(std::string const& animKey) -> void{
    if(ongoingAnimation != animKey){
        timer = 0.0f;
        ongoingAnimation = animKey;
        ongoingFrame = 0;
        changeFrame(frames[ongoingAnimation][ongoingFrame]);
        fmt::println("Changed animation to: {}", animKey);
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

auto Character::setStartingPosition(const sf::Sprite &ground) -> void {

}
