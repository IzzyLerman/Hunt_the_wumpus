#include "room.h"

using namespace std;

Room::Room():event(nullptr) , has_player(false){
	for(int i = 0 ; i < 3; i++){
		coordinates[i] = 0;
	}
}

Room::Room(const Room& other_room): has_player(other_room.has_player)
{
    if (other_room.event != nullptr) {
        this->event = other_room.event->clone();
    } else {
        this->event = nullptr;
    }
    for(int i = 0; i < 3; i++){
        this->coordinates[i] = other_room.coordinates[i];
    }
}

void Room::operator=(const Room& other_room){
	if(this->event != nullptr){
		delete event;
	}

	if (other_room.event != nullptr){
		this->event = other_room.event->clone();
	}else{
		this->event = nullptr;
	}

	for(int i = 0; i < 3; i++){
        this->coordinates[i] = other_room.coordinates[i];
    }
    this->has_player = other_room.has_player;
}

void Room::set_coordinates(int n, int y, int x){
	coordinates[0] = n;
	coordinates[1] = y;
	coordinates[2] = x;
}

void Room::set_event(Event* new_event){
	if(event != nullptr){
		delete event;
	}
	event = new_event;
	return;
}

void Room::set_has_player(bool b){
	this->has_player = b;
}

bool Room::get_has_player() const{
	return has_player;
}

int Room::get_ladder() const{
	if(event == nullptr){
		return 0;
	}else{
		return event->get_ladder();
	}
}

string Room::get_symbol() const{
	if(event == nullptr){
		return "   ";
	}else{
		return event->get_symbol();
	}
}

Event* Room::get_event() const{
	return event;
}

string Room::get_percept() const{
	if(event == nullptr){
		return "   ";
	}else{
		return event->get_percept();
	}
}

Room::~Room(){
	if(event != nullptr){
		delete event;
	}
	event = nullptr;
}