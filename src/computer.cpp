#include "computer.h"

#include <iostream>

Computer::Computer(char symbol_to_set) : Player(symbol_to_set) {
  depth = input.get_input<int>("What should be the computer depth?");
  if (depth > 8)
    std::cout << "WARNING: The depth is high, may take some time to the computer play." << std::endl;
  else if (depth < 0)
    std::cout << "WARNING: Values of depth lower than 0 are the same to 0." << std::endl;
}