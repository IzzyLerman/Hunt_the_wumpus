#include "game.h"
#include "gold.h"
#include "stalactites.h"
#include "bats.h"
#include "wumpus.h"

#include <iostream>

using namespace std;

//Game Implementation

Game::Game(){}

Game::~Game(){}

/*********************************************************************
** Function: set_up
** Description: sets up the game
** Parameters: int; # of floors
**			   int; # of rows
**			   int; # of cols
** Pre-Conditions: 
** Post-Conditions: game board is populated
*********************************************************************/ 

void Game::set_up(int n, int l, int w){
	//set up the game
	this->num_floors = n;
	this->length = l;
	this->width = w;

	this->num_arrows = 3; 	//start with 3 arrows

	c.set_up_grid(n, l, w);
	// randomly insert events (2 bats, 2 stalactites, 1 wumpus, 1 gold)
	// into the board
	c.populate();
	

}

/*********************************************************************
** Function: display_game
** Description: displays the game board and percepts
** Parameters:
** Pre-Conditions: game board is populated
** Post-Conditions: 
*********************************************************************/ 

void Game::display_game() const{
	printw("\n\n");
	printw("Arrows remaining: %i | ", this->num_arrows);
	printw("Floor #%i\n",c.get_player_floor() + 1);
	string line = "";
	for (int i = 0; i < this->width; ++i){
		line += "++-----";
	}
	line += "++\n";
	for (int i = this->length - 1;  i >= 0; i--)
	{
		printw(line.c_str());
		printw("||");
		
		for (int j = 0; j < this->width; j++)
		{

			if(c.get_room(c.get_player_floor(), i, j).get_has_player()){
				printw("*");
			}else{
				printw(" ");
			}

			if(c.get_room(c.get_player_floor(), i, j).get_ladder() != 0 || debug_view){
				printw(c.get_room(c.get_player_floor(), i, j).get_symbol().c_str());	
			}else{
				printw("   ");
			}
			printw(" ||");
		}
		printw("\n");
	}
	printw(line.c_str());
	refresh();
	Game::display_percepts();

}

void Game::display_percepts() const{
	c.display_percepts();
}

/*********************************************************************
** Function: check_win
** Description: multiple win conditions and returns an int code for 
** that win
** Parameters: 
** Pre-Conditions: game board is set up
** Post-Conditions: returns corresponding code - returns 0 when game is not over
*********************************************************************/ 

int Game::check_win() const{
	if(!c.get_player_alive()){
		if(c.get_wump_death()){
			return -1;
		}else{
			return -2;
		}
	}else if(!c.get_wumpus_alive()){
		return 1;
	}else if(c.check_gold_win()){
		return 2;
	}else{
		return 0;
	}
	
}

/*********************************************************************
** Function: get_dir
** Description: get an arrow direction from the user
** Parameters: 
** Pre-Conditions:
** Post-Conditions: returns input
*********************************************************************/ 

char Game::get_dir(){
	char input;
	bool bad_input = true;
	printw("\n\n");
	do{
		display_game();
		printw("Fire an arrow....\n");
		printw("w-up\n");
		printw("a-left\n");
		printw("s-down\n");
		printw("d-right\n");
		printw("Enter direction: \n");
		refresh();
		input = getch();
		wclear(stdscr);
		if (input == 'w' || input == 'a' || input == 's' || input == 'd'){
			bad_input = false;
		}else{
			display_game();
			printw("Invalid input. \n");
		}
	}while(bad_input);
	
	return input;
}

/*********************************************************************
** Function: wumpus_move
** Description: 75% chance to move the Wumpus
** Parameters: 
** Pre-Conditions: 
** Post-Conditions: Wumpus has moved
**********************************************************************/ 

void Game::wumpus_move(){
	if(rand()%4 != 3){
		c.wumpus_move();
		printw("ROOOOAAAR!!! The ground shakes as the Wumpus finds a new place to rest.\n");	
	}else{
		printw("It's too quiet...\n");
	}
	return;
}

/*********************************************************************
** Function: fire_arrow
** Description: Fires an arrow; the arrow moves three spaces and then 
** breaks, unless it hits a wall or the wumpus. It then updates conditions
** based on the result and calls move_wumpus
** Parameters: 
** Pre-Conditions: 
** Post-Conditions: 
*********************************************************************/ 

