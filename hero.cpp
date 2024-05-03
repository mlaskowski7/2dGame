#include "hero.hpp"
#include <chrono>
#include <thread>

Hero::Hero(float x, float y, std::vector<std::string> const& heroFrames){
    positionX = x;
    positionY = y;
    frames = heroFrames;
    heroTexture.loadFromFile(heroFrames[0]);
    heroSprite.setTexture(heroTexture);
    heroSprite.setPosition(positionX, positionY);
}

auto Hero::draw(sf::RenderWindow& window) -> void{
    window.draw(heroSprite);
}

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
}