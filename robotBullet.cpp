#include "robotBullet.hpp"

#include <fmt/core.h>

RobotBullet::RobotBullet(const sf::Vector2f &robotPosition) : Bullet(robotPosition, false) {
    position += sf::Vector2f(30,0);
}

auto RobotBullet::move() -> void{
    position -= sf::Vector2f(15,0);
    sprite.setPosition(position);
}
