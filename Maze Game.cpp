/*This is a code of a game which use linked list , arrays and vector data structures
The game is a maze*/


#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <chrono>  //library to calculate the execution time

using namespace std;

float user_time = 0.0;  //in this variable we save the time which user take to entering data to subtract it from total time of the program so we get the execution time of the code

void timetaken(float Time)  // function to sum user's time in all parts of the program
{
	user_time += Time;
}


class Room    //a class for construct rooms of maze and give it names and connections
{
private:
	string* name;

	Room* north;
	Room* east;
	Room* south;
	Room* west;

public:
	Room();
	Room(string roomName);

	string getName();
	void setName(string roomName);

	Room* getNorth();
	void setNorth(Room* roomP);

	Room* getEast();
	void setEast(Room* roomP);

	Room* getSouth();
	void setSouth(Room* roomP);

	Room* getWest();
	void setWest(Room* roomP);

	string getConnectionString();
};

class Player     // a class to save data of the player while the game
{
private:
	string* name;
	Room* currentRoom;

public:
	Player(string playerName);

	string getName();
	void setName(string playerName);

	Room* getRoom();
	void setRoom(Room* room);

	string getRoomName();

	void moveRoom(string direction);

};

class Map  // in this class we construct the map
{
private:
	Room* start;
	Room* end;

public:
	Map();

	Room* getStart();
	void setStart(Room* room);
	Room* getEnd();
	void setEnd(Room* room);

	void addStartRoom(Room* newRoom);
	void addLink(Room* source, Room* destination, string direction);

};

class Game  // the class where we create levels and drive the game
{
private:
	Map gameMap;

public:
	float time;

	Game();

	void setupGame();
	void startGame(Player* player);
	void setupMap1(bool defaultMap);
	void setupMap2(bool defaultMap);
	void displayMenu();
	void levels();
	string getPlayerInput();

};

Room::Room(string roomName)
{
	name = new string;
	*name = roomName;

	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
};

Room::Room()
{

};

string Room::getName()
{
	return *name;
};

void Room::setName(string roomName)
{
	*name = roomName;
};

Room* Room::getNorth()
{
	return north;
};

void Room::setNorth(Room* roomP)
{
	north = roomP;
};

Room* Room::getEast()
{
	return east;
};

void Room::setEast(Room* roomP)
{
	east = roomP;
};

Room* Room::getSouth()
{
	return south;
};

void Room::setSouth(Room* roomP)
{
	south = roomP;
};

Room* Room::getWest()
{
	return west;
};

void Room::setWest(Room* roomP)
{
	west = roomP;
};

/*
Generates the Rooms that are connection the current room, used to output the available moveable directions to the player
*/
string Room::getConnectionString()
{
	vector<string> connections;
	string connectionsString = "There appears to be a passage: ";

	if (north != NULL)
	{
		connections.push_back("North ");
	}
	if (east != NULL)
	{
		connections.push_back("East ");
	}
	if (south != NULL)
	{
		connections.push_back("South ");
	}
	if (west != NULL)
	{
		connections.push_back("West ");
	}

	for (int i = 0; i < connections.size(); i++)
	{
		string temp;

		if (i == connections.size() - 1 || connections.size() == 1)
		{
			temp = connections.at(i) + "."; // at(i) refer to the element of index i in the connections vector
		}
		else
		{
			temp = connections.at(i) + ", ";
		}

		connectionsString.append(temp);
	}

	return connectionsString;
};

Player::Player(string playerName)
{
	name = new string;
	*name = playerName;
};

string Player::getName()
{
	return *name;
};

void Player::setName(string playerName)
{
	*name = playerName;
};

Room* Player::getRoom()
{
	return currentRoom;
};

void Player::setRoom(Room* room)
{
	currentRoom = room;
};

string Player::getRoomName()
{
	return currentRoom->getName();
};

/*
Changes the players objects currentRoom variable and validates the movement direction
Parameters: direction (string) - The direction the new room will be from the existing room
*/
void Player::moveRoom(string direction)
{

	if (((direction == "N") || (direction == "n") || (direction == "North") || (direction == "north") || (direction == "NORTH")) && currentRoom->getNorth() != NULL)
	{
		cout << "You move North on the map." << endl;
		Room* tempRoom = currentRoom;
		currentRoom = tempRoom->getNorth();
	}
	else if (((direction == "E") || (direction == "e") || (direction == "East") || (direction == "east") || (direction == "EAST")) && currentRoom->getEast() != NULL)
	{
		cout << "You move East on the map." << endl;
		Room* tempRoom = currentRoom;
		currentRoom = tempRoom->getEast();
	}
	else if (((direction == "S") || (direction == "s") || (direction == "South") || (direction == "south") || (direction == "SOUTH")) && currentRoom->getSouth() != NULL)
	{
		cout << "You move South on the map." << endl;
		Room* tempRoom = currentRoom;
		currentRoom = tempRoom->getSouth();
	}
	else if (((direction == "W") || (direction == "w") || (direction == "West") || (direction == "west") || (direction == "WEST")) && currentRoom->getWest() != NULL)
	{
		cout << "You move West on the map." << endl;
		Room* tempRoom = currentRoom;
		currentRoom = tempRoom->getWest();
	}
	else
	{
		cout << "Cannot move in that direction!" << endl;
	}
};

