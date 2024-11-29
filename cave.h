#ifndef CAVE_H
#define CAVE_H 

#include "room.h"

class Cave
{
private:
	
	bool wumpus_alive;
	bool player_alive;
	bool wump_death;
	bool has_gold;
	int confused;
	int num_floor;
	int num_y;
	int num_x;
	int start_pos[3];
	int player_pos[3];
	int* num_empty_on_floor;
	vector<vector<vector<Room>>> rooms;

public:

	Cave();
	Cave(int, int, int);
	void set_up_grid(int, int, int);
	void populate();
	void add_event(Event*, int);
	void add_event(Event*);
	void remove_event(int*);
	void wumpus_move();
	Room get_room(int, int, int) const;
	Room get_player_room() const;
	int get_player_floor() const;
	int get_player_y() const;
	int get_player_x() const;
	bool get_wumpus_alive() const;
	bool get_player_alive() const;
	bool get_has_gold() const;
	int get_confused() const;
	bool get_wump_death() const;
	bool check_gold_win() const;
	void set_player_alive(bool);
	void set_wumpus_alive(bool);
	void set_has_gold(bool);
	void set_confused(int);
	void set_wump_death(bool);
	void decr_confused();
	void move_floor(int);
	void add_player();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void set_player_pos(int*);
	void display_percepts() const;
	string trigger_event();
	void set_portal(int*, int*);
	~Cave();


};

#endif

