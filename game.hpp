#pragma once

#include <SFML/Graphics.hpp>

#include "hero.hpp"
#include "zombie.hpp"
#include "firstEnemy.hpp"
#include "robot.hpp"
#include "mainMenu.hpp"

class Game{

    sf::RenderWindow window;
    MainMenu mainMenu;

    std::string const dataFile = "../data.txt";

//    Game management
    int highScore;
    bool gameStarted;
    bool jumpBlocked;
    bool qBlocked;
//    level tracker
    int currentLevel;


    //    map
    sf::Sprite bg;
    sf::Sprite ground;

//    Game entities
    Hero hero;
//    Place for zombie pointer ( nullptr when no zombie )
    std::unique_ptr<Zombie> zombiePointer;
//    Place for firstEnemy pointer ( nullptr when no firstEnemy)
    std::unique_ptr<FirstEnemy> firstEnemyPointer;
//    Place for robot pointer ( nullptr when no robot)
    std::unique_ptr<Robot> robotPointer;

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




};