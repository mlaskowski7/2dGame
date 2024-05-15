#include "hero.hpp"

#include <map>

// Using fmt for debugging purposes
#include <fmt/core.h>

std::map<Hero::framesNames, std::string> Hero::frames = {{Hero::framesNames::STANDING, "../assets/hero/heroStandingFrame.png"},{Hero::framesNames::RUNNING_FORWARD, "../assets/hero/heroRunningForwardFrame.png"},{Hero::framesNames::CRAWLING,"../assets/hero/heroCrawlingFrame.png"}};



auto Hero::updatePositionX(float x) -> void{
    positionX = x;
    heroSprite.setPosition(positionX, positionY);
}

auto Hero::updatePositionY(float y) -> void {
    positionY = y;
    heroSprite.setPosition(positionX, positionY);
}

auto Hero::changeFrame(Hero::framesNames const& frameName) -> void {
    heroTexture.loadFromFile(frames[frameName]);
    heroSprite.setTexture(heroTexture);
}

Hero::Hero(float x, float y){
    updatePositionX(x);
    updatePositionY(x);
    changeFrame(framesNames::STANDING);
    heroSprite.setScale(0.3,0.3);
    fmt::println("Hero initialized successfully");
}

auto Hero::setStartingPosition(sf::Sprite const& ground) -> void {
    positionX = 1;
    positionY = ground.getPosition().y - 2*ground.getTexture()->getSize().y;
    heroSprite.setPosition(positionX, positionY);
    fmt::println("Hero starting postion set to x = {}, y = {}", heroSprite.getPosition().x, heroSprite.getPosition().y);
}


// TODO: frames animation while moving right
auto Hero::moveRight() -> void{
    changeFrame(framesNames::RUNNING_FORWARD);
    positionX += MOVEMENT_SPEED;
    heroSprite.setPosition(positionX,positionY);

    changeFrame(framesNames::STANDING);
}

auto Hero::moveLeft() -> void{
    positionX -= MOVEMENT_SPEED;
    heroSprite.setPosition(positionX,positionY);
}

auto Hero::jump() -> void {
    positionY -= JUMPING_SPEED;
    heroSprite.setPosition(positionX, positionY);
}

auto Hero::gravityEffect() -> void{
    updatePositionY(positionY + GRAVITY);
}
