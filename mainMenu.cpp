#include "mainMenu.hpp"
#include "utilities.hpp"

MainMenu::MainMenu() {

    container = sf::RectangleShape(sf::Vector2f(300,300));
    container.setFillColor(sf::Color(0,0,0,128));

    font = sf::Font();
    font.loadFromFile("../assets/font/RobotoMono-Italic-VariableFont_wght.ttf");

    headerText = sf::Text("2D Game", font, 50);
    headerText.setFillColor(sf::Color::White);
    headerText.setStyle(sf::Text::Bold);

    newGameText = sf::Text("New Game", font, 30);
    newGameText.setFillColor(sf::Color::White);
    newGameButton = sf::RectangleShape(sf::Vector2f(210,50));
    newGameButton.setFillColor(sf::Color::Black);

    resumeGameText = sf::Text("Resume Game", font, 30);
    resumeGameText.setFillColor(sf::Color::Black);
    resumeGameButton = sf::RectangleShape(sf::Vector2f(210,50));

    pauseButtonTexture = sf::Texture();
    pauseButtonTexture.loadFromFile("../assets/buttons/pauseButton.png");
    pauseButtonSprite.setTexture(pauseButtonTexture);
    pauseButtonSprite.setScale(0.1,0.1);
}

auto MainMenu::getNewGameButton() -> sf::RectangleShape { return newGameButton; }

auto MainMenu::getResumeGameButton() -> sf::RectangleShape { return resumeGameButton; }

auto MainMenu::getPauseGameButton() -> sf::Sprite { return pauseButtonSprite; }

auto MainMenu::displayMainMenu(sf::RenderWindow &window) -> void {

    container.setPosition(windowCenter(window) - positionHelper(container));

    headerText.setPosition(container.getPosition() + sf::Vector2f(50,50));

    newGameButton.setPosition(headerText.getPosition().x, headerText.getPosition().y + 100);
    newGameText.setPosition(headerText.getPosition().x + 10, headerText.getPosition().y + 100);

    resumeGameButton.setPosition(headerText.getPosition().x, newGameButton.getPosition().y + 70);
    resumeGameText.setPosition(headerText.getPosition().x + 10, newGameButton.getPosition().y + 70);

    window.draw(container);
    window.draw(headerText);
    window.draw(newGameButton);
    window.draw(newGameText);
    window.draw(resumeGameButton);
    window.draw(resumeGameText);

}

auto MainMenu::displayPauseButton(sf::RenderWindow &window) -> void {
    pauseButtonSprite.setPosition(0,0);
    window.draw(pauseButtonSprite);

}

auto MainMenu::windowCenter(const sf::Window &window) -> sf::Vector2f {
    return sf::Vector2f ((window.getSize().x)/2,(window.getSize().y)/2);
}

