#include "mainMenu.hpp"
#include "utilities.hpp"

MainMenu::MainMenu() : levelText(), isManualDisplayed() {

    container = sf::RectangleShape(sf::Vector2f(300,400));
    container.setFillColor(sf::Color(0,0,0,128));

    font = sf::Font();
    font.loadFromFile("../assets/font/RobotoCondensed-Italic-VariableFont_wght.ttf");

    headerText = sf::Text("2D Game", font, 50);
    headerText.setFillColor(sf::Color::White);
    headerText.setStyle(sf::Text::Bold);

    gameOverText = sf::Text("Game Over", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);

    deadMessageText = sf::Text("Dead message", font, 25);
    deadMessageText.setFillColor(sf::Color::Red);
    deadMessageText.setStyle(sf::Text::Bold);

    newGameText = sf::Text("New Game", font, 30);
    newGameText.setFillColor(sf::Color::White);
    newGameButton = sf::RectangleShape(sf::Vector2f(210,50));
    newGameButton.setFillColor(sf::Color::Black);

    resumeGameText = sf::Text("Resume Game", font, 30);
    resumeGameText.setFillColor(sf::Color::Black);
    resumeGameButton = sf::RectangleShape(sf::Vector2f(210,50));

    loadGameText = sf::Text("Load Game", font, 30);
    loadGameText.setFillColor(sf::Color::Black);
    loadGameButton = sf::RectangleShape(sf::Vector2f (210,50));
    loadGameButton.setFillColor(sf::Color::Cyan);

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

    messageText = sf::Text("", font, 30);
}

auto MainMenu::getNewGameButton() const -> sf::RectangleShape { return newGameButton; }

auto MainMenu::getResumeGameButton() const -> sf::RectangleShape { return resumeGameButton; }

auto MainMenu::getResumeEnabled() const -> bool{
    return resumeEnabled;
}
auto MainMenu::setResumeEnabled(bool const& value) -> void{
    resumeEnabled = value;
}

auto MainMenu::getLoadGameButton() const -> sf::RectangleShape { return loadGameButton; }


auto MainMenu::getManualButton() const -> sf::Sprite {
    return manualButtonSprite;
}

auto MainMenu::getIsManualDisplayed() const -> bool{
    return isManualDisplayed;
}
auto MainMenu::setIsManualDisplayed(bool const& value) -> void{
    isManualDisplayed = value;
}
auto MainMenu::setMessageText(std::string const& message) -> void {
    messageText = sf::Text(message, font, 30);
    messageText.setFillColor(sf::Color::Red);
}

auto MainMenu::getPauseGameButton() const-> sf::Sprite { return pauseButtonSprite; }

auto MainMenu::displayMainMenu(sf::RenderWindow &window) -> void {

    container.setPosition(windowCenter(window) - positionHelper(container));

    headerText.setPosition(container.getPosition() + sf::Vector2f(50,50));

    newGameButton.setPosition(headerText.getPosition().x, headerText.getPosition().y + 100);
    newGameText.setPosition(headerText.getPosition().x + 10, headerText.getPosition().y + 100);

    loadGameButton.setPosition(headerText.getPosition().x, newGameButton.getPosition().y + 70);
    loadGameText.setPosition(headerText.getPosition().x + 10, newGameButton.getPosition().y + 70);

    resumeGameButton.setPosition(headerText.getPosition().x, loadGameButton.getPosition().y + 70);
    resumeGameText.setPosition(headerText.getPosition().x + 10, loadGameButton.getPosition().y + 70);
    if(resumeEnabled){
        resumeGameText.setFillColor(sf::Color::Black);
        resumeGameButton.setFillColor(sf::Color::White);
    } else{
        resumeGameText.setFillColor(sf::Color::Red);
        resumeGameButton.setFillColor(sf::Color(65,65,65));
    }

    manualButtonSprite.setPosition(10,20);

    manualSprite.setPosition(windowCenter(window) - positionHelper(manualSprite));

    if(!isManualDisplayed){
        window.draw(container);
        window.draw(headerText);
        window.draw(newGameButton);
        window.draw(newGameText);
        window.draw(resumeGameButton);
        window.draw(resumeGameText);
        window.draw(loadGameButton);
        window.draw(loadGameText);
    } else{
        fmt::println("Should show manual");
        window.draw(manualSprite);
    }

    window.draw(manualButtonSprite);

}

auto MainMenu::displayPauseButton(sf::RenderWindow &window) -> void {
    pauseButtonSprite.setPosition(10,20);
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

auto MainMenu::displayGameOver(sf::RenderWindow &window, std::string const& deadMessage) -> void {
    gameOverText.setPosition(windowCenter(window) - positionHelper(gameOverText));
    deadMessageText = sf::Text(deadMessage, font, 25);
    deadMessageText.setFillColor(sf::Color::Red);
    deadMessageText.setPosition(sf::Vector2f(windowCenter(window).x,gameOverText.getPosition().y + 50) - sf::Vector2f(positionHelper(deadMessageText).x,-20));
    window.draw(gameOverText);
    window.draw(deadMessageText);
}

auto MainMenu::displayMessageText(sf::RenderWindow &window) -> void {
    if(messageText.getString() != ""){
        messageText.setPosition(windowCenter(window) - positionHelper(messageText) - sf::Vector2f(0,20));
        window.draw(messageText);
    }

}