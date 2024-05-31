#ifndef EVENT_HPP
#define EVENT_HPP

#include "player.hpp"

// Event interface
class event {
public:
	/*
 	* Name: encounter
 	* Description: virtual function for events that peforms event encounter
	* Parameters:
 	*		p(player&): reference to player object
 	* Returns (bool): true if event needs to be deleted, false if not
 	*/
	virtual bool encounter(player& p) = 0;

	/*
 	* Name: print
 	* Description: prints event symbol for displaying grid
 	* Post-conditions: grid filled with event symbols
 	*/
	virtual void print() const = 0;

	/*
 	* Name: percept
 	* Description: prints event percepts for when player is near
 	* Post-conditions: percepts printed to terminal
 	*/
	virtual void percept() const = 0;

	/*
 	* Name: check_proximity
 	* Description: checks if player is adjacent to event location
	* Parameters:
 	*		ev_w(int): event width index
	* 		ev_h(int): event height index
	* 		p_x(int): player x coordinate
	* 		p_y(int): player y coordinate
 	* Post-conditions: prints percept of event when player is adjacent
 	*/
	virtual void 
	check_proximity(int ev_w, int ev_h, int p_x, int p_y) const = 0;

	/*
 	* Name: hit_by_arrow
 	* Description: 
	* Parameters:
 	*		wump_x(int): x coord of wumpus
	*		wump_y(int): y coord of wumpus
	*		p(player&): reference to player object
	*		direction(char): direction that player is shooting in
 	* Returns (bool): true when wumpus is 3 blocks from players direction, 
	* 		false if otherwise
 	*/
	virtual bool hit_by_arrow(int wump_x, int wump_y, 
	player& p, char direction);

	/*
 	* Name: get_identify
 	* Description: returns an events character for reference to its location
 	* Returns (char): character that is specific to each event 
 	*/
	virtual char get_identify() const = 0;

	/*
 	* Name: ~event
 	* Description: default deconstructor for event class
 	*/
	virtual ~event() = default;

	/*
 	* Name: copy
 	* Description: allows derived classes to return their pointers
 	* Returns (event*): pointer for each specific event
 	*/
	virtual event* copy() const = 0;
};

#endif
