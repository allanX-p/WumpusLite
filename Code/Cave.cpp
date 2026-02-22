#include "Cave.h"

Cave::Cave(int) {
	//Generates Random Distinct Numbers from 1-12 (Necessary for fake_num for rooms)->
	int l[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int endp = 11;
	int randind = 0;
	for (int i = 0; i < 12; i++) {
		if (endp != 0) {
			randind = std::rand() % endp + 1;
		}
		else {
			randind = 0;
		}
		
		Room* new_room = new Room(l[randind]);
		rooms[i] = new_room;
		l[randind] = l[endp];
		--endp;
	}
	
	//Sets the connection in such a way that the whole cave is interconnected and every room is connected to 3 points (Done manually using arbiturary indexes)
	Room* temp = rooms[0];
	temp->Add_Connected_Rooms(rooms[1]);
	temp->Add_Connected_Rooms(rooms[2]);
	temp->Add_Connected_Rooms(rooms[11]);
	
	temp = rooms[1];
	temp->Add_Connected_Rooms(rooms[0]);
	temp->Add_Connected_Rooms(rooms[2]);
	temp->Add_Connected_Rooms(rooms[3]);
	
	temp = rooms[2];
	temp->Add_Connected_Rooms(rooms[0]);
	temp->Add_Connected_Rooms(rooms[1]);
	temp->Add_Connected_Rooms(rooms[5]);

	temp = rooms[3];
	temp->Add_Connected_Rooms(rooms[1]);
	temp->Add_Connected_Rooms(rooms[4]);
	temp->Add_Connected_Rooms(rooms[7]);

	temp = rooms[4];
	temp->Add_Connected_Rooms(rooms[3]);
	temp->Add_Connected_Rooms(rooms[5]);
	temp->Add_Connected_Rooms(rooms[10]);
	
	temp = rooms[5];
	temp->Add_Connected_Rooms(rooms[2]);
	temp->Add_Connected_Rooms(rooms[4]);
	temp->Add_Connected_Rooms(rooms[6]);

	temp = rooms[6];
	temp->Add_Connected_Rooms(rooms[5]);
	temp->Add_Connected_Rooms(rooms[9]);
	temp->Add_Connected_Rooms(rooms[11]);
	
	temp = rooms[7];
	temp->Add_Connected_Rooms(rooms[3]);
	temp->Add_Connected_Rooms(rooms[8]);
	temp->Add_Connected_Rooms(rooms[11]);
	
	temp = rooms[8];
	temp->Add_Connected_Rooms(rooms[7]);
	temp->Add_Connected_Rooms(rooms[9]);
	temp->Add_Connected_Rooms(rooms[10]);
	
	temp = rooms[9];
	temp->Add_Connected_Rooms(rooms[6]);
	temp->Add_Connected_Rooms(rooms[8]);
	temp->Add_Connected_Rooms(rooms[10]);
	
	temp = rooms[10];
	temp->Add_Connected_Rooms(rooms[4]);
	temp->Add_Connected_Rooms(rooms[8]);
	temp->Add_Connected_Rooms(rooms[9]);

	temp = rooms[11];
	temp->Add_Connected_Rooms(rooms[0]);
	temp->Add_Connected_Rooms(rooms[6]);
	temp->Add_Connected_Rooms(rooms[7]);
	randind = std::rand() % 12;
	//Starts Player in Random Room
	player.Set_room(rooms[randind]);
	//Randomly Assings a pit to the rooms (But not to the room player is in)
	int rpit = std::rand() % 12;
	while (rpit == randind) {rpit = std::rand() % 12; }
	rooms[rpit]->SetPit();
	//Assigns Bat Similar To How Pit Was Assigned
	rpit = std::rand() % 12;
	while (rpit == randind) { rpit = std::rand() % 12; }
	rooms[rpit]->SetBat();
	//Set Wumpus Location
	rpit = std::rand() % 12;
	while (rpit == randind) { rpit = std::rand() % 12; }
	wumpus_room = rooms[rpit];
}


void Cave::Player_turn() { //Function which prints the player status and allows player to perform actions
	if (game_over == true) { return; }
	std::cout << "\n";
	player.Print_Status(wumpus_room);
	char in = player.getInput();
	if (in != 'M' && in != 'S') {
		std::cout << "Invalid Input! Please Try Again\n";
		//Clears Input Buffer
		while (getchar() != '\n');
		Player_turn();
	}
	else if (in == 'M') { //Prepares to move player if input is M
		std::cout << "Enter Room Number: ";
		int r = player.getNumInput();
		Move_player(r);
	}
	else if (in == 'S') { // Prepares to fire arrows if input is S
		std::cout << "No. Of Rooms (1-3): ";
		int r = player.getNumInput();
		if (r < 1 || r > 3) {
			std::cout << "Invalid Input (INVALID NUMBER OF ROOMS)! Please Try Again\n";
			while (getchar() != '\n');
			return;
		}
		int room_nums[3];
		std::cout << "Enter Room Number(s): ";
		for (int i = 0; i < r; i++) {
			room_nums[i] = player.getNumInput();
		}
		while (getchar() != '\n');
		char arrow = player.Fire_arrow(r, room_nums, wumpus_room);
		switch (arrow) {
		case 'p':
			std::cout << "\nGAME OVER. YOU WERE HIT BY YOUR ARROW\n";
			game_over = true;
			return;
		case 'w':
			std::cout << "\nYOU GOT THE WUMPUS! YOU WIN!\n";
			game_over = true;
			return;
		case 'o':
			std::cout << "\nInvalid Input (YOU ARE OUT OF ARROWS)! Please Try Again\n";
			Player_turn();
			return;
		case 'n':
			std::cout << "You Hit Nothing. The Wumpus Has Moved\n";
			Move_wumpus();
		}
		
	}

}

void Cave::Move_player(int r) { //Moves Player by first checking if room with specified fake number is connected and then setting the current room of the player object to the room. Also Checks If Room has pit or bats and applies the effects.
	Room* room = player.getConRoom(r);
	if (r == 0) { room = player.getCurRoom(); }
	if (room == NULL) {
		std::cout << "Invalid Input (BAD ROOM NUMBER)! Please Try Again\n";
		//Clears Input Buffer
		while (getchar() != '\n');
		Player_turn();
		return;
	}
	if (room->GetPit() == true) {
		std::cout << "\nGAME OVER. YOU FELL INTO A PIT!\n";
		game_over = true;
		return;
	}
	else if (room->GetBat() == true) { // Sends player to random room
		std::cout << "\nA Giant Bat Carries You To a Random Room!\n";
		int r = std::rand() % 12;
		player.Set_room(rooms[r]);
		Move_player(0);
		return;
	}
	else if (room == wumpus_room) {
		std::cout << "\nGAME OVER. YOU WERE EATEN BY THE WUMPUS!\n";
		game_over = true;
		return;
	}
	player.Set_room(room);
}

void Cave::Move_wumpus() { //Moves the wumpus to a random connected room and checks if it has eaten player
	int r_index = std::rand() % 3;
	wumpus_room = wumpus_room->getConnectedIndex(r_index);
	if (wumpus_room == player.getCurRoom()) {
		std::cout << "\nGAME OVER. YOU WERE EATEN BY THE WUMPUS!\n";
		game_over = true;
		return;
	}
}