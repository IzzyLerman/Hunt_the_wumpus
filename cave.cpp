#include <iostream>
#include <cstdlib>
#include "cave.h"


using namespace std;

Cave::Cave() :
wumpus_alive(true),player_alive(true),has_gold(false), confused(0),
num_empty_on_floor(nullptr)
{}

Cave::Cave(int n, int y, int x) :
wumpus_alive(true),player_alive(true),has_gold(false), confused(0),
num_floor(n), num_y(y), num_x(x),
num_empty_on_floor(nullptr)
{}

/*********************************************************************
** Function: set_up_grid
** Description: adds rooms to the cave
** Parameters: int; # of floors
**			   int; # of rows
**			   int; # of cols
** Pre-Conditions: 
** Post-Conditions:	rooms are set up
*********************************************************************/ 

void Cave::set_up_grid(int n, int y, int x){
	num_floor = n;
	num_y = y;
	num_x = x;
	this->rooms.resize(num_floor);
	for(int i = 0; i < num_floor; i++){
		this->rooms.at(i).resize(num_y);
		for(int j = 0; j < num_y; j++){
			this->rooms.at(i).at(j).resize(num_x);
			for(int k = 0; k < num_x; k++){
				this->rooms.at(i).at(j).at(k).set_coordinates(i,j,k);
			}
		}
	}
	return;
}

/*********************************************************************
** Function: populate
** Description: adds events and the player to the rooms in the cave
** Parameters: 
** Pre-Conditions: rooms have been created
** Post-Conditions: game board is ready
*********************************************************************/ 

void Cave::populate(){
	if(num_empty_on_floor != nullptr){
		delete[] num_empty_on_floor;
	}
	num_empty_on_floor = new int[num_floor];
	Ladder* up_ladder;
	Ladder* down_ladder;
	Bats* bats;
	Stalactites* stal;
	SecretPassage* sec;
	Wumpus* wump;
	Gold* gold;


	for(int i = 0; i < num_floor; i++){
		num_empty_on_floor[i] = num_x * num_y;
		//add down-ladder to floors above 1
		if(i > 0){
			for(int j = 0; j < num_y; j++){
				for(int k = 0; k < num_x; k++){
					if(rooms.at(i - 1).at(j).at(k).get_ladder() > 0){
						down_ladder = new Ladder(false);
						rooms.at(i).at(j).at(k).set_event(down_ladder);
						num_empty_on_floor[i]--;
					}
				}
			}
		}
		//add up-ladders on floors below the top floor
		if(i <= num_floor - 2){
			up_ladder = new Ladder(true);
			add_event(up_ladder, i);
		}
		for(int j = 0; j < 2; j++){
			bats = new Bats;
			add_event(bats, i);
			stal = new Stalactites; 
			add_event(stal, i);
			sec = new SecretPassage;
			add_event(sec, i);
		}

	}
	wump = new Wumpus;
	add_event(wump);
	gold = new Gold;
	add_event(gold);
	add_player();

}

/*********************************************************************
** Function: add_event
** Description: add an event to a given floor
** Parameters: Event*; pointer to event to be added
** 			   int; floor to be inserted on
** Pre-Conditions: rooms have been populated
** Post-Conditions: event inserted; num_empty_on_floor has been updated
*********************************************************************/ 

void Cave::add_event(Event* new_event, int i){
	int temp_index;
	int temp_count = 0;
	temp_index = rand() % num_empty_on_floor[i];
	for(int j = num_y - 1; j >= 0; j--){
		for(int k = 0; k < num_x; k++){
			if(rooms.at(i).at(j).at(k).get_event() != nullptr){
				continue;
			}else if(temp_index == temp_count){
				rooms.at(i).at(j).at(k).set_event(new_event);
				num_empty_on_floor[i]--;
				return;
			}else{
				temp_count++;
			}
		}
	}
}

/*********************************************************************
** Function: add_event
** Description: add an event to a random floor in the cave
** Parameters: Event*; pointer to event to be added
** Pre-Conditions: rooms have been populated
** Post-Conditions: event inserted; num_empty_on_floor has been updated
*********************************************************************/  

void Cave::add_event(Event* new_event){
	int temp_index;
	int temp_count = 0;
	int num_empty = 0;
	for(int i = 0; i < num_floor; i++){
		num_empty += num_empty_on_floor[i];
	}
	temp_index = rand() % num_empty;
	for(int i = 0; i < num_floor; i++){
		for(int j = 0; j < num_y; j++){
			for(int k = 0; k < num_x; k++){
				if(rooms.at(i).at(j).at(k).get_event() != nullptr
				 || rooms.at(i).at(j).at(k).get_has_player())
				{
					continue;
				}else if(temp_index == temp_count){
					rooms.at(i).at(j).at(k).set_event(new_event);
					num_empty_on_floor[i]--;
					return;
				}else{
					temp_count++;
				}
			}
		}
	}
}

void Cave::remove_event(int* pos){
	rooms.at(pos[0]).at(pos[1]).at(pos[2]).set_event(nullptr);
}

/*********************************************************************
** Function: wumpus_move
** Description: moves the wumpus to a random floor
** Parameters: 
** Pre-Conditions: game board populated
** Post-Conditions: Wumpus has moved
*********************************************************************/ 

