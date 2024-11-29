#include "gold.h"
#include "cave.h"

#include <iostream>

using namespace std;

Gold* Gold::clone() const{
	return new Gold(*this);
}
string Gold::get_percept() const{
	return "You see a glimmer nearby.\n";
}
string Gold::get_symbol() const{
	return " $ ";
}
string Gold::perform_action(Cave& c, int* pos){
	c.set_has_gold(true);
	c.remove_event(pos);
	return "You grabbed the Gold! Return to cave entrance to win the game.";
}

