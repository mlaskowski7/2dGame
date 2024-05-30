#include <map>
#include <filesystem>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include <fmt/core.h>
#include <fmt/ranges.h>

//  Method that is used to populate image paths for animation frames for each character from filesystem
auto getFramesMap(std::string const& rootDir) -> std::map<std::string, std::vector<std::string>>;

//  Method used to get sf element's diagonal to correctly determine its position later
auto positionHelper(sf::RectangleShape const& element)-> sf::Vector2f ;
auto positionHelper(sf::Text const& element)-> sf::Vector2f ;
auto positionHelper(sf::Sprite const& element) -> sf::Vector2f;

auto vector2fToString(sf::Vector2f const& vector2f) -> std::string;
auto getLine(std::string const& filePath, int const& line) -> std::string;
auto setLine(std::string const& filePath, int const& line, std::string const& str) -> void;
auto splitString(std::string const& string, char const& delimeter) -> std::vector<std::string>;

// Collisions
auto collision(sf::Sprite const& lhs, sf::Sprite const& rhs) -> bool;
auto collision(sf::Sprite const& lhs, std::unique_ptr<sf::Sprite> const& rhs) -> bool;