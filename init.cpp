#include <SFML/Graphics.hpp>

auto createWindow() -> void{
    auto window = sf::RenderWindow(
            sf::VideoMode({800,600}),
            "2D Game", sf::Style::Default,
            sf::ContextSettings(0,0, 8)
    );

    while(window.isOpen()){
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }
        window.display();
    }
}
