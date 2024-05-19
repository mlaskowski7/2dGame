#include <fmt/core.h>
#include <fmt/ranges.h>

#include <SFML/Graphics.hpp>

#include <vector>
#include <cstdlib>
#include <ctime>

#include "hero.hpp"
#include "mainMenu.hpp"
#include "zombie.hpp"

// CREDITS:
// hero textures were taken from https://www.gameart2d.com/
// ground textures, background textures were generated using DALL-E AI tool

auto rightArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto rightArrowAfterJumpClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto leftArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto upArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto downArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock) -> void;

auto generateRandomGroundObstacles(std::vector<sf::Sprite*>& groundObstacles,sf::Sprite const& ground, sf::Texture const& groundObstacleTexture) -> void;
auto generateRandomFlyingObstacles(std::vector<sf::Sprite*>& flyingObstacles,sf::Sprite const& ground, sf::Texture const& flyingObstacleTexture) -> void;

auto generateZombie(std::vector<Zombie*>& zombies,sf::Sprite const& ground) -> void;


auto main() -> int {

//    Window Declaration
    auto window = sf::RenderWindow(
            sf::VideoMode({1700,1024}),
            "2D Game", sf::Style::Titlebar | sf::Style::Close,
            sf::ContextSettings(0,0, 8)
            );

//    random number generator
    std::srand(std::time(0));

//    Boolean determining whether game has started
    auto gameStarted = false;

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

//    Zombies pointers vector
    auto zombies = std::vector<Zombie*>();

//    Main Menu Object declaration
    auto mainMenu = MainMenu();

//    Boolean for blocking jump during gravity falling (to prevent flying effect)
    bool jumpBlocked = false;

//    sfml clock for animations
    auto clock = sf::Clock();
    auto lastMovementClock = sf::Clock();
    auto deadTimeClock = sf::Clock();

    auto startTime = float();

    auto groundObstacles = std::vector<sf::Sprite*>();
    auto groundObstacleTexture = sf::Texture();
    groundObstacleTexture.loadFromFile("../assets/obstacles/groundObstacle.png");


    auto flyingObstacles = std::vector<sf::Sprite*>();
    auto flyingObstacleTexture = sf::Texture();
    flyingObstacleTexture.loadFromFile("../assets/obstacles/flyingObstacle.png");


    auto heroDead = false;


//    Game Loop
    while(window.isOpen()){
        startTime = clock.restart().asSeconds();
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left){
                    auto mousePosition = sf::Mouse::getPosition(window);
                    if(mainMenu.getNewGameButton().getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)})){
                        hero.setStartingPosition(ground);
                        hero.setScore(0);
                        generateRandomGroundObstacles(groundObstacles, ground,groundObstacleTexture);
                        generateRandomFlyingObstacles(flyingObstacles,ground,flyingObstacleTexture);
                        gameStarted = true;
                        heroDead = false;
                        for(auto* zombie : zombies){
                            delete zombie;
                        }
                        zombies.clear();
                    } else if (mainMenu.getResumeGameButton().getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)})){
                        gameStarted = true;
                    } else if(mainMenu.getPauseGameButton().getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)})){
                        gameStarted = false;
                    }
                }
            } else if (event.type == sf::Event::KeyPressed && gameStarted && !heroDead) {
                if (event.key.code == sf::Keyboard::Left) leftArrowOnClick(hero, lastMovementClock, ground);
                if (event.key.code == sf::Keyboard::Right) {
                    if(hero.getSprite().getPosition().y < ground.getPosition().y - 2*groundTexture.getSize().y){
                        rightArrowAfterJumpClick(hero, lastMovementClock, ground);
                    } else{
                        rightArrowOnClick(hero, lastMovementClock, ground);
                    }
                }
                if (event.key.code == sf::Keyboard::Up) upArrowOnClick(hero, jumpBlocked, lastMovementClock, ground);
                if (event.key.code == sf::Keyboard::Down) downArrowOnClick(hero, jumpBlocked, lastMovementClock);
            }
        }




//        Back to idle if standing ( prevents running when not moving )
        if(lastMovementClock.getElapsedTime().asSeconds() > 0.3 && !heroDead){
            if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*groundTexture.getSize().y){
                hero.backFromSliding(ground);
            }
//            fmt::println("Changing animation to idle because of last movement");
            hero.changeAnimation("Idle");

        }

        if(hero.getSprite().getPosition().y < ground.getPosition().y - 2*groundTexture.getSize().y){
            jumpBlocked = true;
            for(auto i = 0; i < 15; i++){
                hero.gravityEffect();
            }
        }else if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*groundTexture.getSize().y){
            hero.isSliding = true;
        } else{
            jumpBlocked = false;
            hero.isSliding = false;
        }

