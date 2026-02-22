class Player {
	int arrows = 3;
	Room* current_room = NULL;
public:
	Player() {}
	void Set_room(Room* room) {	current_room = room; }
	Room* getCurRoom() { return current_room; } //Gets Current Room Of Player
	void Print_Status(Room* wumpus_room) { //Prints Current Status of the player
		if (current_room->getConnectedIndex(0) == wumpus_room || current_room->getConnectedIndex(1) == wumpus_room || current_room->getConnectedIndex(2) == wumpus_room) {
			std::cout << "\"I smell a wumpus\" \n";
		}
		if (current_room->getConnectedIndex(0)->GetPit() == true || current_room->getConnectedIndex(1)->GetPit() == true || current_room->getConnectedIndex(2)->GetPit() == true) {
			std::cout << "\"I feel a breeze\" \n";
		}
		if (current_room->getConnectedIndex(0)->GetBat() == true || current_room->getConnectedIndex(1)->GetBat() == true || current_room->getConnectedIndex(2)->GetBat() == true) {
			std::cout << "\"I hear a bat\" \n";
		}
		std::cout << "You are in room " << current_room->Getfake_num() << "; there are tunnels to rooms " << current_room->getConnectedIndex(0)->Getfake_num() << "," << current_room->getConnectedIndex(1)->Getfake_num() << "," << current_room->getConnectedIndex(2)->Getfake_num() << "\n";
		std::cout << "Move or Shoot (M/S): ";
	}
	char getInput() {
		char a;
		std::cin >> a;
		return a;
	}
	int getNumInput() {
		int a;
		std::cin >> a;
		return a;
	}

	Room* getConRoom(int r) { //Gets the connected room of the specified index to the current room the player is in.
		return current_room->getConRoom(r);
	}

	char Fire_arrow(int size, int room_nums[], Room* wumpus_room) { //Shoots the arrow and keeps track of which room it is in
		if (arrows < 1) {
			return 'o';
		}
		arrows--;
		Room* arrow_room = current_room;
		int r_index = 0;
		for (int i = 0; i < size; i++) {
			int a = arrow_room->getConnectedIndex(0)->Getfake_num();
			int b = arrow_room->getConnectedIndex(1)->Getfake_num();
			int c = arrow_room->getConnectedIndex(2)->Getfake_num();
			if (room_nums[i] != a && room_nums[i] != b && room_nums[i] != c) {
				r_index = std::rand() % 3;
			}
			else if (room_nums[i] == a) {
				r_index = 0;
			}
			else if (room_nums[i] == b) {
				r_index = 1;
			}
			else {
				r_index = 2;
			}
			arrow_room = arrow_room->getConnectedIndex(r_index);
			if (arrow_room == current_room) {
				return 'p';
			}
			if (arrow_room == wumpus_room) {
				return 'w';
			}
		}
		std::cout << "\nYou Fire an Arrow. You Have " << arrows << " Arrows Left\n";
		return 'n';
	}

};
