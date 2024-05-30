#include <fmt/core.h>
#include <fmt/ranges.h>

#include <SFML/Graphics.hpp>

#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "hero.hpp"
#include "mainMenu.hpp"
#include "zombie.hpp"
#include "utilities.hpp"
#include "dataFileEnum.hpp"
#include "firstEnemy.hpp"


// main menu on click functions declaration
auto newGameOnclick(Hero& hero, sf::Sprite const& ground, std::vector<std::unique_ptr<sf::Sprite>>& groundObstacles, std::vector<std::unique_ptr<sf::Sprite>>& flyingObstacles, sf::Texture const& groundObstacleTexture, sf::Texture const& flyingObstacleTexture, bool& gameStarted, std::unique_ptr<Zombie>& zombiePointer, int& currentLevel) -> void;

// data file integration methods
auto saveGame(Hero const& hero, int const& currentLevel) -> void;
auto checkHighScore(std::string const& dataFilePath,int const& score, int& highScore) -> void;

// hero controls on click functions declaration
auto rightArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto rightArrowAfterJumpClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto leftArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto leftArrowAfterJumpClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto upArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock, sf::Sprite ground) -> void;
auto downArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock) -> void;
auto qOnClick(Hero& hero, sf::Sprite const& ground,sf::Clock& lastMovementClock, std::unique_ptr<FirstEnemy>& firstEnemy) -> void;
auto wOnClick(Hero& hero, sf::Sprite const& ground, sf::Clock& lastMovementClock) -> void;

// game state management functions
auto nextLevel(Hero& hero, sf::Sprite const& ground, std::vector<std::unique_ptr<sf::Sprite>>& groundObstacles, std::vector<std::unique_ptr<sf::Sprite>>& flyingObstacles, sf::Texture const& groundObstacleTexture, sf::Texture const& flyingObstacleTexture, sf::Clock& levelClock, std::unique_ptr<Zombie>& zombiePointer, int& currentLevel, std::vector<std::unique_ptr<sf::Sprite>>& bushes, sf::Texture const& bushTexture) -> void;

// functions used to randomly generate obstacles and enemies
auto generateRandomGroundObstacles(std::vector<std::unique_ptr<sf::Sprite>>& groundObstacles,sf::Sprite const& ground, sf::Texture const& groundObstacleTexture) -> void;
auto generateRandomFlyingObstacles(std::vector<std::unique_ptr<sf::Sprite>>& flyingObstacles,std::vector<std::unique_ptr<sf::Sprite>>& groundObstacles,sf::Sprite const& ground, sf::Texture const& flyingObstacleTexture) -> void;
auto generateRandomBushes(std::vector<std::unique_ptr<sf::Sprite>>& bushes, sf::Texture const& bushTexture, std::vector<std::unique_ptr<sf::Sprite>> const& groundObstacles, std::vector<std::unique_ptr<sf::Sprite>> const& flyingObstacles,sf::Sprite const& ground) -> void;
auto generateZombie(std::unique_ptr<Zombie>& zombiePointer,sf::Sprite const& ground) -> void;
auto generateFirstEnemy(sf::Sprite const& ground, std::unique_ptr<FirstEnemy>& firstEnemyPointer) -> void;




