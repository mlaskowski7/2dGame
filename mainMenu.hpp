#include <SFML/Graphics.hpp>

class MainMenu{
    sf::Font font;
    sf::Text headerText;
    sf::RectangleShape newGameButton;
    sf::Text newGameText;
    sf::RectangleShape resumeGameButton;
    sf::Text resumeGameText;
    sf::RectangleShape pauseGameButton;
    sf::Text pauseGameText;

public:
    MainMenu();
    auto getNewGameButton() -> sf::RectangleShape;
    auto getResumeGameButton() -> sf::RectangleShape;
    auto getPauseGameButton() -> sf::RectangleShape;
    auto displayMainMenu(sf::RenderWindow& window) -> void;
    auto displayPauseButton(sf::RenderWindow& window) -> void;
};