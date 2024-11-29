#ifndef EVENT_H
#define EVENT_H 

#include <string>
#include <iostream>
#include <ncurses.h>

using namespace std;

class Cave;

class Event
{
public:

	virtual Event* clone() const = 0;
	virtual string get_percept() const;
	virtual int get_ladder() const;
	virtual string get_symbol()const = 0;
	virtual string perform_action(Cave&, int*) = 0;
	virtual ~Event();

};
#endif