auto main() -> int {

//    Window Declaration and setting frame limit to 60 to avoid skipping frames
    auto window = sf::RenderWindow(
            sf::VideoMode({1700,1024}),
            "2D Game", sf::Style::Titlebar | sf::Style::Close,
            sf::ContextSettings(0,0, 8)
            );
    window.setFramerateLimit(60);

//    loading data file
    auto dataFile = std::string("../data.txt");

    auto highScore = std::stoi(getLine(dataFile, dataLines::HIGH_SCORE));
    fmt::println("Loaded high score - {}", highScore);

//    seeding random number generator
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

//    Place for zombie pointer ( nullptr when no zombie )
    std::unique_ptr<Zombie> zombiePointer = nullptr;

//    Place for firstEnemy pointer ( nullptr when no firstEnemy)
    std::unique_ptr<FirstEnemy> firstEnemyPointer = nullptr;

//    Main menu object init
    auto mainMenu = MainMenu();

//    Boolean for blocking jump during gravity falling (to prevent flying effect)
    bool jumpBlocked = false;

//    sfml clock for animations
    auto clock = sf::Clock();
//    clock used to track time in current level
    auto levelClock = sf::Clock();
//    clock used to track hero's last movement so that the hero goes back to idle when movement is finished
    auto lastMovementClock = sf::Clock();
//    message clock that is used to determine whether the message should be displayed
    auto messageClock = sf::Clock();
    auto isMessageDisplayed = bool();

//    time used for conducting animations
    auto startTime = float();

//    level tracker
    auto currentLevel = 1;

    auto groundObstacles = std::vector<std::unique_ptr<sf::Sprite>>();
    auto groundObstacleTexture = sf::Texture();
    groundObstacleTexture.loadFromFile("../assets/obstacles/groundObstacle.png");


    auto flyingObstacles = std::vector<std::unique_ptr<sf::Sprite>>();
    auto flyingObstacleTexture = sf::Texture();
    flyingObstacleTexture.loadFromFile("../assets/obstacles/flyingObstacle.png");

    auto bushes = std::vector<std::unique_ptr<sf::Sprite>>();
    auto bushTexture = sf::Texture();
    bushTexture.loadFromFile("../assets/obstacles/bush.png");

//    dead message displayed after game over
    auto deadMessage = std::string();


//    Game Loop
    while(window.isOpen()){
//        save time till last clock restart to variable for animations
        startTime = clock.restart().asSeconds();
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::MouseButtonPressed) {
//                Main menu controls
                if(event.mouseButton.button == sf::Mouse::Left){
                    auto mousePosition = sf::Mouse::getPosition(window);
                    if(mainMenu.getNewGameButton().getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)}) && !gameStarted && !mainMenu.getIsManualDisplayed()){
                        newGameOnclick(hero,ground,groundObstacles,flyingObstacles,groundObstacleTexture,flyingObstacleTexture,gameStarted,zombiePointer, currentLevel);
                    } else if (mainMenu.getResumeGameButton().getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)}) && !gameStarted && mainMenu.getResumeEnabled() && !mainMenu.getIsManualDisplayed()){
                        gameStarted = true;
                    } else if(mainMenu.getPauseGameButton().getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)})){
                        gameStarted = false;
                        mainMenu.setResumeEnabled(true);
                    } else if(mainMenu.getManualButton().getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)})){
                        fmt::println("Manual button clicked");
                        if(mainMenu.getIsManualDisplayed()){
                            fmt::println("Manual button is true setting to false");
                            mainMenu.setIsManualDisplayed(false);
                        } else{
                            fmt::println("Should set is manual displayed to true");
                            mainMenu.setIsManualDisplayed(true);
                        }
                    } else if(mainMenu.getLoadGameButton().getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)})){
                        auto savedPosition = splitString(getLine(dataFile, dataLines::HERO_POSITION_SAVE), ',') ;
                        fmt::println("{},{}",savedPosition[0], savedPosition[1]);
                        auto position = sf::Vector2f(std::stof(savedPosition[0]), std::stof(savedPosition[1]));
                        hero.updatePosition(position);
                        gameStarted = true;
                        currentLevel = std::stoi(getLine(dataFile, dataLines::LEVEL_SAVE));
                        hero.setScore(std::stoi(getLine(dataFile, dataLines::SCORE_SAVE)));
                    }
                }
            }else if (event.type == sf::Event::KeyPressed && gameStarted && !hero.getIsDead()) {
//                Save game
                if(event.key.code == sf::Keyboard::S){
                    saveGame(hero, currentLevel);
                    mainMenu.setMessageText("Game Saved");
                    messageClock.restart();
                    isMessageDisplayed = true;
                }
//                Move Left
                if (event.key.code == sf::Keyboard::Left) {
                    if(hero.getSprite().getPosition().y < ground.getPosition().y - 2*groundTexture.getSize().y){
                        leftArrowAfterJumpClick(hero,lastMovementClock,ground);
                    } else{
                        leftArrowOnClick(hero, lastMovementClock, ground);
                    }

                }
//                Move Right
                if (event.key.code == sf::Keyboard::Right) {
                    if(hero.getSprite().getPosition().y < ground.getPosition().y - 2*groundTexture.getSize().y){
                        rightArrowAfterJumpClick(hero, lastMovementClock, ground);
                    } else{
                        rightArrowOnClick(hero, lastMovementClock, ground);
                    }
                }
//                Jump
                if (event.key.code == sf::Keyboard::Up) upArrowOnClick(hero, jumpBlocked, lastMovementClock, ground);
//                Slide
                if (event.key.code == sf::Keyboard::Down) downArrowOnClick(hero,jumpBlocked,lastMovementClock);

//                Hero attacks controls
                if(event.key.code == sf::Keyboard::Q) qOnClick(hero, ground, lastMovementClock, firstEnemyPointer);

                if(event.key.code == sf::Keyboard::W) wOnClick(hero, ground, lastMovementClock);

                if(event.key.code == sf::Keyboard::Escape){
                    gameStarted = false;
                    mainMenu.setResumeEnabled(true);
                }


            } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M && !gameStarted){
                if(mainMenu.getIsManualDisplayed()){
                    fmt::println("Manual button is true setting to false");
                    mainMenu.setIsManualDisplayed(false);
                } else{
                    fmt::println("Should set is manual displayed to true");
                    mainMenu.setIsManualDisplayed(true);
                }

            }
        }


