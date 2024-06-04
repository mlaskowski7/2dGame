#include "enemy.hpp"

Enemy::Enemy() : Character(){
    fmt::println("enemy constructor called");

    fmt::println("enemy constructor passed");
}

auto Enemy::setStartingPosition(const sf::Sprite &ground) -> void {
    updatePosition(sf::Vector2f(1500, ground.getPosition().y - 2.25*ground.getTexture()->getSize().y));
    fmt::println("firstEnemy position set to x = {}, y = {}",sprite.getPosition().x,sprite.getPosition().y);
}

auto Enemy::kill() -> void {
    isDead = true;
    changeAnimation("Dead");
    deadTimeClock.restart();
}

auto Enemy::reduceHealthPoint() -> int {
    healthPoints--;
    return healthPoints;
}

auto Enemy::getHealthPoints() -> int {
    return healthPoints;
}