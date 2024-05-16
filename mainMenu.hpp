#include <SFML/Graphics.hpp>

class MainMenu{
    sf::Font font;
    sf::Text headerText;
    sf::RectangleShape newGameButton;
    sf::Text newGameText;
    sf::RectangleShape resumeGameButton;
    sf::Text resumeGameText;

public:
    MainMenu();
};