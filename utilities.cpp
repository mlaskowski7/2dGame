#include "utilities.hpp"

auto getFramesMap(std::string const& rootDir) -> std::map<std::string, std::vector<std::string>>{
    auto result = std::map<std::string, std::vector<std::string>>();

    for(auto const& subdir : std::filesystem::directory_iterator(rootDir)){
        if(subdir.is_directory()){
            auto paths = std::vector<std::string>();
            for(auto const& image : std::filesystem::directory_iterator(subdir.path())){
                paths.push_back(image.path().string());
            }

            auto key = subdir.path().filename().string();
            result[key] = paths;
        }
    }
    fmt::println("Generated frames map - {}", result);
    return result;
}

//  method used to get element's diagonal that is helping in setting up element's position
auto positionHelper(sf::RectangleShape const& element)-> sf::Vector2f{
    return sf::Vector2f(element.getSize().x/2, element.getSize().y/2);
}
auto positionHelper(sf::Text const& element)-> sf::Vector2f{
    return sf::Vector2f(element.getLocalBounds().width/2, element.getLocalBounds().height/2);
}
