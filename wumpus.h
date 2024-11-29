#ifndef WUMPUS_H
#define WUMPUS_H 

#include "event.h"

class Wumpus: public Event
{
public:
	virtual Wumpus* clone() const;
	virtual string get_percept() const;
	virtual string get_symbol() const;
	virtual string perform_action(Cave&, int*);

};

#endif