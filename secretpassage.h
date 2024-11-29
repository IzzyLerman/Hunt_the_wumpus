#ifndef SECRETPASSAGE_H
#define SECRETPASSAGE_H

#include "event.h"

class SecretPassage: public Event
{
protected:
	int portal_out[2];
public:
	SecretPassage();
	virtual SecretPassage* clone() const;
	virtual string get_percept() const;
	virtual string get_symbol() const;
	virtual string perform_action(Cave&, int*);
	void set_portal(Cave&, int*);

};

#endif