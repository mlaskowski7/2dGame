#include "robot.hpp"

Robot::Robot() : Character(), killing(), killingClock(){
    frames = getFramesMap("../assets/robotBackwards");
    healthPoints = 3;
    changeAnimation("Idle");
    movementVelocity = sf::Vector2f (1,0);
}

auto Robot::setStartingPosition(const sf::Sprite &ground) -> void {
    updatePosition(sf::Vector2f(750, ground.getPosition().y - 2.25*ground.getTexture()->getSize().y));
    fmt::println("Robot position set to x = {}, y = {}",sprite.getPosition().x,sprite.getPosition().y);
}

auto Robot::kill() -> void {
    fmt::println("robot killed called");
    isDead = true;
    changeAnimation("Dead");
    deadTimeClock.restart();
}

auto Robot::reduceHealthPoint() -> int {
    healthPoints--;
    fmt::println("enemy health: {}", healthPoints);
    return healthPoints;
}

auto Robot::getHealthPoints() -> int {
    return healthPoints;
}

auto Robot::getBulletSprite() -> sf::Sprite{
    return bulletPointer->getSprite();
}

auto Robot::drawBullet(sf::RenderWindow &window) -> void {
    if(bulletPointer != nullptr){
        window.draw(bulletPointer->getSprite());
    }
}

auto Robot::initBullet() -> void {
    bulletPointer = std::make_unique<RobotBullet>(position);
}

auto Robot::deleteBullet() -> void {
    bulletPointer = nullptr;
}

auto Robot::getIsBulletInitialized() -> bool {
    return bulletPointer != nullptr;
}

auto Robot::moveBullet(int const& currentLevel) -> void {
    if(bulletPointer != nullptr){
        bulletPointer->move(currentLevel);
    }
}