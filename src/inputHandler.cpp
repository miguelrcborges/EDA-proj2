#include "inputHandler.h"

#include <iostream>
#include <cctype>
#include <cstdlib>

#ifndef _WIN32
#include <cstiod>
#endif

template<typename T>
T InputHandler::get_input(std::string prompt) const {
  char exit_confirmation;
  T input;
ask_input:
  std::cout << prompt;

  if (std::cin >> input) {
    bool was_it_alone = std::cin.get() == '\n'; 
    if (!was_it_alone) {
      std::cout << "Please, send only one integer number." << std::endl;
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


std::string InputHandler::get_string(std::string prompt) const {
  char exit_confirmation;
  std::string input;
ask_input:
  std::cout << prompt;

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