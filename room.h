#ifndef ROOM_H
#define ROOM_H 

#include <vector>
#include <string>
#include <iostream>
#include "event.h"
#include "ladder.h"
#include "bats.h"
#include "stalactites.h"
#include "secretpassage.h"
#include "wumpus.h"
#include "gold.h"

using namespace std;

//Room Interface
//Note: Each room may be empty or has an event (bat, gold, pit, or wumpus);
//		Use event polymorphically

class Room
{
private: 
	Event* event;
	int coordinates[3];
	bool has_player;

	
public:
	Room();
	Room(const Room&);
	void operator=(const Room&);
	void set_coordinates(int, int, int);
	void set_event(Event*);
	void set_has_player(bool);
	bool get_has_player() const;
	int get_ladder() const;
	string get_symbol() const;
	Event* get_event() const;
	string get_percept() const;
	~Room();





};

#endif