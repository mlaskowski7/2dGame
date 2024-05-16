#include "hero.hpp"

#include <filesystem>

// Using fmt for debugging purposes
#include <fmt/core.h>
#include <fmt/ranges.h>

//  Method that is used to populate image paths with the help of filesystem
auto getFramesMap() -> std::map<std::string, std::vector<std::string>>{
    auto result = std::map<std::string, std::vector<std::string>>();

    for(auto const& subdir : std::filesystem::directory_iterator("../assets/hero")){
        if(subdir.is_directory()){
            auto paths = std::vector<std::string>();
            for(auto const& image : std::filesystem::directory_iterator(subdir.path())){
                paths.push_back(image.path().string());
            }

            auto key = subdir.path().filename().string();
            result[key] = paths;
        }
    }
    fmt::println("Generated frames map - {}", result);
    return result;
}

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
    auto tempTexture = sf::Texture();
    tempTexture.loadFromFile(framePath);
    heroTexture = tempTexture;
    heroSprite.setTexture(heroTexture);
    fmt::println("Successfully changed frame to {}", framePath);
}

Hero::Hero(){
    changeAnimation("Run");
    changeAnimation("Idle");
    isSliding = false;
    heroSprite.setScale(0.3,0.3);
    fmt::println("Hero initialized successfully");
}

auto Hero::setStartingPosition(sf::Sprite const& ground) -> void {
    updatePosition(sf::Vector2f(1,ground.getPosition().y - 2*ground.getTexture()->getSize().y));
    fmt::println("Hero starting position set to x = {}, y = {}", heroSprite.getPosition().x, heroSprite.getPosition().y);
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