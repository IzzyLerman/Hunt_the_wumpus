#include "wumpus.h"
#include "cave.h"

#include <iostream>
#include "cave.h"

using namespace std;

Wumpus* Wumpus::clone() const{
	return new Wumpus(*this);
}
string Wumpus::get_percept() const{
	return "You smell a terrible stench.\n";
}
string Wumpus::get_symbol() const{
	return "-.-";
}
string Wumpus::perform_action(Cave& c, int* pos){
	c.set_player_alive(false);
	c.set_wump_death(true);
	c.remove_event(pos);
	return "The wumpus ate you alive.\n";
}