#include "ConsoleInputs.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

int cinInteger(std::string init_message, std::string invalid_arg_message) {
    std::string input;
    std::cout << init_message << std::flush;
    while(true) {
        std::cin >> input;
        try {
            return std::stoi(input);
        }
        catch(const std::invalid_argument&) {
            std::cout << invalid_arg_message;
        }
        catch(const std::out_of_range&) {
            std::cout << "Your input is out of range. Please input a valid integer value.\n"; 
        }
        std::cout << std::flush;
    }
}