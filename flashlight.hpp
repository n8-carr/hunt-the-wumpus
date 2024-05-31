#ifndef FLASHLIGHT_HPP
#define FLASHLIGHT_HPP

#include "event.hpp"
#include "player.hpp"

class flashlight : public event { 
public:
    /*
 	* Name: encounter
 	* Description: sets players flash bool to true and sets result for display
	* Parameters:
 	*		p(player&): reference to player object
 	* Returns (bool): false for deletion
 	*/
    bool encounter(player& p) override;

    /*
 	* Name: print
 	* Description: prints P for display
	* Post-conditons: character printed to display
 	*/
    void print () const override;

    /*
 	* Name: percept
 	* Description: displays event percept for display
 	* Post-conditions: percept printed to terminal
 	*/
    void percept () const override;

    /*
 	* Name: check_proximity
 	* Description: checks if players location is adjacent to event
    * Parameters:
    *       ev_w(int): event width index
    *       ev_h(int): event height index
    *       p_x(int): player x coord
    *       p_y(int): player y coord
 	* Post-conditions: prints percept when player near
 	*/
    void check_proximity (int ev_w, int ev_h, int p_x, int p_y) const override;

    /*
 	* Name: get_identify
 	* Description: returns player character for reference to its location
 	* Returns (char): event character
 	*/
    char get_identify() const override;

    /*
    * Name: copy
    * Description: returns pointer to this specific event 
    * Returns(flashlight*) : flashlight pointer 
    */
    flashlight* copy() const override;
};

#endif
