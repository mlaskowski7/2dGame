#include "zombie.hpp"
#include "utilities.hpp"

#include <cstdlib>

Zombie::Zombie(std::string const& zombieGender) : Character(){
    gender = zombieGender;
    frames = getFramesMap("../assets/zombie/" + zombieGender);
    changeAnimation("Idle");
    movementVelocity = sf::Vector2f (0.002f,0);
}

auto Zombie::setStartingPosition(sf::Sprite const& ground) -> void {
    if(gender == "male"){
        updatePosition(sf::Vector2f(1,ground.getPosition().y - 2.2*ground.getTexture()->getSize().y));
    } else{
        updatePosition(sf::Vector2f(1,ground.getPosition().y - 2.5*ground.getTexture()->getSize().y));
    }
    fmt::println("Hero starting position set to x = {}, y = {}", sprite.getPosition().x, sprite.getPosition().y);
}