//        Move hero to start if  touched the border of a window
        if(hero.getSprite().getPosition().x >= window.getSize().x){
            hero.setStartingPosition(ground);
            generateRandomGroundObstacles(groundObstacles, ground,groundObstacleTexture);
            generateRandomFlyingObstacles(flyingObstacles, ground, flyingObstacleTexture);

//            generate zombie
            generateZombie(zombies, ground);

        }

        hero.animation(startTime);

        window.clear(sf::Color::Black);
        window.draw(bg);
        window.draw(ground);
        mainMenu.displayScore(window, hero.getScore());
        if(!gameStarted){
            mainMenu.displayMainMenu(window);
        } else{
            mainMenu.displayPauseButton(window);
            window.draw(hero.getSprite());

            for(auto const& zombie : zombies){
                zombie->animation(startTime);
                window.draw(zombie->getSprite());
            }

            for(auto const& groundObstacle : groundObstacles){
                if(groundObstacle->getGlobalBounds().intersects(hero.getSprite().getGlobalBounds()) && !heroDead){
                    hero.changeAnimation("Dead");
                    heroDead = true;
                    deadTimeClock.restart();
                }
                window.draw(*groundObstacle);
            }

            for(auto const& flyingObstacle : flyingObstacles){
                if(flyingObstacle->getGlobalBounds().intersects(hero.getSprite().getGlobalBounds()) && !heroDead){
                    hero.changeAnimation("Dead");
                    heroDead = true;
                    deadTimeClock.restart();
                }
                window.draw(*flyingObstacle);
            }
        }

        if(deadTimeClock.getElapsedTime().asSeconds() > 0.7 && heroDead){
            gameStarted = false;
            hero.setStartingPosition(ground);
        }

        window.display();


    }

    for(auto* zombie : zombies){
        delete zombie;
    }

    for (auto* groundObstacle : groundObstacles) {
        delete groundObstacle;
    }

    for (auto* flyingObstacle : flyingObstacles) {
        delete flyingObstacle;
    }
}

auto rightArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    hero.changeAnimation("Run");
    lastMovementClock.restart();
    for(auto i = 0; i < 2000; i++){
        hero.moveRight();
    }
}

auto rightArrowAfterJumpClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    hero.changeAnimation("Glide");
    lastMovementClock.restart();
    for(auto i = 0; i < 2000; i++){
        hero.moveRight();
    }
}

auto leftArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    hero.changeAnimation("RunBackwards");
    lastMovementClock.restart();
    for(auto i = 0; i < 2000; i++){
        hero.moveLeft();
    }
}

auto upArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    if(!jumpBlocked){
        hero.changeAnimation("Jump");
        lastMovementClock.restart();
        for(auto i = 0; i < 18000; i++){
            hero.jump();
        }
    }
}

auto downArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock) -> void{
    if(!hero.isSliding && !jumpBlocked){
        hero.changeAnimation("Slide");
        for(auto i = 0; i < 1500; i++){
            hero.slide();
        }
    } else if(!jumpBlocked){
        for(auto i = 0; i < 1000; i++){
            hero.moveRight();
        }
    }
    lastMovementClock.restart();

}

auto generateRandomGroundObstacles(std::vector<sf::Sprite*>& groundObstacles,sf::Sprite const& ground, sf::Texture const& groundObstacleTexture) -> void{

    for(auto* groundObstacle : groundObstacles){
        delete groundObstacle;
    }
    groundObstacles.clear();

    auto numberOfObstacles = std::rand() % 3;
    fmt::println("Generating {} ground obstacles", numberOfObstacles);
    for(auto i = 0; i < numberOfObstacles; i++){
        auto* obstacle = new sf::Sprite;
        auto positionX = std::rand() % 1500;
        auto position = sf::Vector2f(positionX + 100, ground.getPosition().y - ground.getTexture()->getSize().y);
        obstacle->setPosition(position);
        obstacle->setTexture(groundObstacleTexture);
        obstacle->setScale(0.3,0.3);
        groundObstacles.push_back(obstacle);
    }
}

auto generateRandomFlyingObstacles(std::vector<sf::Sprite*>& flyingObstacles,sf::Sprite const& ground, sf::Texture const& flyingObstacleTexture) -> void{

    for(auto* flyingObstacle : flyingObstacles){
        delete flyingObstacle;
    }
    flyingObstacles.clear();

    auto numberOfObstacles = std::rand() % 3;
    fmt::println("Generating {} flying obstacles", numberOfObstacles);
    for(auto i = 0; i < numberOfObstacles; i++){
        auto* obstacle = new sf::Sprite;
        auto positionX = std::rand() % 1500;
        auto position = sf::Vector2f(positionX + 100, ground.getPosition().y - 3*ground.getTexture()->getSize().y);
        obstacle->setPosition(position);
        obstacle->setTexture(flyingObstacleTexture);
        obstacle->setScale(0.2,0.2);
        flyingObstacles.push_back(obstacle);
    }
}

auto generateZombie(std::vector<Zombie*>& zombies, sf::Sprite const& ground) -> void{
    for(auto* zombie : zombies){
        delete zombie;
    }
    zombies.clear();

    if(std::rand() %  2 == 0){
        auto* zombie = new Zombie(std::rand() % 2 == 0 ? "male" : "female");
        zombie->setStartingPosition(ground);
        zombies.push_back(zombie);
    }
}