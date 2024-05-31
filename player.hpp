#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class player {
private:
    int lives = 3; // Number of lives player has
    int armor_health = 0; // Armor health at start
    int x = 1; // x coord of player
    int y = 1; // y coord of player
    int num_arrows = 0; // Number of arrows player has
    bool gold = false; // If player has gold or not
    bool flashlight = false; // If player has a flashlight or not
    int game_w = 0; // Gameboard width
    int game_h = 0;	// Gameboard height
    std::string result; // String to save percept result

public: 
    /*
 	* Name: player
 	* Description: non-default constructor that sets players 
    *       coordinates and also game board size for event reference
	* Parameters:
 	*		x(int): x coord of player
    *       y(int): y coord of player
    *       game_w(int): width of game board
    *       game_h(int): height of game board
    * Post-conditions: player object constructed
 	*/
    player(int x, int y, int game_w, int game_h);

    /*
 	* Name: get_num_lives
 	* Description: getter for player number of lives
 	* Returns (int): current number of lives player has
 	*/
    int get_num_lives() const;

    /*
 	* Name: get_armor_health
 	* Description: getter for players armor health
 	* Returns (int): current health of players armor
 	*/
    int get_armor_health() const;

    /*
 	* Name: set_armor_health
 	* Description: sets armor health to provided health
	* Parameters:
 	*		new_health(const int&): new health int to be copied
    * Post-conditions: armor health updated
 	*/
    void set_armor_health(const int& new_health);

    /*
 	* Name: take_damage
 	* Description: takes away one of the players lives
    * Post-conditions: player has one less life
 	*/
    void take_damage();

    /*
 	* Name: get_num_arrows
 	* Description: getter for number of arrows player has
 	* Returns (int): number of arrows player has
    * Post-conditions: 
 	*/
    int get_num_arrows() const;

    /*
 	* Name: set_num_arrows
 	* Description: setter for number of arrows player has
	* Parameters:
 	*		new_num(const int&): new number that will be copied
    * Post-conditions: num arrows updated
 	*/
    void set_num_arrows(const int& new_num);

    /*
 	* Name: has_gold
 	* Description: bool that checks if player has gold
 	* Returns (bool): true when player has gold, false when they dont 
 	*/
    bool has_gold() const;

    /*
 	* Name: set_gold
 	* Description: setter for bool has gold
	* Parameters:
 	*		new_gold(const bool&): updated bool value to be copied
    * Post-conditions: has_gold is updated
 	*/
    void set_gold(const bool& new_gold);

    /*
 	* Name: has_flash
 	* Description: bool that checks if player has a flashlight
 	* Returns (bool): true when player has flashlight, false when they don't
 	*/
    bool has_flash() const;

    /*
 	* Name: set_flash
 	* Description: setter for bool has_flash 
	* Parameters:
 	*		new_flash(const bool&): updated bool value to be copied
    * Post-conditions: has_flash is updated
 	*/
    void set_flash(const bool& new_flash);
    
    /*
 	* Name: get_x
 	* Description: getter for players x coordinate
 	* Returns (int): x coordinate of player
 	*/
    int get_x() const;

    /*
 	* Name: get_y
 	* Description: getter for players y coordinate
 	* Returns (int): y coordinate of player
 	*/
    int get_y() const;

    /*
 	* Name: set_location
 	* Description: sets players x and y coordinates to new coordinates
	* Parameters:
 	*		x_cord(const int&): new x coord
    *       y_cord(const int&): new y coord
    * Post-conditions: x and y coordinates of player updated
 	*/
    void set_location(const int& x_cord, const int& y_cord);

    /*
 	* Name: get_game_w
 	* Description: getter for games width
 	* Returns (int): game width
 	*/
    int get_game_w() const;

    /*
 	* Name: get_game_h
 	* Description: getter for games height
 	* Returns (int): game height
 	*/
    int get_game_h() const;

    /*
 	* Name: move_up
 	* Description: moves player up one space on the y plane
    * Post-conditions: player is one space up 
 	*/
    void move_up();

    /*
 	* Name: move_down
 	* Description: moves player down one space on the y plane
    * Post-conditions: player is one space down
 	*/
    void move_down();

    /*
 	* Name: move_left
 	* Description: moves player left one space on the x plane
    * Post-conditions: player is one space to the left
 	*/
    void move_left();

    /*
 	* Name: move_right
 	* Description: moves player right one space on the x plane
    * Post-conditions: player is one space to the right
 	*/
    void move_right();

    /*
 	* Name: get_result
 	* Description: gets the result of the player after an encounter
 	* Returns (std::string): result of encounter
 	*/
    std::string get_result() const;

    /*
 	* Name: set_result
 	* Description: sets the result of the player after an encounter
	* Parameters:
 	*		new_string(const std::string&): string that event supplies
    * Post-conditions: result variable updated
 	*/
    void set_result(const std::string& new_string);

    


};

#endif