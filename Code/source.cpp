#include "Cave.h"



int main() {
	srand(time(NULL));
	Cave newCave(1);
	std::cout << "Randomly Generating Cave\n";
	newCave.Player_turn();

	while (1) {
		newCave.Player_turn();
		if (newCave.Is_game_over() == true) {
			std::cout << "Play Again? (Y/N): ";
			char a;
			std::cin >> a;
			if (a == 'Y') { // Resets the game if player wants to play again
				newCave = Cave(1);
				std::cout << "\nRandomly Generating Cave\n";
				//newCave.print_rooms();
				while (getchar() != '\n');
			}
			else {
				break;
			}
		}
	}
	std::cout << "THANKS FOR PLAYING";
}

