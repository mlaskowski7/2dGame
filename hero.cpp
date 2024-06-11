#include "hero.hpp"
#include "utilities.hpp"


// Default constructor implementation
Hero::Hero() : Character(), isSlowed(), slowedClock(), moving(){
    frames = getFramesMap("../assets/hero/male");
    changeAnimation("Idle");
    movementVelocity = sf::Vector2f(6,0);
    score = 0;
    isSliding = false;
    bulletPointer = nullptr;
}

auto Hero::setMoving(Movement const& value) -> void {
    moving = value;
}

auto Hero::getMoving() const -> Movement {
    return moving;
}

auto Hero::newGame(sf::Sprite const& ground) -> void{
    setStartingPosition(ground);
    setScore(0);
    updateVelocity(sf::Vector2f(6,0));
    isDead = false;
}

auto Hero::getBulletSprite() -> sf::Sprite{
    return bulletPointer->getSprite();
}

auto Hero::drawBullet(sf::RenderWindow &window) -> void {
    if(bulletPointer != nullptr){
        window.draw(bulletPointer->getSprite());
    }
}

auto Hero::initBullet() -> void {
    bulletPointer = std::make_unique<Bullet>(position, true);
}

auto Hero::deleteBullet() -> void {
    bulletPointer = nullptr;
}

auto Hero::getIsBulletInitialized() -> bool {
    return bulletPointer != nullptr;
}

auto Hero::moveBullet() -> void {
    if(bulletPointer != nullptr){
        bulletPointer->move();
    }
}

// Score getter implementation
auto Hero::getScore() const -> int {
    return score;
}

// Score setter implementation
auto Hero::setScore(int const& newScore ) -> void{
    score = newScore;
}

auto Hero::slow() -> void {
    if(!isSlowed){
        movementVelocity -= sf::Vector2f(3.5,0);
        fmt::println("Hero movement velocity changed to {}", movementVelocity.x);
        isSlowed = true;
        slowedClock.restart();
    }

}

auto Hero::unslow() -> bool {
    if(isSlowed && slowedClock.getElapsedTime().asSeconds() > 5){
        movementVelocity += sf::Vector2f(3.5,0);
        fmt::println("Hero movement velocity changed to {}", movementVelocity.x);
        isSlowed = false;
        return true;
    }
    return false;
}

auto Hero::kill(sf::Sprite const& ground) -> void{
    if(isSliding){
        backFromSliding(ground);
    }
    changeAnimation("Dead");
    moving = Movement::STILL;
    isDead = true;
    fmt::println("Hero isDead: {}", isDead);
    deadTimeClock.restart();
}

// Hero controls implementation
auto Hero::moveRight() -> void{
    position += movementVelocity;
    score += 1;
    updatePosition();
}

auto Hero::moveLeft() -> void{
    position -= movementVelocity;
    score -= 1;
    updatePosition();
}

auto Hero::jump() -> void {
    position += jumpingVelocity;
    updatePosition();
}

auto Hero::slide() -> void{
    if(isSliding){
        position += slideVelocity - sf::Vector2f(0,30);
    } else{
        position += slideVelocity;
    }
    score += 1;

    updatePosition();
}

auto Hero::backToIdle(sf::Sprite const& ground) -> void{
    if(sprite.getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        backFromSliding(ground);
    }
    changeAnimation("Idle");
}

auto Hero::backFromSliding(sf::Sprite const& ground) -> void{
    auto newPosition = sf::Vector2f(sprite.getPosition().x, ground.getPosition().y - 2*ground.getTexture()->getSize().y);
    position = newPosition;
    updatePosition();
}

auto Hero::gravityEffect() -> void{
    position += gravityVelocity;
    updatePosition();
}

auto Hero::setStartingPosition(sf::Sprite const& ground) -> void {
    updatePosition(sf::Vector2f(1,ground.getPosition().y - 2*ground.getTexture()->getSize().y));
    fmt::println("Hero starting position set to x = {}, y = {}", sprite.getPosition().x, sprite.getPosition().y);
}