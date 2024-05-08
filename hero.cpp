#include "hero.hpp"
#include <chrono>
#include <thread>
#include <vector>

// TODO : fix the standing frame png
std::map<Hero::framesNames, std::string> Hero::frames = {{Hero::framesNames::STANDING, "assets/heroStandingFrame.png"},{Hero::framesNames::RUNNING_FORWARD, "assets/heroRunningFrame.png"},{Hero::framesNames::CRAWLING,"assets/heroCrawlingFrame.png"}};

Hero::Hero(float x, float y){
    positionX = x;
    positionY = y;
    heroTexture.loadFromFile(frames[framesNames::STANDING]);
    heroSprite.setTexture(heroTexture);
    heroSprite.setScale(0.2,0.2);
    heroSprite.setPosition(positionX, positionY);
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
