#include "firstEnemy.hpp"

FirstEnemy::FirstEnemy() : Character(){
    frames = getFramesMap("../assets/firstEnemyBackwards");
    changeAnimation("Idle");
    movementVelocity = sf::Vector2f (1,0);
}

auto FirstEnemy::setStartingPosition(const sf::Sprite &ground) -> void {
    updatePosition(sf::Vector2f(1500, ground.getPosition().y - 2.25*ground.getTexture()->getSize().y));
    fmt::println("firstEnemy position set to x = {}, y = {}",sprite.getPosition().x,sprite.getPosition().y);
}