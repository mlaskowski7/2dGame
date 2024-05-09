#include "hero.hpp"

#include <map>

// Using fmt for debugging purposes
#include <fmt/core.h>

std::map<Hero::framesNames, std::string> Hero::frames = {{Hero::framesNames::STANDING, "../assets/hero/heroStandingFrame.png"},{Hero::framesNames::RUNNING_FORWARD, "../assets/hero/heroRunningForwardFrame.png"},{Hero::framesNames::CRAWLING,"../assets/hero/heroCrawlingFrame.png"}};

Hero::Hero(float x, float y){
    positionX = x;
    positionY = y;
    heroTexture.loadFromFile(frames[framesNames::STANDING]);
    heroSprite.setTexture(heroTexture);
    heroSprite.setScale(0.3,0.3);
    heroSprite.setPosition(positionX, positionY);
    fmt::println("Hero initialized successfully");
}

auto Hero::setStartingPosition(sf::Sprite const& ground) -> void {
    positionX = 1;
    positionY = ground.getPosition().y - 2*ground.getTexture()->getSize().y;
    heroSprite.setPosition(positionX, positionY);
    fmt::println("Hero starting postion set to x = {}, y = {}", heroSprite.getPosition().x, heroSprite.getPosition().y);
}


/*
auto Hero::moveRight() -> void{
    positionX += movementSpeed;
    heroSprite.setPosition(positionX,positionY);
    updateFrame();
}

auto Hero::moveLeft() -> void{
    positionX -= movementSpeed;
    heroSprite.setPosition(positionX,positionY);
}

auto Hero::updateFrame() -> void{
    if(clock.getElapsedTime().asMilliseconds() > 200){
        currentFrame + 1 < frames.size() ? currentFrame += 1 : currentFrame = 0;
        heroTexture.loadFromFile(frames[currentFrame]);
        heroSprite.setTexture(heroTexture);
        clock.restart();
    }
}*/