void Game::fire_arrow(){
	char dir = get_dir();
	int distance_left = 3;
	bool wall_ahead = false;
	bool wall_here = false;
	int arrow_current_pos[2] = {c.get_player_y(),c.get_player_x()};
	while(!wall_ahead && distance_left > 0){
		switch(dir){
		case 'w':
			arrow_current_pos[0] ++;
			if(arrow_current_pos[0] >= length){
				wall_here = true;
			}
			if(arrow_current_pos[0] >= length - 1){
				wall_ahead = true;
			}
			break;
		case 'd':
			arrow_current_pos[1] ++;
			if(arrow_current_pos[1] >= length){
				wall_here = true;
			}
			if(arrow_current_pos[1] >= width - 1){
				wall_ahead = true;
			}
			break;
		case 's':
			arrow_current_pos[0] --;
			if(arrow_current_pos[0] <= -1){
				wall_here = true;
			}
			if(arrow_current_pos[0] <= 0){
				wall_ahead = true;
			}
			break;
		case 'a':
			arrow_current_pos[1] --;
			if(arrow_current_pos[1] <= -1){
				wall_here = true;
			}
			if(arrow_current_pos[1] <= 0){
				wall_ahead = true;
			}
			break;
		}if(wall_here){}
		else if(c.get_room(
			c.get_player_floor(),arrow_current_pos[0],arrow_current_pos[1]).get_symbol() == "-.-"){
			c.set_wumpus_alive(false);
		}
		distance_left--;
	}
	if(c.get_wumpus_alive() == true){
		wumpus_move();
	}
	num_arrows--;
	return;


}

string Game::trigger_event(){
	return c.trigger_event();
}

/*********************************************************************
** Function: move
** Description: moves the player or fires an arrow based on user input
** Parameters: 
** Pre-Conditions: 
** Post-Conditions: player either moves or fires an arrow
*********************************************************************/ 

void Game::move() {
	bool bad_input = true;
	char input;
	do{
		input = Game::get_input();
		wclear(stdscr);
		if(c.get_confused() > 0){
			switch(input){
			case 'w':
				input = 's';
				break;
			case 's':
				input = 'w';
				break;
			case 'a':
				input = 'd';
				break;
			case 'd':
				input = 'a';
			}
			printw("You are confused for %i more turns\n", c.get_confused() - 1);
			refresh();
		}
		if (input == 'f'){
			if(num_arrows <= 0){
				bad_input = true;
				printw("No arrows left!\n");
			}else{
				Game::fire_arrow();
				bad_input = false;
			}
			return;
		}
		switch(input){
			case 'w':
				if(c.get_player_y() >= length - 1){
					display_game();
					printw("Can't move outside the cave boundaries. ");
				}else{
					c.move_up();
					bad_input = false;
				}break;
			case 'a':
				if(c.get_player_x() <= 0){
					display_game();
					printw("Can't move outside the cave boundaries. ");
				}
				else{
					c.move_left();
					bad_input = false;
				}
				break;
			case 's':
				if(c.get_player_y() <= 0){
					display_game();
					printw("Can't move outside the cave boundaries. ");
				}
				else{
					c.move_down();
					bad_input = false;
				}
				break;
			case 'd':
				if(c.get_player_x() >= width - 1){
					display_game();
					printw("Can't move outside the cave boundaries. ");
				}
				else{
					c.move_right();
					bad_input = false;
				}
				break;
		}
		refresh();
	}while(bad_input);
	c.decr_confused();
}

/*********************************************************************
** Function: get_input
** Description: get user input for their action on their turn
** Parameters: 
** Pre-Conditions: user's turn
** Post-Conditions: returns input
*********************************************************************/ 

char Game::get_input(){
	//get action, move direction or firing an arrow
	
	char input;
	bool bad_input = true;
	printw("\n\n");
	do{
		printw("Player move...\n");
		printw("w-up\n");
		printw("a-left\n");
		printw("s-down\n");
		printw("d-right\n");
		printw("f-fire an arrow\n");
		printw("Enter input: \n");
		refresh();
		input = getch();
		wclear(stdscr);
		if (input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'f'){
			bad_input = false;
		}else{
			display_game();
			printw("Invalid input. \n");
		}
	}while(bad_input);
	
	return input;
}

/*********************************************************************
** Function: end_game
** Description: displays an error message based on the win condition
** Parameters: 
** Pre-Conditions: game has ended
** Post-Conditions:
*********************************************************************/ 

void Game::end_game(){
	int win = Game::check_win();
	switch(win){
	case -2:
		printw("You were killed by a falling stalactite.\n");
		break;
	case -1:
		printw("The Wumpus ate you alive.\n");
		break;
	case 1:
		printw("Your arrow pierced the Wumpus' heart and killed it. You win!!!\n");
		break;
	case 2:
		printw("You escaped with the gold! You win!!!\n");
		break;
	}
}

/*********************************************************************
** Function: play_game
** Description: game main loop execution
** Parameters: int;	# of floors  
** 			   int; # of cols
** 			   int; # of rows
** 			   bool; debug mode
** Pre-Conditions: 
** Post-Conditions: game ends
*********************************************************************/ 

void Game::play_game(int n, int l, int w, bool d){

	Game::set_up(n, l, w);
	this->debug_view = d;

	char input, arrow_input;
	string event_message = "";
	
	while (Game::check_win() == 0){
		printw("%s\n",event_message.c_str());
		Game::display_game();
		Game::move();
		event_message = Game::trigger_event();

	}
	end_game();
	return;

}