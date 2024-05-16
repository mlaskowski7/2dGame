#include "mainMenu.hpp"

MainMenu::MainMenu() {

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

    pauseGameText = sf::Text("||", font, 20);
    pauseGameText.setStyle(sf::Text::Bold);
    pauseGameText.setFillColor(sf::Color::White);
    pauseGameButton = sf::RectangleShape(sf::Vector2f(30,30));
    pauseGameButton.setFillColor(sf::Color::Black);
}

auto MainMenu::getNewGameButton() -> sf::RectangleShape { return newGameButton; }

auto MainMenu::getResumeGameButton() -> sf::RectangleShape { return resumeGameButton; }

auto MainMenu::getPauseGameButton() -> sf::RectangleShape { return pauseGameButton; }

auto MainMenu::displayMainMenu(sf::RenderWindow &window) -> void {

    headerText.setPosition((window.getSize().x)/2 - 100, (window.getSize().y)/2 - 100);

    newGameButton.setPosition(headerText.getPosition().x, headerText.getPosition().y + 100);
    newGameText.setPosition(headerText.getPosition().x + 10, headerText.getPosition().y + 100);

    resumeGameButton.setPosition(headerText.getPosition().x, newGameButton.getPosition().y + 70);
    resumeGameText.setPosition(headerText.getPosition().x + 10, newGameButton.getPosition().y + 70);

    window.draw(headerText);
    window.draw(newGameButton);
    window.draw(newGameText);
    window.draw(resumeGameButton);
    window.draw(resumeGameText);

}

auto MainMenu::displayPauseButton(sf::RenderWindow &window) -> void {
    pauseGameButton.setPosition(0,0);
    pauseGameText.setPosition(0,0);
    window.draw(pauseGameButton);
    window.draw(pauseGameText);
}



