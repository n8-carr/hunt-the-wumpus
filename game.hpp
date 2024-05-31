#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "room.hpp"
#include "player.hpp"
// game interface
class game {
private:
	std::vector<std::vector<room>> grid; // 2D vector of room objects
	int width; // width of the game grid
	int height;	// height of the game grid
	bool debug;	// debug mode or not
	player p; // player object
	int wumpus_x = 0; // wumpus x-coordinate
	int wumpus_y = 0; // wumpus y-coordinate
	int escape_rope_x = 0; // escape_rope x-coordinate
	int escape_rope_y = 0; // escape_rope y-coordinate
	bool wumpus_dead = false; // wumpus dead or not

	// Template class that places events on grid randomly, with a given
	// type of event and quantity of event
	template <typename type>
	/*
	* Function: random_events
	* Description: creates events at random location based on given event and 
	*		and given quantity
	* Parameters:
	* 		count (const int&): amount of events needed to be created
	* Post-condition: new events based on count and type are created
	*/
	void random_events(const int& count);
public:
	/*
	 * Function: Constructor
	 * Description: Constructs game object with a grid matching the given
	 * 		width and height
	 * Parameters:
	 * 		width (int): Width of the grid
	 * 		height (int): Height of the grid
	 * 		debug (bool): Whether or not debug mode should be enabled
	 */
	game(int width, int height, bool debug);

	/*
	 * Function: generate_random_num
	 * Description: Generates a random number betweeen 1 and the given max,
	 * 		inclusive
	 * Parameters:
	 * 		max (int): max number as limit, inclusive
	 * Returns (int): random number between given boundaries
	 */
	int generate_random_num(const int& max);

	/*
	 * Function: populate_grid
	 * Description: Populates grid with random location for player 
	 * 		(matched with escape rope), and all other events
	 * Post-Conditions: 2D vector of rooms filled with event pointers 
	 * 		(or nullptr)
	 */
	void populate_grid();

	/*
	 * Function: set_event_location
	 * Description: Sets given event location at a given row and column index
	 * Parameters:
	 * 		new_event (event*): event pointer for event to be set
	 * 		h (int): height index
	 * 		w (int): width index
	 * Returns (bool): true if event was able to be set,
	 * 		false if event could not be set 
	 * 		(out of boundaries indexes, space occupied by other event, etc.)
	 */
	bool set_event_location(event* new_event, const int& h, const int& w);

	/*
	 * Function: check_percept
	 * Description: uses event functions to check if player is adjacent
	 * Post-Conditions: Displays percept when player is adjacent
	 */
	void check_percept() const;

	/*
	 * Function: delete_event
	 * Description: deletes event from a given row or collumn
	 * Parameters:
	 * 		row (const int&): row index
	 * 		column (const int&): column index
	 * Post-Conditions: grid spot at row and column location is set to nullptr
	 */
	void delete_event(const int& row, const int& column);

	/*
	 * Function: perform_encounter
	 * Description: Runs event encounters when players go on event
	 * 		Also deletes event (for bats, armor, gold, and flashlight), 
	 * 		or resets players location and belongings
	 * Parameters:
	 * 		p (player&): 
	 * Post-Conditions: Event encounter is ran
	 */
	void perform_encounter(player& p);

	/*
	 * Function: confused_display
	 * Description: asks player for direction, then supplying a randomized 
	 * 		direction
	 * Parameters:
	 * 		y (const int&): index of players y coord on grid
	 * 		x (const int&): index of players x coord on grid
	 * Post-Conditions: runs bat encounter
	 */
	void confused_display(const int& y, const int& x);

	/*
	 * Function: scatter_events
	 * Description: moves wumpus and scatters new events based on
	 * 		players belongings at time of death
	 * Parameters:
	 * 		p (player&): player reference
	 * 		num_arrows (const int&): players number of arrows
	 * 		has_gold (const bool&): whether player has gold or not
	 * 		flash (const bool&): whether player has flashlight or not
	 * Post-Conditions: Wumpus is moved to new location, and new events created
	 */
	void scatter_events(player& p, const int& num_arrows, 
	const bool& has_gold, const bool& flash);

	/*
	 * Function: restart
	 * Description: Sets players belongings to original state, and
	 *		sets player to escape rope location
	 * Parameters:
	 * 		p (player&): reference to player object 
	 * Post-Conditions: Player at original location and new events created
	 */
	void restart(player& p);
	
