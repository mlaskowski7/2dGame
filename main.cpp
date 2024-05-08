#include <fmt/core.h>
#include <fmt/ranges.h>

#include <SFML/Graphics.hpp>

#include "hero.hpp"

// images were generated using DALL-E AI tool ( hero frames )

auto main() -> int {

//    Window Declaration
    auto window = sf::RenderWindow(
            sf::VideoMode({800,512}),
            "2D Game", sf::Style::Default,
            sf::ContextSettings(0,0, 8)
            );

//    Background Sprite Declaration
    auto bg = sf::Sprite();
    sf::Texture bgTexture;
    bgTexture.loadFromFile("assets/background.png");
    bg.setTexture(bgTexture);

//    Ground Sprite Declaration
    auto ground  = sf::Sprite();
    sf::Texture groundTexture;
    groundTexture.loadFromFile("assets/ground.png");
    ground.setTexture(groundTexture);
    ground.setPosition(0, window.getSize().y - groundTexture.getSize().y);
    ground.setScale(10,1);

//    Hero Declaration
    auto heroFrames = std::vector<std::string>{"assets/heroStandingFrame.png","assets/runningAnimationPhase1.png","assets/runningAnimationPhase2.png"};
    auto hero = Hero(1,window.getSize().y - groundTexture.getSize().y);


//    Game Loop
    while(window.isOpen()){
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }

        /*if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) hero.moveLeft();
            if (event.key.code == sf::Keyboard::Right) hero.moveRight();
//            if (event.key.code == sf::Keyboard::Up) ;
//            if (event.key.code == sf::Keyboard::Down);
        }*/

        window.clear(sf::Color::Black);
        window.draw(bg);
        window.draw(ground);
        window.draw(hero.heroSprite);
        window.display();


    }

}