//        disabling multiple jumps and enabling gravity effect, so that hero cant fly
        if(hero.getSprite().getPosition().y < ground.getPosition().y - 2*groundTexture.getSize().y){
            jumpBlocked = true;
            hero.gravityEffect();
        }else if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*groundTexture.getSize().y){
            hero.isSliding = true;
        } else{
            jumpBlocked = false;
            hero.isSliding = false;
        }

        auto isUnslowingConducted = hero.unslow();
        if(isUnslowingConducted) mainMenu.setMessageText("");

//        Next level handling when hero is touching and of the window
        if(hero.getSprite().getPosition().x >= window.getSize().x){
            nextLevel(hero,ground,groundObstacles,flyingObstacles,groundObstacleTexture,flyingObstacleTexture,levelClock,zombiePointer, currentLevel, bushes, bushTexture);
            if(currentLevel >= 5){
                generateFirstEnemy(ground, firstEnemyPointer);
                auto wasUpdated = hero.updateVelocity(sf::Vector2f(12,0));
                if(zombiePointer != nullptr){
                    zombiePointer->updateVelocity(sf::Vector2f (4,0));
                }
                if(wasUpdated){
                    mainMenu.setMessageText("Speed has permanently increased because of new level");
                }
                messageClock.restart();
                isMessageDisplayed = true;

            }
        }

        if(isMessageDisplayed && messageClock.getElapsedTime().asSeconds() > 3){
            mainMenu.setMessageText("");
            isMessageDisplayed = false;

        }

//        conducting hero animation
        hero.animation(startTime);

//        move bullet if its not nullptr
        hero.moveBullet();

//        Back to idle if standing ( prevents running when not moving )
        if(lastMovementClock.getElapsedTime().asSeconds() > 0.3 && !hero.getIsDead()){
            hero.backToIdle(ground);
        }

        if(firstEnemyPointer != nullptr){
//              Kill hero on collision with first enemy
            if(hero.getIsBulletInitialized() && collision(firstEnemyPointer->getSprite(), hero.getBulletSprite())){
                auto enemyHealth = firstEnemyPointer->reduceHealthPoint();
                mainMenu.setMessageText("Enemy health points reduced to " + std::to_string(enemyHealth));
                messageClock.restart();
                hero.deleteBullet();
                if(firstEnemyPointer->getHealthPoints() == 0){
                    firstEnemyPointer->kill();
                }

            }
            if(collision(hero.getSprite(), firstEnemyPointer->getSprite()) && !hero.getIsDead() && !firstEnemyPointer->getIsDead()){
                fmt::println("Detected collision between firstEnemy and hero");
                firstEnemyPointer->changeAnimation("JumpAttack");
                if(!firstEnemyPointer->killing){
                    firstEnemyPointer->killingClock.restart();
                    firstEnemyPointer->killing = true;
                    fmt::println("first enemy killing clock restarted");
                }
                fmt::println("first enemy killing clock {}", firstEnemyPointer->killingClock.getElapsedTime().asMilliseconds());
                if(firstEnemyPointer->killing && firstEnemyPointer->killingClock.getElapsedTime().asSeconds() >= 0.7){
                    hero.kill(ground);
                    deadMessage = "Killed by enemy ninja";
                }

            }

            if(firstEnemyPointer->getIsDead() && firstEnemyPointer->getDeadTimeClock().getElapsedTime().asSeconds() > 0.5){
                firstEnemyPointer = nullptr;
            }
        }

