#include "secretpassage.h"
#include "cave.h"

using namespace std;

SecretPassage::SecretPassage(){
	portal_out[0] = -1;
	portal_out[1] = -1;
}

SecretPassage* SecretPassage::clone() const{
	return new SecretPassage(*this);
}
string SecretPassage::get_percept() const{
	return "You feel a breeze.\n";
}
string SecretPassage::get_symbol() const{
	return " ? ";
}
string SecretPassage::perform_action(Cave& c, int* pos){
	if(portal_out[0] == -1){
		set_portal(c, pos);
	}
	int new_pos[3] = {pos[0],portal_out[0],portal_out[1]};
	c.set_player_pos(new_pos);
	return "...What just happened?";
}

void SecretPassage::set_portal(Cave& c, int* pos){
  c.set_portal(portal_out, pos);
}


