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

auto Hero::animation(std::vector<std::string> const& frames, float const& startTime) -> void{
    auto nextFrame = (currentFrame + 1) % frames.size();
    timer += startTime;
    if(timer >= 0.1f){
        timer = 0.0f;
        heroTexture.loadFromFile(frames[nextFrame]);
        heroSprite.setTexture(heroTexture);
        currentFrame = nextFrame;
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
}

Hero::Hero(){
    changeFrame(frames["Idle"][0]);
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

auto Hero::gravityEffect() -> void{
    position += gravityVelocity;
    updatePosition();
}
