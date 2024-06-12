#include "knife.hpp"

Knife::Knife(sf::Vector2f newPosition) : sprite(), texture(), timer(){
    texture.loadFromFile("../assets/hero/male/Bullet.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0, texture.getSize().x, texture.getSize().y));
    ongoingPosition = 0;
    position = newPosition;
    defaultPosition = newPosition.y;
    sprite.setPosition(position);
    sprite.setScale(0.4,0.4);
};

auto Knife::animation(float const& startTime) -> void{
    timer += startTime;
    if(timer >= 0.1f){
        timer = 0.0f;
        ongoingPosition + 1 < 8 ? ongoingPosition += 1 : ongoingPosition = 1;
        changePosition();
    }

}

auto Knife::changePosition() -> void {
    sprite.setPosition(position.x, defaultPosition - 10 * ongoingPosition);
}

auto Knife::getSprite() const -> sf::Sprite {
    return sprite;
}
