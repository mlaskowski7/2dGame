#include <fmt/core.h>
#include <fmt/ranges.h>

#include <SFML/Graphics.hpp>

#include "hero.hpp"

// CREDITS:
// hero textures were taken from https://www.gameart2d.com/
// ground textures, background textures were generated using DALL-E AI tool

auto rightArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto leftArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto upArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto downArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock) -> void;


auto main() -> int {

//    Window Declaration
    auto window = sf::RenderWindow(
            sf::VideoMode({1792,1024}),
            "2D Game", sf::Style::Default,
            sf::ContextSettings(0,0, 8)
            );

//    Background Sprite Declaration
    auto bg = sf::Sprite();
    sf::Texture bgTexture;
    bgTexture.loadFromFile("../assets/background/background.png");
    bg.setTexture(bgTexture);

//    Ground Sprite Declaration
    auto ground  = sf::Sprite();
    sf::Texture groundTexture;
    groundTexture.loadFromFile("../assets/ground/groundDoubled.png");
    ground.setTexture(groundTexture);
    ground.setPosition(sf::Vector2f(0, window.getSize().y - groundTexture.getSize().y + 5));


//    Hero Declaration
    auto hero = Hero();
    hero.setStartingPosition(ground);

//    Boolean for blocking jump during gravity falling (to prevent flying effect)
    bool jumpBlocked = false;

//    sfml clock for animations
    auto clock = sf::Clock();
    auto lastMovementClock = sf::Clock();

    auto startTime = float();

//    Game Loop
    while(window.isOpen()){
        startTime = clock.restart().asSeconds();
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) leftArrowOnClick(hero, lastMovementClock, ground);
            if (event.key.code == sf::Keyboard::Right) rightArrowOnClick(hero, lastMovementClock, ground);
            if (event.key.code == sf::Keyboard::Up) upArrowOnClick(hero, jumpBlocked, lastMovementClock, ground);
            if (event.key.code == sf::Keyboard::Down) downArrowOnClick(hero, jumpBlocked, lastMovementClock);
        }


//        Back to idle if standing ( prevents running when not moving )
        if(lastMovementClock.getElapsedTime().asSeconds() > 0.5){
            if(hero.getHeroSprite().getPosition().y > ground.getPosition().y - 2*groundTexture.getSize().y){
                hero.backFromSliding(ground);
            }
            hero.changeAnimation("Idle");

        }

        if(hero.getHeroSprite().getPosition().y < ground.getPosition().y - 2*groundTexture.getSize().y){
            jumpBlocked = true;
            for(auto i = 0; i < 10; i++){
                hero.gravityEffect();
            }
        }else if(hero.getHeroSprite().getPosition().y > ground.getPosition().y - 2*groundTexture.getSize().y){
            hero.isSliding = true;
        } else{
            jumpBlocked = false;
            hero.isSliding = false;
        }

        hero.animation(startTime);

        window.clear(sf::Color::Black);
        window.draw(bg);
        window.draw(ground);
        window.draw(hero.getHeroSprite());
        window.display();


    }

}

auto rightArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getHeroSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    hero.changeAnimation("Run");
    lastMovementClock.restart();
    for(auto i = 0; i < 1000; i++){
        hero.moveRight();
    }
}

auto leftArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getHeroSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    hero.changeAnimation("RunBackwards");
    lastMovementClock.restart();
    for(auto i = 0; i < 1000; i++){
        hero.moveLeft();
    }
}

auto upArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getHeroSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    if(!jumpBlocked){
        hero.changeAnimation("Jump");
        lastMovementClock.restart();
        for(auto i = 0; i < 6000; i++){
            hero.jump();
        }
    }
}

auto downArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock) -> void{
    if(!hero.isSliding && !jumpBlocked){
        hero.changeAnimation("Slide");
        lastMovementClock.restart();
        for(auto i = 0; i < 1500; i++){
            hero.slide();
        }
    }

}