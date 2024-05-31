#ifndef WUMPUS_HPP
#define WUMPUS_HPP

#include "event.hpp"
#include "player.hpp"

class wumpus : public event { 
public:
   /*
 	* Name: encounter
 	* Description: deals damage to players armor or health, and sets   
   *       result for dispaly
	* Parameters:
 	*		p(player&): reference to player object
 	* Returns (bool): true for non-deletion
 	*/
   bool encounter(player& p) override;

   /*
 	* Name: print
 	* Description: prints W for display
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
 	* Name: hit_by_arrow
 	* Description: checks if wumpus was 3 blocks away from players shooting
   *       direction
   * Parameters:
   *       wump_x(int): wumpus x coord
   *       wump_y(int): wumpus y coord
   *       p(player&): reference to player object
   *       direction(char): character player intends to shoot arrow in
 	* Returns bool: true if wumpus was withint 3 block radius, false if not
 	*/
   bool hit_by_arrow(int wump_x, int wump_y, 
   player& p, char direction) override;

   /*
 	* Name: get_identify
 	* Description: returns player character for reference to its location
 	* Returns (char): event character
 	*/
   char get_identify() const override;

   /*
   * Name: copy
   * Description: returns pointer to this specific event 
   * Returns(wumpus*) : wumpus pointer 
   */
   wumpus* copy() const override;
};
#endif