void Cave::wumpus_move(){
	int wump_coords[3];
	for(int i = 0; i < num_floor; i++){
		for(int j = 0; j < num_y; j++){
			for(int k = 0; k < num_x; k++){
				if(rooms.at(i).at(j).at(k).get_symbol() == "-.-"){
					wump_coords[0] = i;
					wump_coords[1] = j;
					wump_coords[2] = k;
				}
			}
		}
	}
	int total_num_empty = 0;
	Wumpus* wump = new Wumpus;
	remove_event(wump_coords);
	num_empty_on_floor[wump_coords[0]]++;
	num_empty_on_floor[player_pos[0]]--;
	add_event(wump);
	num_empty_on_floor[player_pos[0]]++;
}

Room Cave::get_room(int n, int y, int x) const{
	return rooms.at(n).at(y).at(x);
}

Room Cave::get_player_room() const{
	return rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]);
}

int Cave::get_player_floor() const{
	return player_pos[0];
}

int Cave::get_player_y() const{
	return player_pos[1];
}

int Cave::get_player_x() const{
	return player_pos[2];
}

bool Cave::get_wumpus_alive() const{
	return wumpus_alive;
}
bool Cave::get_player_alive() const{
	return player_alive;
}

bool Cave::get_has_gold() const{
	return has_gold;
}

int Cave::get_confused() const{
	return confused;
}

bool Cave::get_wump_death() const{
	return wump_death;
}

bool Cave::check_gold_win() const{
	bool at_start = true;
	for(int i = 0; i < 3; i++){
		if(player_pos[i] != start_pos[i]){
			at_start = false;
		}
	}
	return at_start && has_gold;
}

void Cave::set_player_alive(bool b){
	player_alive = b;
}

void Cave::set_wumpus_alive(bool b){
	wumpus_alive = b;
}

void Cave::set_has_gold(bool b){
	has_gold = b;
}


void Cave::set_confused(int n){
	confused = n;
}

void Cave::set_wump_death(bool b){
	wump_death = b;
}

void Cave::decr_confused(){
	confused--;
}

void Cave::move_floor(int n){
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]).set_has_player(false);
	player_pos[0] += n;
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]).set_has_player(true);
}

/*********************************************************************
** Function: add_player
** Description: adds a player to the first floor
** Parameters: 
** Pre-Conditions: cave has rooms
** Post-Conditions: player is in the board
*********************************************************************/ 

void Cave::add_player(){
	int temp_index;
	int temp_count = 0;
	temp_index = rand() % num_empty_on_floor[0];
	for(int j = 0; j < num_y; j++){
		for(int k = 0; k < num_x; k++){
			if(rooms.at(0).at(j).at(k).get_event() != nullptr){
				continue;
			}else if(temp_index == temp_count){
				rooms.at(0).at(j).at(k).set_has_player(true);
				start_pos[0] = 0;
				start_pos[1] = j;
				start_pos[2] = k;
				for(int i = 0; i < 3; i++){
					player_pos[i] = start_pos[i];
				}
				return;
			}else{
				temp_count++;
			}
		}
	}
}

void Cave::move_up(){
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]).set_has_player(false);
	rooms.at(player_pos[0]).at(player_pos[1] + 1).at(player_pos[2]).set_has_player(true);
	player_pos[1] += 1;
}

void Cave::move_down(){
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]).set_has_player(false);
	rooms.at(player_pos[0]).at(player_pos[1] - 1).at(player_pos[2]).set_has_player(true);
	player_pos[1] -= 1;
}

void Cave::move_left(){
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]).set_has_player(false);
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2] - 1).set_has_player(true);
	player_pos[2] -= 1;
}

void Cave::move_right(){
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]).set_has_player(false);
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2] + 1).set_has_player(true);
	player_pos[2] += 1;
}

void Cave::set_player_pos(int* new_pos){
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]).set_has_player(false);
	for(int i = 0; i < 3; i++){
		player_pos[i] = new_pos[i];
	}
	rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2]).set_has_player(true);
}

/*********************************************************************
** Function: display_percepts
** Description:	display percepts for any adjacent room
** Parameters: none
** Pre-Conditions: cave populated
** Post-Conditions: 
*********************************************************************/ 

void Cave::display_percepts() const{
	if(player_pos[1] <= num_y - 2){
		printw(rooms.at(player_pos[0]).at(player_pos[1] + 1).at(player_pos[2]).get_percept().c_str());
	}
	if(player_pos[1] >= 1){
		printw(rooms.at(player_pos[0]).at(player_pos[1] - 1).at(player_pos[2]).get_percept().c_str());
	}
	if(player_pos[2] <= num_x - 2){
		printw(rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2] + 1).get_percept().c_str());
	}
	if(player_pos[2] >= 1){
		printw(rooms.at(player_pos[0]).at(player_pos[1]).at(player_pos[2] - 1).get_percept().c_str());
	}
	printw("\n");
	refresh();
}

string Cave::trigger_event(){
	if (get_player_room().get_event() == nullptr){
		return "";
	}else{
		return get_player_room().get_event()->perform_action(*this, player_pos);
	}
}

/*********************************************************************
** Function: set_portal
** Description: given a secretpassage at pos, update its portal member
** with the pos of its partner secretpassage
** Parameters: int*; portal member of the secretpassage
**			   int*; position of the secretpassage
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/ 

void Cave::set_portal(int* portal_out, int* pos){
	for(int j = 0; j < num_y; j++){
		for(int k = 0; k < num_x; k++){
			if((j != pos[1] || k != pos[2]) &&
			rooms.at(pos[0]).at(j).at(k).get_symbol() == " ? "
			){
				portal_out[0] = j;
				portal_out[1] = k;
			}
		}
	}
}

Cave::~Cave(){
	if(num_empty_on_floor != nullptr){
		delete[] num_empty_on_floor;
	}
	num_empty_on_floor = nullptr;
}