Map::Map()
{
	start = NULL;
	end = NULL;
};

Room* Map::getStart()
{
	return start;
};

void Map::setStart(Room* room)
{
	start = room;
};

Room* Map::getEnd()
{
	return end;
};

void Map::setEnd(Room* room)
{
	end = room;
};

void Map::addStartRoom(Room* newRoom)
{
	start = newRoom;
	end = newRoom;
};


void Map::addLink(Room* source, Room* destination, string direction)
{
	if (direction == "NORTH")
	{
		source->setNorth(destination);
		destination->setSouth(source);
	}
	else if (direction == "EAST")
	{
		source->setEast(destination);
		destination->setWest(source);
	}
	else if (direction == "SOUTH")
	{
		source->setSouth(destination);
		destination->setNorth(source);
	}
	else if (direction == "WEST")
	{
		source->setWest(destination);
		destination->setEast(source);
	}
};

Game::Game()
{
	gameMap = Map();
};

/*
Sets up the game maps
*/

void Game::setupMap1(bool defaultMap)   // level1, the passage is ESEES
{
	if (defaultMap)
	{
		Room* tempArray[12];
		string name = "Room ";
		// Holds the different letters for each room in the default maze
		string roomsymbol[12] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };

		// Create each of the needed rooms
		for (int i = 0; i < 12; i++)
		{
			name = name.append(roomsymbol[i]);
			Room* tempRoom = new Room(name);
			tempArray[i] = tempRoom;
			name = "Room ";
		}

		//add the start and end room
		gameMap.addStartRoom(tempArray[0]);
		gameMap.setEnd(tempArray[11]);


		//add  links between rooms
		gameMap.addLink(tempArray[0], tempArray[4], "SOUTH");  // a-e
		gameMap.addLink(tempArray[4], tempArray[8], "SOUTH");  // e-i
		gameMap.addLink(tempArray[8], tempArray[9], "EAST");   // i-j
		gameMap.addLink(tempArray[0], tempArray[1], "EAST");   // a-b
		gameMap.addLink(tempArray[1], tempArray[5], "SOUTH");  // b-f
		gameMap.addLink(tempArray[5], tempArray[6], "EAST");   // f-g
		gameMap.addLink(tempArray[6], tempArray[10], "SOUTH"); // g-k
		gameMap.addLink(tempArray[6], tempArray[2], "NORTH");  // g-c
		gameMap.addLink(tempArray[2], tempArray[3], "EAST");   // c-d
		gameMap.addLink(tempArray[6], tempArray[7], "EAST");   // g-h
		gameMap.addLink(tempArray[7], tempArray[11], "SOUTH"); // h-l


	}

};

void Game::setupMap2(bool defaultMap)  // level2 , the passages is ENEES
{
	if (defaultMap)
	{
		Room* tempArray[12];
		string name = "Room ";
		// Holds the different letters for each room in the default maze
		string roomsymbol[12] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };

		// Create each of the needed rooms
		for (int i = 0; i < 12; i++)
		{
			name = name.append(roomsymbol[i]);
			Room* tempRoom = new Room(name);
			tempArray[i] = tempRoom;
			name = "Room ";
		}

		//add the start and end room
		gameMap.addStartRoom(tempArray[8]);
		gameMap.setEnd(tempArray[11]);

		//add  links between rooms
		gameMap.addLink(tempArray[0], tempArray[2], "SOUTH");
		gameMap.addLink(tempArray[0], tempArray[1], "EAST");
		gameMap.addLink(tempArray[1], tempArray[0], "WEST");
		gameMap.addLink(tempArray[1], tempArray[3], "SOUTH");
		gameMap.addLink(tempArray[1], tempArray[5], "EAST");
		gameMap.addLink(tempArray[2], tempArray[0], "NORTH");
		gameMap.addLink(tempArray[2], tempArray[3], "EAST");
		gameMap.addLink(tempArray[2], tempArray[8], "SOUTH");
		gameMap.addLink(tempArray[3], tempArray[1], "NORTH");
		gameMap.addLink(tempArray[3], tempArray[6], "EAST");
		gameMap.addLink(tempArray[3], tempArray[2], "WEST");
		gameMap.addLink(tempArray[4], tempArray[5], "WEST");
		gameMap.addLink(tempArray[4], tempArray[7], "SOUTH");
		gameMap.addLink(tempArray[3], tempArray[10], "SOUTH");
		gameMap.addLink(tempArray[5], tempArray[1], "WEST");
		gameMap.addLink(tempArray[5], tempArray[6], "SOUTH");
		gameMap.addLink(tempArray[5], tempArray[4], "EAST");
		gameMap.addLink(tempArray[6], tempArray[5], "NORTH");
		gameMap.addLink(tempArray[6], tempArray[7], "EAST");
		gameMap.addLink(tempArray[6], tempArray[3], "WEST");
		gameMap.addLink(tempArray[7], tempArray[11], "SOUTH");
		gameMap.addLink(tempArray[7], tempArray[6], "WEST");
		gameMap.addLink(tempArray[7], tempArray[4], "NORTH");
		gameMap.addLink(tempArray[8], tempArray[2], "NORTH");
		gameMap.addLink(tempArray[8], tempArray[9], "WEST");
		gameMap.addLink(tempArray[8], tempArray[10], "EAST");
		gameMap.addLink(tempArray[9], tempArray[8], "EAST");
		gameMap.addLink(tempArray[10], tempArray[3], "SOUTH");
		gameMap.addLink(tempArray[10], tempArray[8], "WEST");
		gameMap.addLink(tempArray[11], tempArray[7], "NORTH");

	}

};

