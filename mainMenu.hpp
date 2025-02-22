#pragma once

#include <SFML/Graphics.hpp>

#include "hero.hpp"

class MainMenu{
    sf::RectangleShape container;
    sf::Font font;
    sf::Text headerText;
    sf::RectangleShape newGameButton;
    sf::Text newGameText;
    sf::RectangleShape resumeGameButton;
    sf::Text resumeGameText;
    sf::RectangleShape loadGameButton;
    sf::Text loadGameText;
    sf::Sprite pauseButtonSprite;
    sf::Texture pauseButtonTexture;
    sf::RectangleShape highScoreContainer;
    sf::Text highScoreText;
    sf::RectangleShape scoreContainer;
    sf::Text scoreText;
    sf::Text levelText;
    sf::Sprite manualButtonSprite;
    sf::Texture manualButtonTexture;
    sf::Sprite manualSprite;
    sf::Texture manualTexture;
    sf::Text gameOverText;
    sf::Text deadMessageText;
    sf::Text messageText;

    bool isManualDisplayed;
    bool resumeEnabled;

    static auto windowCenter(sf::Window const& window) -> sf::Vector2f;

public:
    MainMenu();
    auto getNewGameButton() const -> sf::RectangleShape;
    auto getResumeGameButton() const -> sf::RectangleShape;
    auto getResumeEnabled() const -> bool;
    auto setResumeEnabled(bool const& value) -> void;
    auto getLoadGameButton() const -> sf::RectangleShape;
    auto getManualButton() const -> sf::Sprite;
    auto getPauseGameButton() const -> sf::Sprite;
    auto getIsManualDisplayed() const -> bool;
    auto setIsManualDisplayed(bool const& value) -> void;
    auto setMessageText(std::string const& message) -> void;
    auto displayMainMenu(sf::RenderWindow& window) -> void;
    auto displayPauseButton(sf::RenderWindow& window) -> void;
    auto displayHighScore(sf::RenderWindow& window, int const& highScore) -> void;
    auto displayScore(sf::RenderWindow& window, int const& score) -> void;
    auto displayLevel(sf::RenderWindow& window, int const& currentLevel) -> void;
    auto displayGameOver(sf::RenderWindow& window, std::string const& deadMessage) -> void;
    auto displayMessageText(sf::RenderWindow& window) -> void;
};