#include <fmt/core.h>
#include <fmt/ranges.h>

#include <SFML/Graphics.hpp>

#include "hero.hpp"

// CREDITS:
// hero textures were taken from https://www.gameart2d.com/
// ground textures, background textures were generated using DALL-E AI tool

auto rightArrowOnClick(Hero& hero, sf::Clock& clock) -> void;
auto leftArrowOnClick(Hero& hero, sf::Clock& clock) -> void;
auto upArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& clock) -> void;
auto downArrowOnClick(Hero& hero, sf::Clock& clock) -> void;


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
    groundTexture.loadFromFile("../assets/ground/ground.png");
    ground.setTexture(groundTexture);
    ground.setPosition(0, window.getSize().y - groundTexture.getSize().y);


//    Hero Declaration
    auto hero = Hero();
    hero.setStartingPosition(ground);

//    Boolean for blocking jump during gravity falling (to prevent flying effect)
    bool jumpBlocked = false;

//    sfml clock for animations
    auto clock = sf::Clock();

//    Game Loop
    while(window.isOpen()){
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) leftArrowOnClick(hero, clock);
            if (event.key.code == sf::Keyboard::Right) rightArrowOnClick(hero, clock);
            if (event.key.code == sf::Keyboard::Up) upArrowOnClick(hero, jumpBlocked, clock);
            if (event.key.code == sf::Keyboard::Down) downArrowOnClick(hero, clock);
        }

        if(hero.heroSprite.getPosition().y < ground.getPosition().y - 2*groundTexture.getSize().y){
            jumpBlocked = true;
            for(auto i = 0; i < 10; i++){
                hero.gravityEffect();
            }
        } else{
            jumpBlocked = false;
        }

        hero.animation(Hero::frames["Idle"], clock.restart().asSeconds());

        window.clear(sf::Color::Black);
        window.draw(bg);
        window.draw(ground);
        window.draw(hero.heroSprite);
        window.display();


    }

}

auto rightArrowOnClick(Hero& hero, sf::Clock& clock) -> void{
    hero.animation(Hero::frames["Run"], clock.restart().asSeconds());
    for(auto i = 0; i < 1000; i++){
        hero.moveRight();
    }
}

auto leftArrowOnClick(Hero& hero, sf::Clock& clock) -> void{
    for(auto i = 0; i < 1000; i++){
        hero.moveLeft();
    }
}

auto upArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& clock) -> void{
    if(!jumpBlocked){
        for(auto i = 0; i < 5000; i++){
            hero.jump();
        }
    }
}

auto downArrowOnClick(Hero& hero, sf::Clock& clock) -> void{
}