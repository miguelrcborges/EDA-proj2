#include "game.h"
#include "inputHandler.h"
#include <cstdlib>

int main() {
	InputHandler input;
	srand(time(NULL));
	do
	{
		Game game;
		game.loop();
		char play_again = toupper(input.get_input<char>("Do you want to play again? Y/N"));
		if (play_again == 'N')
		{
			break;
		}
		while (play_again != 'Y' && play_again != 'N')
		{
			std::cout << "Please provide a valid answer to the question \n";
			play_again = toupper(input.get_input<char>("Do you want to play again? Y/N"));
		}

	} while (1);
}