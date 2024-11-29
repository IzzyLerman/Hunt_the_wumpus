#include "stalactites.h"
#include "cave.h"

#include <iostream>
#include <cstdlib>

using namespace std;

Stalactites* Stalactites::clone() const{
	return new Stalactites(*this);
}
string Stalactites::get_percept() const{
	return "You hear water dripping.\n";
}
string Stalactites::get_symbol() const{
	return " S ";
}
string Stalactites::perform_action(Cave& c, int* pos){
	
if (rand() % 2 == 0){
	c.set_player_alive(false);
	c.set_wump_death(false);
	c.remove_event(pos);
	return "The stalactite fell on your head and killed you.\n";
}else{
	c.remove_event(pos);
	return "BANG!!! A stalactite came crashing down near you.\n";
	}
}
