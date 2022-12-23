#pragma once

#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>

#ifndef _WIN32
#include <cstdio>
#endif

class InputHandler {
public:
    template<typename T>

    /**
    * Gets valid input of necessary type.
    * If it receives an invalid input, asks
    * to re-entrer input until it is valid.
    *
    * @return Valid input.
    */
    T get_input(std::string prompt) const {
        char exit_confirmation;
        T input;
        //asks for input until it has a valid one.
    ask_input:
        std::cout << prompt << "\n> ";

        if (std::cin >> input) {
            bool was_it_alone = std::cin.get() == '\n';
            //return to the beggining if the received input is not valid.
            if (!was_it_alone) {
                std::cout << "Please, send a valid value." << std::endl;
                std::cin.ignore(100000, '\n');
                goto ask_input;
            }
            return input;
        }

        //if the user types EOF.
        do {
            std::cout << "\nDo you really want to quit? (Y/N)\n> ";
            bool eof = std::cin.eof();
            if (std::cin.fail()) {
                std::cin.clear();
#ifndef _WIN32
                clearerr(stdin);
#endif
            }

            if (!eof && std::cin.peek() != '\n')
                std::cin.ignore(100000, '\n');

            std::cin >> exit_confirmation;
            bool was_it_alone = std::cin.get() == '\n';
            if (!was_it_alone) {
                std::cout << "Please, send only one character." << std::endl;
                std::cin.ignore(100000, '\n');
                continue;
            }
            exit_confirmation = toupper(exit_confirmation);
            if (exit_confirmation == 'N') goto ask_input;
            std::cout << "Exit confirmation must be either Y or N!" << std::endl;
        } while (exit_confirmation != 'Y');

        std::exit(0);
    }

    /**
    * Gets valid input when a string with spaces is required.
    *
    * @return Valid input.
    */
    std::string get_string(std::string prompt) const {

        char exit_confirmation;
        std::string input;
    ask_input:
        std::cout << prompt << "\n> ";

        if (getline(std::cin, input))
            return input;

        do {
            std::cout << "\nDo you really want to quit? (Y/N)\n> ";
            bool eof = std::cin.eof();
            if (std::cin.fail()) {
                std::cin.clear();
#ifndef _WIN32 
                clearerr(stdin);
#endif
            }

            if (!eof && std::cin.peek() != '\n')
                std::cin.ignore(100000, '\n');

            std::cin >> exit_confirmation;
            bool was_it_alone = std::cin.get() == '\n';
            if (!was_it_alone) {
                std::cout << "Please, send only one character." << std::endl;
                std::cin.ignore(100000, '\n');
                continue;
            }
            exit_confirmation = toupper(exit_confirmation);
            if (exit_confirmation == 'N') goto ask_input;
            std::cout << "Exit confirmation must be either Y or N!" << std::endl;
        } while (exit_confirmation != 'Y');

        std::exit(0);
    }
};
