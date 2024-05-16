#include <map>
#include <filesystem>

#include <fmt/core.h>
#include <fmt/ranges.h>

//  Method that is used to populate image paths for animation frames for each character from filesystem
auto getFramesMap() -> std::map<std::string, std::vector<std::string>>;