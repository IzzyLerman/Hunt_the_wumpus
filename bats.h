#ifndef BATS_H
#define BATS_H 

#include "event.h"

class Bats: public Event
{
public:
	virtual Bats* clone() const;
	virtual string get_percept() const;
	virtual string get_symbol() const;
	virtual string perform_action(Cave& c, int*);

};
#endif