//        enabling zombie movement and killing hero func after one second of a level
        if(levelClock.getElapsedTime().asSeconds() > 1 && zombiePointer != nullptr && !hero.getIsDead() && gameStarted){
//            collision system between zombie and ground obstacle or hero
            zombiePointer->move();
            for(auto i = groundObstacles.begin(); i != groundObstacles.end();){
                auto& current = *i;
                if(collision(zombiePointer->getSprite(), current)){
                    zombiePointer->changeAnimation("Attack");
                    i = groundObstacles.erase(i);
                    zombiePointer->restartZombieClock();
                } else{
                    i++;
                }
            }
            if(collision(zombiePointer->getSprite(), hero.getSprite())){
                zombiePointer->changeAnimation("Attack");
                hero.kill(ground);
                deadMessage = "Killed by zombie";
            }
        }

        window.clear(sf::Color::Black);

//        always draw bg and ground
        window.draw(bg);
        window.draw(ground);

        mainMenu.displayHighScore(window,highScore);
        mainMenu.displayScore(window, hero.getScore());
        checkHighScore("../data.txt",hero.getScore(),highScore);
        if(!gameStarted && !hero.getIsDead()){
            mainMenu.displayMainMenu(window);
        } else if(!hero.getIsDead()){
            mainMenu.displayPauseButton(window);
            mainMenu.displayLevel(window, currentLevel);
            mainMenu.displayMessageText(window);
            window.draw(hero.getSprite());
            hero.drawBullet(window);

//            drawing zombie if not nullptr
            if(zombiePointer != nullptr){
                zombiePointer->animation(startTime);
                window.draw(zombiePointer->getSprite());
            }

            if(firstEnemyPointer != nullptr){
                firstEnemyPointer->animation(startTime);
                window.draw(firstEnemyPointer->getSprite());
            }

//            loop checking whether hero has hit any ground obstacle and drawing ground obstacles
            for(auto const& groundObstacle : groundObstacles){
                if(collision(hero.getSprite(),groundObstacle) && !hero.getIsDead()){
                    hero.kill(ground);
                    deadMessage = "Hit ground obstacle";
                }
                window.draw(*groundObstacle);
            }

//            loop checking whether hero has hit any flying obstacle and drawing glying obstacles
            for(auto const& flyingObstacle : flyingObstacles){
                if(collision(hero.getSprite(), flyingObstacle) && !hero.getIsDead()){
                    hero.kill(ground);
                    deadMessage = "Hit flying obstacle";
                }
                window.draw(*flyingObstacle);
            }

            for(auto i = bushes.begin(); i != bushes.end();){
                auto& current = *i;
                if(current->getPosition().x - hero.getSprite().getPosition().x <= 170 && (hero.getOngoingAnimation() == "Attack" || hero.getOngoingAnimation() == "Jump_Attack")){
                    i = bushes.erase(i);
                } else if(collision(hero.getSprite(),current)){
                    hero.slow();
                    mainMenu.setMessageText("slowed!");
                    i = bushes.erase(i);
                } else{
                    window.draw(*current);
                    i++;
                }
            }
        }

        if(hero.getDeadTimeClock().getElapsedTime().asSeconds() < 2 && hero.getIsDead()){
            mainMenu.displayGameOver(window, deadMessage);
            mainMenu.setMessageText("");
        } else if(hero.getDeadTimeClock().getElapsedTime().asSeconds() > 2 && hero.getIsDead()){
            hero.setIsDead(false);
            mainMenu.setResumeEnabled(false);
            hero.updateVelocity(sf::Vector2f(10,0));
        }


//        finish game when hero has been killed ( 0.7 seconds later so that dead animation is fully conducted )
        if(hero.getDeadTimeClock().getElapsedTime().asSeconds() > 0.7 && hero.getIsDead() && gameStarted){
            gameStarted = false;
            currentLevel = 1;
            firstEnemyPointer = nullptr;
            zombiePointer = nullptr;
            groundObstacles.clear();
            flyingObstacles.clear();
        }

        window.display();


    }
}

auto newGameOnclick(Hero& hero, sf::Sprite const& ground, std::vector<std::unique_ptr<sf::Sprite>>& groundObstacles, std::vector<std::unique_ptr<sf::Sprite>>& flyingObstacles, sf::Texture const& groundObstacleTexture, sf::Texture const& flyingObstacleTexture, bool& gameStarted, std::unique_ptr<Zombie>& zombiePointer, int& currentLevel) -> void{
    zombiePointer = nullptr;
    generateRandomGroundObstacles(groundObstacles, ground,groundObstacleTexture);
    generateRandomFlyingObstacles(flyingObstacles, groundObstacles,ground,flyingObstacleTexture);
    gameStarted = true;
    currentLevel = 1;

    hero.newGame(ground);
}

