#include "bullet.hpp"
#include <SFML/Graphics.hpp>

class RobotBullet : public Bullet{

public:
    RobotBullet(sf::Vector2f const& robotPosition);
    auto move() -> void override;
};