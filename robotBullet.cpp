#include "robotBullet.hpp"

#include <fmt/core.h>

RobotBullet::RobotBullet(const sf::Vector2f &robotPosition) : Bullet(robotPosition, false) {
    position += sf::Vector2f(30,0);
}

auto RobotBullet::move(int const& currentLevel) -> void{
    if(currentLevel < 5){
        position -= sf::Vector2f(15,0);
    } else if(currentLevel < 10){
        position -= sf::Vector2f(16,0);
    } else{
        position -= sf::Vector2f (17,0);
    }
    sprite.setPosition(position);
}