auto saveGame(Hero const& hero, int const& currentLevel) -> void{
    fmt::println("S clicked (Saved Game)");
    setLine("../data.txt", dataLines::HERO_POSITION_SAVE, vector2fToString(hero.getSprite().getPosition()));
    setLine("../data.txt",dataLines::SCORE_SAVE, std::to_string(hero.getScore()));
    setLine("../data.txt", dataLines::LEVEL_SAVE, std::to_string(currentLevel));
}

auto checkHighScore(std::string const& dataFilePath,int const& score, int& highScore) -> void{
    if(score >= highScore){
        setLine(dataFilePath,dataLines::HIGH_SCORE, std::to_string(score));
        highScore = score;
    }
}

auto nextLevel(Hero& hero, sf::Sprite const& ground, std::vector<std::unique_ptr<sf::Sprite>>& groundObstacles, std::vector<std::unique_ptr<sf::Sprite>>& flyingObstacles, sf::Texture const& groundObstacleTexture, sf::Texture const& flyingObstacleTexture, sf::Clock& levelClock, std::unique_ptr<Zombie>& zombiePointer, int& currentLevel, std::vector<std::unique_ptr<sf::Sprite>>& bushes, sf::Texture const& bushTexture) -> void{
    hero.setStartingPosition(ground);
    generateRandomGroundObstacles(groundObstacles, ground,groundObstacleTexture);
    generateRandomFlyingObstacles(flyingObstacles, groundObstacles, ground, flyingObstacleTexture);
    generateRandomBushes(bushes, bushTexture, groundObstacles, flyingObstacles,ground);
//            generate zombie
    generateZombie(zombiePointer, ground);
    currentLevel++;
    levelClock.restart();
}

auto rightArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    hero.changeAnimation("Run");
    lastMovementClock.restart();
    hero.moveRight();
}

auto rightArrowAfterJumpClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    hero.changeAnimation("Glide");
    lastMovementClock.restart();
    hero.moveRight();
}

auto leftArrowOnClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    hero.changeAnimation("RunBackwards");
    lastMovementClock.restart();
    hero.moveLeft();
}

auto leftArrowAfterJumpClick(Hero& hero, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    hero.changeAnimation("GlideBackwards");
    lastMovementClock.restart();
    hero.moveLeft();
}

auto upArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock, sf::Sprite ground) -> void{
    if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    if(!jumpBlocked){
        hero.changeAnimation("Jump");
        lastMovementClock.restart();
        for(auto i = 0; i < 3; i++){
            hero.jump();
        }

    }
}

auto downArrowOnClick(Hero& hero, bool const& jumpBlocked, sf::Clock& lastMovementClock) -> void{
    if(!jumpBlocked){
        hero.changeAnimation("Slide");
        hero.slide();
    }
    lastMovementClock.restart();

}

auto qOnClick(Hero& hero, sf::Sprite const& ground, sf::Clock& lastMovementClock, std::unique_ptr<FirstEnemy>& firstEnemy) -> void{
    if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }
    if(hero.getSprite().getPosition().y < ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.changeAnimation("Jump_Attack");
    } else{
        hero.changeAnimation("Attack");
    }
    if(firstEnemy != nullptr && firstEnemy->getSprite().getPosition().x - hero.getSprite().getPosition().x <= 170){
        firstEnemy->reduceHealthPoint();
        if(firstEnemy->getHealthPoints() == 0){
            firstEnemy->kill();
        }
    }
    lastMovementClock.restart();
}

auto wOnClick(Hero& hero, sf::Sprite const& ground, sf::Clock& lastMovementClock) -> void{
    if(hero.getSprite().getPosition().y > ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.backFromSliding(ground);
    }

    if(hero.getSprite().getPosition().y < ground.getPosition().y - 2*ground.getTexture()->getSize().y){
        hero.changeAnimation("Jump_Throw");
    } else{
        hero.changeAnimation("Throw");
    }
    hero.initBullet();
    lastMovementClock.restart();
}

