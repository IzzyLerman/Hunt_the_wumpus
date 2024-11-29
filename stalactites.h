#ifndef STALACTITES_H
#define STALACTITES_H 

#include "event.h"

class Stalactites: public Event
{
public:
	virtual Stalactites* clone() const;
	virtual string get_percept() const;
	virtual string get_symbol() const;
	virtual string perform_action(Cave&, int*);

};

#endif
