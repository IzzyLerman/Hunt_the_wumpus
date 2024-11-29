#include "bats.h"
#include "cave.h"

#include <iostream>

using namespace std;

Bats* Bats::clone() const{
	return new Bats(*this);
}
string Bats::get_percept() const{
	return "You hear wings flapping.\n";
}
string Bats::get_symbol() const{
	return "\\M/";
}
string Bats::perform_action(Cave& c, int* pos){
	c.set_confused(5);
	c.remove_event(pos);
	return "Super Bats swoop from the ceiling and spray you with venom!";
}

