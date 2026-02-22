#include <random>
#include <iostream>

class Room { // Room Class for cave room
	int fake_num; // Number that is only displayed to the user (randomly generated among a set of available numbers from 1-12)
	bool is_pit = false;
	Room* c_rooms[3] = {NULL, NULL, NULL}; // Pointers to connecting rooms
	bool is_bat = false;
	int current_null = 0; //First null index in c_Rooms
public:
	Room(int random) :fake_num{ random } {} // Constructor which randomly assigns fake number based on available numbers from 1 - 12.
	void SetPit() {is_pit = true;}
	bool GetPit() { return is_pit; }
	void SetBat() { is_bat = true; }
	bool GetBat() { return is_bat; }
	int Getfake_num() { return fake_num; }
	Room* getConRoom(int fake_num) { //Gets the pointer to a connected room of the specified fake_num. Returns NULL if room isn't connected.
		for (int i = 0; i < 3; i++) {
			if (c_rooms[i]->Getfake_num() == fake_num) {
				return c_rooms[i];
			}
		}
		return NULL;
	}
	Room* getConnectedIndex(int i) { //Gets the pointer of a connected room of the specified index in c_room
		return c_rooms[i];
	} 
	void Add_Connected_Rooms(Room* r) { //Adds room to c_room based on current index that is null
		c_rooms[current_null] = r;
		current_null++;
	}
	
	void DebugPrint() {
		Room* a = c_rooms[0];
		Room* b = c_rooms[1];
		Room* c = c_rooms[2];
		int n1 = a->Getfake_num();
		int n2 = b->Getfake_num();
		int n3 = c->Getfake_num();
		std::cout << "Room: " << fake_num << " is connected to Room: " << n1 << "," << n2 << "," << n3 <<" Is pit: "<< is_pit << " Is bat:" << is_bat << "\n\n";
	}
	~Room() {}
	
};