void Game::setupGame()
{
	displayMenu();
	levels();
};

bool level2 = false;

/*
Contains Main game loop
Parameters: player (Player*) - The player object that will be used to interact with the game
*/

bool playing = true;

int n = 2;
void Game::startGame(Player* player)
{


	// Set the players start position to the start of the maze
	player->setRoom(gameMap.getStart());
	string currentMove;
	cout << endl;

	while (playing)
	{
		cout << "\nYou are currently standing In: " << player->getRoomName() << endl<<endl;
		cout << player->getRoom()->getConnectionString() << endl<<endl;
		cout << "Where would you like to move?   ";

		currentMove = getPlayerInput();

		// checks if the player wants to quit the game
		if (currentMove == "q" || currentMove == "Q" || currentMove == "Quit" || currentMove == "quit" || currentMove == "QUIT")

		{
			cout << "Quitting Game!" << endl;
			playing = false;
		}
		else
		{
			player->moveRoom(currentMove);

			// Checks if the player has finished the maze
			if (player->getRoom() == gameMap.getEnd())
			{
				cout << "\nWell done " << player->getName() << " congratulations now you are out of maze 🎉🎉!" << endl;

				// checks if the player reach the last level
				if (n > 0)
				{

					cout << "Would you like to play the next level ? \nif Yes press Y   if No press any key ";
					string playAgain = getPlayerInput();
					cout << endl;

					// checks if the player wants to play another level
					if ((playAgain == "y") || (playAgain == "Y") || (playAgain == "yes") || (playAgain == "Yes") || (playAgain == "YES"))
					{

						level2 = true;

						levels();

					}
					else
					{
						playing = false;
					}
				}
				else
				{
					playing = false;
				}


			}
		}
	}
};

/*
Displays the main menu and handles the users input
*/
string name;

void Game::displayMenu()
{
	cout << "Welcome to the maze game!\n" << endl;
	cout<<"you are in maze consist of rooms connected by passages you should choose right passage go out of maze "<<endl<<endl;
	cout << "Notice that, if you want to move a direction you can write it or just the first letter of it " << endl<<endl;

	cout << "Enter your name:  ";

	auto START = chrono::steady_clock::now();  // to stat count the time which the user take while enter his name

	getline(cin, name);

	auto END = chrono::steady_clock::now(); // stop counting here

	time = chrono::duration_cast<chrono::nanoseconds>(END - START).count(); //calculate time

	timetaken(time); // send it to be saved



	cout << " \nTO quit the game press Q\n\nGood Luck :)\n"<<endl;
};
/*
choose the level
*/
void Game::levels()
{
	Player* player = new Player(name);


	n--;  //changeing the level

	if (level2)
	{
		setupMap2(true);
	}
	else setupMap1(true);

	startGame(player);

};

/*
Generic user input method to reduce code clutter
*/
string Game::getPlayerInput()
{
	string input;
	cout << "-----> ";

	auto start = chrono::steady_clock::now();  // to stat count the time which the user take while enter his answer

	cin >> input;

	auto end = chrono::steady_clock::now();  // stop counting here

	time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();  //calculate time
	timetaken(time);  // send time to be saved


	return input;
};




int main()
{
	float total_time = 0.0; //in this variable to save the execution time of all the program including the time of playing

	auto Start = chrono::steady_clock::now();  // stat count the time

	Game game;

	game.setupGame();

	auto End = chrono::steady_clock::now();  // stop counting


	total_time = chrono::duration_cast<chrono::nanoseconds>(End - Start).count();  //calculate time

	cout << "The Execution Time is :  " << (total_time - user_time) << " ns\n ";   // show time in ns

	cout << "The Execution Time is :  " << ((total_time - user_time) * 0.000000001) << " s\n ";  // show time in seconds


	return 0;
}
