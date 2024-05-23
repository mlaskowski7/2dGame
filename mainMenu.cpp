#include "mainMenu.hpp"
#include "utilities.hpp"

MainMenu::MainMenu() : levelText(), isManualDisplayed() {

    container = sf::RectangleShape(sf::Vector2f(300,300));
    container.setFillColor(sf::Color(0,0,0,128));

    font = sf::Font();
    font.loadFromFile("../assets/font/RobotoCondensed-Italic-VariableFont_wght.ttf");

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
    pauseButtonSprite.setScale(0.5,0.5);

    manualButtonTexture = sf::Texture();
    manualButtonTexture.loadFromFile("../assets/buttons/manual.png");
    manualButtonSprite.setTexture(manualButtonTexture);
    manualButtonSprite.setScale(0.5,0.5);

    manualTexture = sf::Texture();
    manualTexture.loadFromFile("../assets/controlsInstruction/manual.png");
    manualSprite.setTexture(manualTexture);
}

auto MainMenu::getNewGameButton() const -> sf::RectangleShape { return newGameButton; }

auto MainMenu::getResumeGameButton() const -> sf::RectangleShape { return resumeGameButton; }

auto MainMenu::getManualButton() const -> sf::Sprite {
    return manualButtonSprite;
}

auto MainMenu::getIsManualDisplayed() const -> bool{
    return isManualDisplayed;
}
auto MainMenu::setIsManualDisplayed(bool const& value) -> void{
    isManualDisplayed = value;
}

auto MainMenu::getGameOver() const -> bool {
    return isGameOver;
}

auto MainMenu::setGameOver(bool const& value) -> void {
    isGameOver = value;
}

auto MainMenu::getPauseGameButton() const-> sf::Sprite { return pauseButtonSprite; }

auto MainMenu::displayMainMenu(sf::RenderWindow &window) -> void {

    container.setPosition(windowCenter(window) - positionHelper(container));

    headerText.setPosition(container.getPosition() + sf::Vector2f(50,50));

    newGameButton.setPosition(headerText.getPosition().x, headerText.getPosition().y + 100);
    newGameText.setPosition(headerText.getPosition().x + 10, headerText.getPosition().y + 100);

    resumeGameButton.setPosition(headerText.getPosition().x, newGameButton.getPosition().y + 70);
    resumeGameText.setPosition(headerText.getPosition().x + 10, newGameButton.getPosition().y + 70);

    manualButtonSprite.setPosition(10,10);

    manualSprite.setPosition(windowCenter(window) - positionHelper(manualSprite));

    if(!isManualDisplayed){
        window.draw(container);
        window.draw(headerText);
        window.draw(newGameButton);
        window.draw(newGameText);
        window.draw(resumeGameButton);
        window.draw(resumeGameText);
    } else{
        fmt::println("Should show manual");
        window.draw(manualSprite);
    }

    window.draw(manualButtonSprite);

}

auto MainMenu::displayPauseButton(sf::RenderWindow &window) -> void {
    pauseButtonSprite.setPosition(10,10);
    window.draw(pauseButtonSprite);

}

auto MainMenu::windowCenter(const sf::Window &window) -> sf::Vector2f {
    return sf::Vector2f ((window.getSize().x)/2,(window.getSize().y)/2);
}

auto MainMenu::displayHighScore(sf::RenderWindow& window, int const& highScore) -> void{
    highScoreContainer = sf::RectangleShape(sf::Vector2f(200,50));
    highScoreContainer.setFillColor(sf::Color(0,0,0,128));
    highScoreText = sf::Text("High Score:" + std::to_string(highScore), font, 20);
    highScoreText.setFillColor(sf::Color(255,255,255));
    highScoreContainer.setPosition(sf::Vector2f(window.getSize().x, 150) - positionHelper(highScoreContainer) - positionHelper(highScoreContainer));
    highScoreText.setPosition(sf::Vector2f(window.getSize().x, 150) - positionHelper(highScoreContainer) - positionHelper(highScoreContainer) + sf::Vector2f(10,10));
    window.draw(highScoreContainer);
    window.draw(highScoreText);
}


auto MainMenu::displayScore(sf::RenderWindow& window, int const& score) -> void{
    scoreContainer = sf::RectangleShape(sf::Vector2f(200,50));
    scoreContainer.setFillColor(sf::Color(255,255,255,128));
    scoreText = sf::Text("Score:" + std::to_string(score), font, 20);
    scoreText.setFillColor(sf::Color::Black);
    scoreContainer.setPosition(sf::Vector2f(window.getSize().x, 100) - positionHelper(scoreContainer) - positionHelper(scoreContainer));
    scoreText.setPosition(sf::Vector2f(window.getSize().x, 100) - positionHelper(scoreContainer) - positionHelper(scoreContainer) + sf::Vector2f(10,10));
    window.draw(scoreContainer);
    window.draw(scoreText);
}

auto MainMenu::displayLevel(sf::RenderWindow& window, int const& currentLevel) -> void{
    auto text = std::string();
    if(currentLevel < 5){
        text = "Level Easy";
    } else if(currentLevel < 10){
        text = "Level Medium";
    } else if(currentLevel <= 20){
        text = "Level Hard";
    } else{
        text = "Level Hardcore";
    }
    levelText = sf::Text(text, font, 45);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(sf::Vector2f(window.getSize().x/2, 50) - positionHelper(levelText));
    window.draw(levelText);
}

