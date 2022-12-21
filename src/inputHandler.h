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
  T get_input(std::string prompt) const {
    char exit_confirmation;
    T input;
ask_input:
    std::cout << prompt << "\n> ";

    if (std::cin >> input) {
      bool was_it_alone = std::cin.get() == '\n'; 
      if (!was_it_alone) {
        std::cout << "Please, send a valid value." << std::endl;
        std::cin.ignore(100000, '\n');
        goto ask_input;
      }
      return input;
    }

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
        std::cin.ignore(100000,'\n');

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
        std::cin.ignore(100000,'\n');

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