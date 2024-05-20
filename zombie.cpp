#include "zombie.hpp"
#include "utilities.hpp"


Zombie::Zombie(std::string const& zombieGender) : Character(), clock(){
    gender = zombieGender;
    clockRestarted = false;
    isDead = false;
    frames = getFramesMap("../assets/zombie/" + zombieGender);
    changeAnimation("Idle");
    movementVelocity = sf::Vector2f (2,0);
}

auto Zombie::setStartingPosition(sf::Sprite const& ground) -> void {
    if(gender == "male"){
        updatePosition(sf::Vector2f(1,ground.getPosition().y - 2.2*ground.getTexture()->getSize().y));
    } else{
        updatePosition(sf::Vector2f(1,ground.getPosition().y - 2.5*ground.getTexture()->getSize().y));
    }
    fmt::println("Hero starting position set to x = {}, y = {}", sprite.getPosition().x, sprite.getPosition().y);
}

auto Zombie::move() -> void{
    if(!isDead){
        if(ongoingAnimation == "Attack"){
            if(clock.getElapsedTime().asSeconds() > 0.7){
                changeAnimation("Walk");
            }
        } else{
            changeAnimation("Walk");
            position += movementVelocity;
            updatePosition();
        }


    }

}

auto Zombie::getIsDead() const -> bool {
    return isDead;
}

auto Zombie::restartZombieClock() -> void{
    clock.restart();
}