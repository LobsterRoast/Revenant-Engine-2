#include "SerializeString.hpp"

// Divides strings into tokens to make them easier to work with

std::vector<std::string> SerializeString(std::string input, std::string delimiter) {
    std::vector<std::string> serializedString;
    size_t delimiterIndex;
    while((delimiterIndex = input.find(delimiter)) != std::string::npos) {
        serializedString.push_back(input.substr(0, delimiterIndex));
        input.erase(0, delimiterIndex+1);
    }
    serializedString.push_back(input);
    return serializedString;
}