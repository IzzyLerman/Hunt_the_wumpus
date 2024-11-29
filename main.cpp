#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "game.h"
#include "display.h"

using namespace std;

/*********************************************************************
** Program Filename: asm4
** Author: Lermani
** Date: 11/27/23
** Description: Hunt the Wumpus is a dungeon-crawler game where information
** is hidden from the user. The goal is to grab the gold and return to the 
** starting location, or to kill the Wumpus with an arrow.
** Input: Cave size n * y * x; debug mode option; user can choose to play again.
** Output: Game information
*********************************************************************/

/*********************************************************************
** Function: main
** Description: Executes the main game control.
** Parameters: 
** Pre-Conditions:
** Post-Conditions: Program terminates.
*********************************************************************/

int main()
{
	//set the random seed
	srand(time(NULL));
	
	int wid, len, num_floors;
	bool debug = false;
	bool restart;
	bool keep_settings;

	do{
		wid = get_width();
		len = get_length();
		num_floors = get_num_floors();
		debug = get_debug();
		cbreak();
		initscr();
		do{
			Game g;
			g.play_game(num_floors, len, wid, debug);
			restart = get_restart();
			if(restart){
				keep_settings = get_keep_settings();
			}
		raw();
		endwin();
		}while(restart && keep_settings);
	}while(restart);

	return 0;
}