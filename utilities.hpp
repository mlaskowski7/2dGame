#include <map>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include <fmt/core.h>
#include <fmt/ranges.h>

//  Method that is used to populate image paths for animation frames for each character from filesystem
auto getFramesMap(std::string const& rootDir) -> std::map<std::string, std::vector<std::string>>;

//  Method used to get sf element's diagonal to correctly determine its position later
auto positionHelper(sf::RectangleShape const& element)-> sf::Vector2f ;
auto positionHelper(sf::Text const& element)-> sf::Vector2f ;