#ifndef GAME_H
#define GAME_H 

#include <vector>
#include <iostream> 
#include "room.h"
#include "cave.h"

using namespace std;

//Game interface 
class Game
{
private:

	//other member variables:
	int num_floors;
	int length; 			//length of the board
	int width;  			//width of the board
	int num_arrows; 		//keep track of number of arrows remaining
	bool debug_view;		//debug mode or not
	Cave c;
	//feel free to add more variables...

public:

	//suggested functions:
	Game();
	~Game();
	
	void set_up(int, int, int);

	void display_game() const;
	void display_percepts() const;

	int check_win() const;

	char get_dir();
	void wumpus_move();
	void fire_arrow();
	string trigger_event();

	void move();

	char get_input();

	void end_game();

	void play_game(int, int, int, bool);

	//feel free (and you will need) to add more functions...




};
#endif