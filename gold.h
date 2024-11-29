#ifndef GOLD_H
#define GOLD_H 

#include "event.h"

class Gold: public Event
{
private:
	int room_coordinates[3];
public:
	virtual Gold* clone() const;
	virtual string get_percept() const;
	virtual string get_symbol() const;
	virtual string perform_action(Cave& c, int*);

};

#endif