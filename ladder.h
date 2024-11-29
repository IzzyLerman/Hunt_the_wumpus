#ifndef LADDER_H
#define LADDER_H

#include "event.h"



class Ladder: public Event {
private:
	bool up;
public:
	Ladder(bool);
	Ladder* clone() const;
	//string get_percept() const;
	int get_ladder() const;
	string get_symbol() const;
	string perform_action(Cave&, int*);

};

#endif