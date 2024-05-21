#include <SFML/Graphics.hpp>

class MainMenu{
    sf::RectangleShape container;
    sf::Font font;
    sf::Text headerText;
    sf::RectangleShape newGameButton;
    sf::Text newGameText;
    sf::RectangleShape resumeGameButton;
    sf::Text resumeGameText;
    sf::Sprite pauseButtonSprite;
    sf::Texture pauseButtonTexture;
    sf::RectangleShape highScoreContainer;
    sf::Text highScoreText;
    sf::RectangleShape scoreContainer;
    sf::Text scoreText;
    sf::Text levelText;


    static auto windowCenter(sf::Window const& window) -> sf::Vector2f;

public:
    MainMenu();
    auto getNewGameButton() -> sf::RectangleShape;
    auto getResumeGameButton() -> sf::RectangleShape;
    auto getPauseGameButton() -> sf::Sprite;
    auto displayMainMenu(sf::RenderWindow& window) -> void;
    auto displayPauseButton(sf::RenderWindow& window) -> void;
    auto displayHighScore(sf::RenderWindow& window, int const& highScore) -> void;
    auto displayScore(sf::RenderWindow& window, int const& score) -> void;
    auto displayLevel(sf::RenderWindow& window, int const& currentLevel) -> void;
};