auto generateRandomGroundObstacles(std::vector<std::unique_ptr<sf::Sprite>>& groundObstacles,sf::Sprite const& ground, sf::Texture const& groundObstacleTexture) -> void{
    groundObstacles.clear();

    auto numberOfObstacles = std::rand() % 3;
    fmt::println("Generating {} ground obstacles", numberOfObstacles);
    for(auto i = 0; i < numberOfObstacles; i++){
        auto obstacle = std::make_unique<sf::Sprite>();
        auto positionX = std::rand() % 1000 + 300;
        auto wrongPosition = bool();
        do {
            wrongPosition = false;
            for(auto const& groundObstacle : groundObstacles){
                if (std::abs(groundObstacle->getPosition().x - positionX) <= 200) {
                    wrongPosition = true;
                    positionX = std::rand() % 1000 + 300;
                    break;
                }
            }
        } while (wrongPosition);
        auto position = sf::Vector2f(positionX, ground.getPosition().y - 1.1*ground.getTexture()->getSize().y);
        obstacle->setPosition(position);
        obstacle->setTexture(groundObstacleTexture);
        obstacle->setScale(0.3,0.3);
        groundObstacles.push_back(std::move(obstacle));
    }
}

auto generateRandomFlyingObstacles(std::vector<std::unique_ptr<sf::Sprite>>& flyingObstacles, std::vector<std::unique_ptr<sf::Sprite>>& groundObstacles, sf::Sprite const& ground, sf::Texture const& flyingObstacleTexture) -> void {
    flyingObstacles.clear();

    auto numberOfObstacles = std::rand() % 3;
    fmt::println("Generating {} flying obstacles", numberOfObstacles);

    for(auto i = 0; i < numberOfObstacles; i++){
        auto obstacle = std::make_unique<sf::Sprite>();
        auto positionX = std::rand() % 1000 + 300;
        auto wrongPosition = bool();
        do {
            wrongPosition = false;
            for(auto const& groundObstacle : groundObstacles){
                if (std::abs(groundObstacle->getPosition().x - positionX) <= 200) {
                    wrongPosition = true;
                    positionX = std::rand() % 1000 + 300;
                    break;
                }
            }
        } while (wrongPosition);

        auto position = sf::Vector2f(positionX, ground.getPosition().y - 3 * ground.getTexture()->getSize().y);
        obstacle->setPosition(position);
        obstacle->setTexture(flyingObstacleTexture);
        obstacle->setScale(0.2, 0.2);
        flyingObstacles.push_back(std::move(obstacle));
    }
}

auto generateRandomBushes(std::vector<std::unique_ptr<sf::Sprite>>& bushes, sf::Texture const& bushTexture, std::vector<std::unique_ptr<sf::Sprite>> const& groundObstacles, std::vector<std::unique_ptr<sf::Sprite>> const& flyingObstacles, sf::Sprite const& ground) -> void{
    bushes.clear();

    auto numberOfObstacles = std::rand() % 3;
    fmt::println("Generating {} bushes", numberOfObstacles);
    for(auto i = 0; i < numberOfObstacles; i++){
        auto obstacle = std::make_unique<sf::Sprite>();
        auto positionX = std::rand() % 1100 + 300;
        auto wrongPositionGround = bool();
        auto wrongPositionAir = bool();
        do {
            wrongPositionGround = false;
            wrongPositionAir = false;
            for(auto const& groundObstacle : groundObstacles){
                if (std::abs(groundObstacle->getPosition().x - positionX) <= 200) {
                    wrongPositionGround = true;
                    positionX = std::rand() % 1100 + 300;
                    break;
                }
            }
            for(auto const& flyingObstacle : flyingObstacles){
                if (std::abs(flyingObstacle->getPosition().x - positionX) <= 200) {
                    wrongPositionAir = true;
                    positionX = std::rand() % 1100 + 300;
                    break;
                }
            }
        } while (wrongPositionGround || wrongPositionAir);

        auto position = sf::Vector2f(positionX, ground.getPosition().y - 1.4*ground.getTexture()->getSize().y);
        obstacle->setPosition(position);
        obstacle->setTexture(bushTexture);
        obstacle->setScale(2,2);
        bushes.push_back(std::move(obstacle));
    }
}

auto generateZombie(std::unique_ptr<Zombie>& zombiePointer, sf::Sprite const& ground) -> void{
    zombiePointer = nullptr;

    if(std::rand() %  2 == 0){
        auto zombie = std::make_unique<Zombie>(std::rand() % 2 == 0 ? "male" : "female");
        zombie->setStartingPosition(ground);
        zombiePointer = std::move(zombie);
    }
}

auto generateFirstEnemy(sf::Sprite const& ground, std::unique_ptr<FirstEnemy>& firstEnemyPointer) -> void{
    if(std::rand() % 3 == 0){
        firstEnemyPointer = std::move(std::make_unique<FirstEnemy>());
        firstEnemyPointer->setStartingPosition(ground);
        fmt::println("Generated firstEnemy");
    }
}