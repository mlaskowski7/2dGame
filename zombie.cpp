#include "zombie.hpp"
#include "utilities.hpp"


Zombie::Zombie(std::string const& zombieGender) : Character(), clock(){
    gender = zombieGender;
    frames = getFramesMap("../assets/zombie/" + zombieGender);
    changeAnimation("Idle");
    movementVelocity = sf::Vector2f (2,0);
}

auto Zombie::setZombieIndex(int const& index) -> void{
    zombieIndex = index;
}

auto Zombie::setStartingPosition(sf::Sprite const& ground) -> void {
    if(gender == "male"){
        updatePosition(sf::Vector2f(1 + zombieIndex*30,ground.getPosition().y - 2.25*ground.getTexture()->getSize().y));
    } else{
        updatePosition(sf::Vector2f(1 + zombieIndex*30,ground.getPosition().y - 2.5*ground.getTexture()->getSize().y));
    }
    fmt::println("Zombie starting position set to x = {}, y = {}", sprite.getPosition().x, sprite.getPosition().y);
}

auto Zombie::move() -> void{

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

auto Zombie::restartZombieClock() -> void{
    clock.restart();
}