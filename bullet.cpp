#include "bullet.hpp"


Bullet::Bullet(sf::Vector2f const& heroPosition, bool const& isHero) {
    sprite = sf::Sprite();
    texture = sf::Texture();
    if(isHero){
        texture.loadFromFile("../assets/hero/male/Bullet.png");
    } else {
        texture.loadFromFile("../assets/robot/bullet.png");
    }
    sprite.setTexture(texture);
    sprite.setScale(0.4,0.4);
    if(isHero){
        position = heroPosition + sf::Vector2f(10,30);
    } else {
        position = heroPosition;
    }


    sprite.setPosition(position);
}

auto Bullet::move() -> void {
    position += sf::Vector2f(15,0);
    sprite.setPosition(position);
}

auto Bullet::getSprite() -> sf::Sprite {
    return sprite;
}