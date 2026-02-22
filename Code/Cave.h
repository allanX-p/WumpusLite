#include "Room.h"
#include "Player.h"
class Cave { // Cave Object used as main game object as well
	Room* rooms[12]; //Room list
	Room* wumpus_room = NULL; //Pointer to room where wumpus is in
	Player player = Player();
	bool game_over = false;
public:

	Cave(int);//Creates Room Arrangement then stores in list.
	void print_rooms() { //Prints all rooms and the connected rooms to them
		for (Room* r : rooms) {
			r->DebugPrint();
		}
		std::cout << "Wumpus Is Currently In Room: " << wumpus_room->Getfake_num();
	
	}
	void Player_turn(); // Function which prints the player status and allows player to perform actions
	void Move_player(int r); //Moves Player by first checking if room is connected and then setting the current room of the player object to the room
	void Move_wumpus();
	bool Is_game_over() { return game_over; }


};