	/*
	 * Function: set_wumpus_location
	 * Description: Sets wumpus coords based on its location
	 * Post-Conditions: x and y coords of wumpus set
	 */
	void set_wumpus_location();

	/*
	 * Function: move_wumpus
	 * Description: deletes current wumpus and creates new wumpus at random
	 * 		location
	 * Post-Conditions: New wumpus at random location created
	 */
	void move_wumpus();

	/*
	 * Function: set_escape_location
	 * Description: sets x and y coords of escape rope
	 * Post-Conditions: x and y coords of escape rope set
	 */
	void set_escape_location();

	/*
	 * Function: display_game
	 * Description: Displays the game grid in the terminal
	 */
	void display_game() const;

	/*
	 * Function: check_win
	 * Description: Determines whether the player has won the game
	 * Returns (bool): True if the player has won, false otherwise
	 */
	bool check_win() const;

	/*
	 * Function: check_lose
	 * Description: Determines whether the player has lost the game
	 * Returns (bool): True if the player has lost, false otherwise
	 */
	bool check_lose() const;

	/*
	 * Function: is_direction
	 * Description: Returns true if the given character is a valid direction
	 * 		character (w/a/s/d) and false otherwise
	 * Parameters:
	 * 		c (char): The character to check
	 * Returns (bool): Boolean indicating whether the character is a valid
	 * 		direction character (w/a/s/d)
	 */
	bool is_direction(char c);

	/*
	 * Function: to_lower
	 * Description: Converts a given character to lowercase. Used to standardize
	 * 		a user's character input.
	 * Parameters:
	 * 		direction (char): Character to convert to lowercase
	 * Returns (char): Character converted to lowercase
	 */
	char to_lower(char direction);

	/*
	 * Function: can_move_in_direction
	 * Description: Determines whether the player can move in the given
	 * 		direction, based on their current location and the size of the
	 * 		grid.
	 * Parameters:
	 * 		direction (char): Direction the player wishes to move in
	 * Returns (bool): True if the player can move in the given direction
	 * 		without moving off the grid. False otherwise.
	 */
	bool can_move_in_direction(char direction);

	/*
	 * Function: is_valid_action
	 * Description: Determines whether the given action is valid.
	 * Parameters:
	 * 		action (char): Action the player wishes to perform.
	 * Returns (bool): True if the requested action is valid. False otherwise.
	 */
	bool is_valid_action(char action);

	/*
	 * Function: print_action_error
	 * Description: Prints a clear error message associated with the user's
	 * 		provided invalid action
	 * Parameters:
	 * 		action (char): Invalid action that the user requested
	 */
	void print_action_error(char action);

	/*
	 * Function: get_player_action
	 * Description: Prompts the player for their action for the turn and
	 * 		returns it as a char (w, a, s, d, or f). If the player enters
	 * 		an invalid action, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid action provided by the player.
	 */
	char get_player_action();

	/*
	 * Function: get_arrow_fire_direction
	 * Description: Prompts the player for the direction they want to fire an
	 * 		arrow (w, a, s, or d) and returns it as a char. If the player enters
	 * 		an invalid direction, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid direction provided by the player.
	 */
	char get_arrow_fire_direction();

	/*
	 * Function: move
	 * Description: Moves the player in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to move the player (a for
	 * 			west, s for south, d for east, w for north).
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move(char direction);

	/*
	 * Function: fire_arrow
	 * Description: Fires an arrow in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to fire arrow (a for
	 * 			west, s for south, d for east, w for north).
	 * Post-condition: Arrow is fired. Wumpus is killed if hit and moves if
	 * 		missed.
	 */
	void fire_arrow(char direction);

	/*
	 * Function: play_game
	 * Description: Runs one full iteration of the game
	 */
	void play_game();

	/*
	 * Function: ~game
	 * Description: game destructor
	 * Post-Conditions: 2d vector deleted
	 */
	~game();
	
};

template<typename type> // Type of event to be created
void game::random_events(const int& count) {
	for (int i = 0; i < count;){
		// Creates random number for height and width index
		int row = generate_random_num(height);
		int column = generate_random_num(width);
		type* new_event = new type(); // Temporary pointer for new event
		// Runs until event could be set
		if (set_event_location(new_event, row, column)) {
			i++;
		} else if (!set_event_location(new_event, row, column)){
			delete new_event; // Pointer deleted when event could not be set
		}
	}
}
#endif
