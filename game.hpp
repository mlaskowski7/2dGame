#pragma once

#include <SFML/Graphics.hpp>

#include "hero.hpp"
#include "zombie.hpp"
#include "firstEnemy.hpp"
#include "robot.hpp"
#include "mainMenu.hpp"
#include "utilities.hpp"
#include "dataFileEnum.hpp"

class Game{

//    Window initialization
    sf::RenderWindow window = sf::RenderWindow(
            sf::VideoMode({1700,1024}),
            "2D Game", sf::Style::Titlebar | sf::Style::Close,
            sf::ContextSettings(0,0, 8)
    );
    MainMenu mainMenu;

    std::string const dataFile = "../data.txt";

//    Game management
    int highScore;
    bool gameStarted;
    bool jumpBlocked;
    bool qBlocked;
//    level tracker
    int currentLevel;
//    dead message displayed after game over
    std::string deadMessage;


    //    map
    sf::Sprite bg;
    sf::Sprite ground;
    sf::Texture groundTexture;

//    Game entities
    Hero hero;
//    Place for zombie pointer ( nullptr when no zombie )
    std::unique_ptr<Zombie> zombiePointer;
//    Place for firstEnemy pointer ( nullptr when no firstEnemy)
    std::unique_ptr<FirstEnemy> firstEnemyPointer;
//    Place for robot pointer ( nullptr when no robot)
    std::unique_ptr<Robot> robotPointer;
//    ground obstacles
    std::vector<std::unique_ptr<sf::Sprite>> groundObstacles;
    sf::Texture groundObstacleTexture;
//    flying obstacles
    std::vector<std::unique_ptr<sf::Sprite>> flyingObstacles;
    sf::Texture flyingObstacleTexture;
//    bush obstacles
    std::vector<std::unique_ptr<sf::Sprite>> bushes;
    sf::Texture bushTexture;

//    sfml clock for animations
    sf::Clock clock;
//    clock used to track time in current level
    sf::Clock levelClock;
//    clock used to track hero's last movement so that the hero goes back to idle when movement is finished
    sf::Clock lastMovementClock;
//    determining whether the message should still be displayed
    sf::Clock messageClock;
    bool isMessageDisplayed;
//    conducting robot shots
    sf::Clock robotShootingClock;
    bool robotShotFired;

// main menu on click functions declaration
    auto newGameOnclick() -> void;

// data file integration methods
    auto saveGame() -> void;
    auto loadGame() -> void;
    auto checkHighScore() -> void;

// hero controls on click functions declaration
    auto rightArrowOnClick() -> void;
    auto rightArrowAfterJumpClick() -> void;
    auto leftArrowOnClick() -> void;
    auto leftArrowAfterJumpClick() -> void;
    auto upArrowOnClick() -> void;
    auto downArrowOnClick() -> void;
    auto qOnClick() -> void;
    auto wOnClick() -> void;

// game state management functions
    auto nextLevel() -> void;

// functions used to randomly generate obstacles and enemies
    auto generateRandomGroundObstacles() -> void;
    auto loadGroundObstacle(sf::Vector2f const& position) -> void;
    auto generateRandomFlyingObstacles() -> void;
    auto loadFlyingObstacle(sf::Vector2f const& position) -> void;
    auto generateRandomBushes() -> void;
    auto loadBush(sf::Vector2f const& position) -> void;
    auto generateZombie() -> void;
    auto loadZombie(sf::Vector2f const& position) -> void;
    auto generateFirstEnemy() -> void;
    auto loadFirstEnemy() -> void;
    auto generateRobot() -> void;
    auto loadRobot() -> void;


//    run game
    auto run() -> void;


public:
    Game();





};