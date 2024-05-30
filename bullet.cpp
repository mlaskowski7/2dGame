#include "bullet.hpp"


Bullet::Bullet(sf::Vector2f const& heroPosition) {
    sprite = sf::Sprite();
    texture = sf::Texture();
    texture.loadFromFile("../assets/hero/male/Bullet.png");
    sprite.setTexture(texture);
    sprite.setScale(0.4,0.4);
    position = heroPosition + sf::Vector2f(10,30);
    sprite.setPosition(position);
}

auto Bullet::move() -> void {
    position += sf::Vector2f(15,0);
    sprite.setPosition(position);
}

auto Bullet::getSprite() -> sf::Sprite {
    return sprite;
}