
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Knife {

    sf::Sprite sprite;
    sf::Texture texture;

//    animation
    int ongoingPosition;
    float timer;

    sf::Vector2f position;
    float defaultPosition;

    auto changePosition() -> void;

public:
    Knife(sf::Vector2f newPosition);
    auto animation(float const& startTime) -> void;
    auto getSprite() const -> sf::Sprite;

};

