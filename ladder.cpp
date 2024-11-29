#include "ladder.h"
#include "cave.h"

Ladder::Ladder(bool up):up(up){}

Ladder* Ladder::clone() const{
	return new Ladder(*this);
}

/*string Ladder::get_percept() const{
	return "";
}*/

int Ladder::get_ladder() const{
	if(up){
		return 1;
	}else{
		return -1;
	}
}

string Ladder::get_symbol() const{
	if(up){
		return " ^ ";
	}else{
		return " v ";
	}
}

string Ladder::perform_action(Cave& c, int* coordinates){
	if(up){
		c.move_floor(1);
	}else{
		c.move_floor(-1);
	}
	return "";
}