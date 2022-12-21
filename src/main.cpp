#include "game.h"
#include <cstdlib>

int main() {
  srand(time(NULL));
  Game game;
  game.loop();
}