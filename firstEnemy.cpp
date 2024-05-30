#include "firstEnemy.hpp"

FirstEnemy::FirstEnemy() : Character(), killingClock(), killing(){
    frames = getFramesMap("../assets/firstEnemyBackwards");
    healthPoints = 3;
    changeAnimation("Idle");
    movementVelocity = sf::Vector2f (1,0);
}

auto FirstEnemy::setStartingPosition(const sf::Sprite &ground) -> void {
    updatePosition(sf::Vector2f(1500, ground.getPosition().y - 2.25*ground.getTexture()->getSize().y));
    fmt::println("firstEnemy position set to x = {}, y = {}",sprite.getPosition().x,sprite.getPosition().y);
}

auto FirstEnemy::kill() -> void {
    fmt::println("first enemy killed called");
    isDead = true;
    changeAnimation("Dead");
    deadTimeClock.restart();
}

auto FirstEnemy::reduceHealthPoint() -> int {
    healthPoints--;
    fmt::println("enemy health: {}", healthPoints);
    return healthPoints;
}

auto FirstEnemy::getHealthPoints() -> int {
    return healthPoints;
}