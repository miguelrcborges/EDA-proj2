#pragma once

#include <string>

class InputHandler {
  public:
  template<typename T>
  T get_input(std::string prompt);

  std::string get_string(std::string prompt);
};