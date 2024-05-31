#ifndef ROOM_HPP
#define ROOM_HPP

#include "event.hpp"

// Room interface
class room {
private: 
	event* current_event = nullptr; // Polymorphic handle for event 
public:
	/*
	* Function: room
	* Description: default constructor for room object
	*/
	room();

	/*
	* Function: set_event
	* Description: sets room event pointer to a given event pointer
	* Parameters:
	* 		new_event (event*): event pointer for new event 
	* Post-conditions: event pointer is set
	*/
	void set_event(event* new_event);

	/*
	* Function: get_event
	* Description: returns event pointer of room
	* Returns (event*): event pointer of room
	*/
	event* get_event() const;

	/*
	* Function: ~room
	* Description: deletes current event and sets it to nullptr
	*/
	~room();

	/*
	* Function: room
	* Description: copy constructor for room object
	* Parameters:
	* 		copy (const room&): reference to room that will be copied to
	* Post-conditions: deep copy is peformed of room
	*/
	room(const room& copy);

	/*
 	* Name: operator=
 	* Description: assignment operator overload for room class 
	* Parameters:
 	*		copy(const room&): constant reference to given room class
 	* Post-conditions: assignment operator defined for deep copies
 	*/
	room& operator=(const room& copy);
};

#endif
