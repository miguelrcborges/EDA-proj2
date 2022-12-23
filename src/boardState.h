#pragma once

#include "board.h"

#include <vector>

/**
* Our BoardState class. This class is used by the Computer class to find the best move.
* 
* It holds the a Board corresponding to a specific scenario, a value representing its evaluation
* for the computer who is doing the calculation, as well how much orders of child states there is (depth).
*/
class BoardState {
public:
  /**
  * The base constructor. Creates a board state relying on the current board and the Computer information.
  *
  * @param game_board Current board.
  * @param depth Computer's depth.
  * @param symbol_to_play Computer's symbol, since it is the one playing.
  */
  BoardState(Board &game_board, int depth, char symbol_to_play);

  /**
  * A second constructor made to speed up the generation of states. The recursive call of the first one
  * would make so a copy of a Board would be required to be passed to the childs (old code is present
  * as a comment for reference), so this constructor will also play the move at a given column. It accepts
  * an int pointer that will be pointing afterwards to the row where the symbol was placed.
  *
  * @param game_board Parent's state's Board (which will be simulated a move on).
  * @param parents_depth Parent's state's depth. 
  * @param symbol_playing Parent's state's symbol, which will be played on this state.
  * @param column Index of the column which will be played on.
  * @param row Integer pointer which, after execution, will hold the index of the row where the symbol will be placed.
  */
  BoardState(Board &game_board, int parents_depth, char symbol_playing, int column, int &row);

  /**
  * The desconstructor of the state. It frees the memory occupied by its child states before freeing himself.
  */
  ~BoardState();

  /**
  * A method created so we could cache States generated on previous moves.
  * It returns a pointer pointing to the current state (since now it was moved 2 turns) and frees the old state.
  *
  * @param computer_move Last move played by the computer using this AI in the past turn.
  * @param opponent_move Last move played by the opponent.
  */
  BoardState *update_state(int computer_move, int opponent_move);

  /**
  * A method that runs evaluation of every possible child state and returns the best moves possible.
  * 
  * @param player_symbol The symbol of the computer which is playing.
  * @return The index of the columns corresponding to the best moves.
  */
  std::vector<int> get_best_moves(char player_symbol) const;
private:
  /**
  * An helper method for get_best_moves which evaluates a single state, which can call
  * an evaluation on its child states to so it can find its value.
  *
  * @param player_symbol Symbol of the player using this AI.
  */
  void evaluate(char player_symbol);

  /**
  * An helper method to update_state which increases the depth of every current state by 2,
  * since has passed 2 turns. 
  */
  void increment_depth();

  /**
  * An helper method to update_state which will generate the missing state after moving the state to the
  * right child.
  */
  void generate_missing_states();

  /**
  * Board corresponding to this specific state of the game.
  */
  Board board;

  /**
  * Score corresponding to this state in the perspective of the computer who generated this states.
  */
  int value;

  /**
  * Represents how much more orders of child states there could be.
  */
  int depth;

  /**
  * Last simulated move so it can be passed to the Board's check_win method.
  */
  std::array<int, 2> last_move;

  /**
  * Vector holding the possible derivated states from this one.
  */
  std::vector<BoardState *> child_states;

  /**
  * Symbol that is going to play in the moves that are being simulated.
  */
  char symbol_to_play;
};