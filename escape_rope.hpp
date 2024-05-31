#ifndef ESCAPE_ROPE_HPP
#define ESCAPE_ROPE_HPP

#include "event.hpp"
#include "player.hpp"

class escape_rope : public event { 
public:
    /*
 	* Name: encounter
 	* Description: placeholder code for escape rope
	* Parameters:
 	*		p(player&): reference to player object
 	* Returns (bool): true for non-deletion
 	*/
    bool encounter(player& p) override;

    /*
 	* Name: print
 	* Description: prints E for display
	* Post-conditons: character printed to display
 	*/
    void print () const override;

    /*
 	* Name: percept
 	* Description: placeholder code for override
 	* Post-conditions: does nothing
 	*/
    void percept () const override;

    /*
 	* Name: check_proximity
 	* Description: placeholder code for override
    * Parameters:
    *       ev_w(int): event width index
    *       ev_h(int): event height index
    *       p_x(int): player x coord
    *       p_y(int): player y coord
 	* Post-conditions: does nothing
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
    * Returns(escape_rope*) : escape rope pointer 
    */
    escape_rope* copy() const override;
};
#endif
