#include <iostream>
#include "game.hpp"
#include "gold.hpp"
#include "bats.hpp"
#include "stalactites.hpp"
#include "wumpus.hpp"
#include "escape_rope.hpp"
#include "arrow.hpp"
#include "flashlight.hpp"
#include "armor.hpp"

// Game implementation

// Non-default constructor for game
game::game(int width, int height, bool debug) :
    width(width),
    height(height),
    debug(debug),
    grid(height, std::vector<room>(width)), // Constructs grid
	p(1, 1, width, height) { // Constructs player object
    populate_grid(); // Populates grid with random events
	set_wumpus_location(); // Sets x and y coords of wumpus
	set_escape_location(); // Sets x and y coords of escape_location
}

void game::populate_grid() {
	// Creates random coordinates for player, and places player at location
	int c = generate_random_num(width);
	int r = generate_random_num(height);
	p.set_location(c,r);

	// Creates escape_rope at players start location
	grid[r-1][c-1].set_event(new escape_rope());
	
	// Sets each event at a random location
	random_events<bats>(2);
	random_events<stalactites>(2);
	random_events<wumpus>(1);
	random_events<gold>(1);
	random_events<arrow>(2);
	random_events<flashlight>(1);
	random_events<armor>(1);
}

bool game::set_event_location(event* new_event, const int& h, const int& w) {
	// Checks if randomized height and width are within grid boundaries
	if (h > 0 && h <= height && w > 0 && w <= width) {
		// Checks if the grid spot is empty and not where player is at
		if (grid[h-1][w-1].get_event() == nullptr 
		&& !(h-1 == p.get_y() && w-1 == p.get_x())) {
			// Sets event location at given spot
			grid[h-1][w-1].set_event(new_event);
			return true;
		}
	}
	// Returns false if event could not be set
	return false;
}

int game::generate_random_num(const int& max) {
	// Generates a random number between 1 and the max value, inclusive
	return (1 + (rand() % max));
}

void game::set_wumpus_location() {
	// Itterates over every grid spot until wumpus is found
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			if (grid[i][j].get_event() != nullptr) {
				if (grid[i][j].get_event()->get_identify() == 'W') {
					// Sets wumpus coordinates for future reference
					this->wumpus_x = j+1;
					this->wumpus_y = i+1;
					return;
				}
			}
		}
	}
}

void game::move_wumpus() {
	// Deletes current wumpus and creates new wumpus at randomized location
	delete_event(wumpus_y - 1, wumpus_x-1);
	random_events<wumpus>(1);
	set_wumpus_location();
}

void game::display_game() const{
	std::cout << std::endl << std::endl;
	// Displays player information
	std::cout << "Lives remaining: " << p.get_num_lives() << std::endl;
	std::cout << "Arrows remaining: " << p.get_num_arrows() << std::endl;
	std::cout << "Armor health: " << p.get_armor_health() << std::endl;

	std::string row_border = "--";
	for (int i = 0; i < this->width; ++i) {
		row_border += "-----";
	}
	std::cout << row_border << std::endl;

	// Column and row variables where player is at for reference
	int column = p.get_x() - 1;
	int row = p.get_y() - 1;

	// Iterates over every grid square
	for (int i = 0; i < this->height; i++) {
		std::cout << "|";
		for (int j = 0; j < this->width; j++) {
			// If room contains player print asterix, else print space
			if (i == (p.get_y() - 1) && j == (p.get_x() - 1)) {
				std::cout << "*";
			} else {
				std::cout << " ";
			}

			// Runs when a given space is occupied by an event
			if (grid[i][j].get_event() != nullptr) {
				// If debug mode is set, print event 
				if (this->debug) {
					grid[i][j].get_event()->print();
				// If player has flashlight, print events in column and row
				// of player
				} else if (p.has_flash() == true) {
					if (i == row || j == column) {
						grid[i][j].get_event()->print();
					// Print space if event is not in column or row
					} else {
						std::cout << " ";
					}
				// Print space on event square if debug mode is not set 
				} else {
					std::cout << " ";
				}
			// Print space if event is not occupied by an event
			} else {
				std::cout << " ";
			}
			std::cout << " |";
		}
		std::cout << std::endl;
		std::cout << row_border << std::endl;
	}
}

void game::check_percept() const {
	// Itterates over every square and checks if player is near
	for (int h = 0; h < this->height; h++) {
		for (int w = 0; w < this->width; w++) {
			// Prints event percept when adjacent to player
			if (grid[h][w].get_event() != nullptr) {
				grid[h][w].get_event()->
				check_proximity(w + 1, h + 1, p.get_x(), p.get_y());
			}
		}
	}
}

void game::delete_event(const int& row, const int& column) {
	// Checks that grid spot is occupied
	if (grid[row][column].get_event() != nullptr) {
		// Sets event to nullptr and deletes event
		grid[row][column].set_event(nullptr);
		delete grid[row][column].get_event();
	}
}

void game::perform_encounter(player& p) {
	// Player variables for future reference
	int x = p.get_x() - 1;
	int y = p.get_y() - 1;
	int current_lives = p.get_num_lives();
	int current_armor = p.get_armor_health();
	// Runs when grid spot is occupied by an event
	if (grid[y][x].get_event() != nullptr) {
		// Identification variable for event
		char id = grid[y][x].get_event()->get_identify();
		// Deletes event if encounter returns false, 
		// and given event is not bats
		if (id != 'B' && grid[y][x].get_event()->encounter(p) == false) {
			delete_event(y, x);
		// Displays game when bats confuses player
		} else if (id == 'B'){
			confused_display(y, x);
		// Drops players items when they take damage, and restarts player to 
		// beginning spot
		} else if (current_lives > p.get_num_lives() ||
		current_armor > p.get_armor_health()) {
			scatter_events(p, p.get_num_arrows(), p.has_gold(), p.has_flash());
			restart(p);
		}
	}
}

void game::confused_display(const int& y, const int& x) {
	// Asks player for direction, but runs a randomized direction
	// given by bats encounter function
	display_game();
	check_percept();
	get_player_action();
	grid[y][x].get_event()->encounter(p);
}

void game::scatter_events(player& p, const int& num_arrows, 
const bool& has_gold, const bool& flash) {
	// Moves wumpus to new location
	move_wumpus();
	// Creates new arrows, gold, and flashlight objects
	// depending on how much were aquired at time of death
	if (num_arrows == 2) {
		random_events<arrow>(2);
	} else if (num_arrows == 1) {
		random_events<arrow>(1);
	}
	if (has_gold == true) {
		random_events<gold>(1);
	}
	if (flash == true) {
		random_events<flashlight>(1);
	}
}

void game::restart(player& p) {
	// Sets players belongings to original state, and
	// sets player to escape rope location
	p.set_num_arrows(0);
    p.set_gold(false);
    p.set_flash(false);
	p.set_location(escape_rope_x, escape_rope_y);	
}

void game::set_escape_location() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			if (grid[i][j].get_event() != nullptr) {
				if (grid[i][j].get_event()->get_identify() == 'E') {
					// Sets escape rope coordinates for future reference
					this->escape_rope_x = j+1;
					this->escape_rope_y = i+1;
					return;
				}
			}
		}
	}
}

bool game::check_win() const{
	// Returns true when either:
	// 1. Player has gold and returns to escape rope
	// 2. Player hits wumpus with arrow
	if ((p.has_gold() == true && 
	(escape_rope_x == p.get_x() && escape_rope_y == p.get_y())) 
	|| wumpus_dead == true) {
		std::cout << "You won!" << std::endl;
		return true;
	}
	return false;
}

bool game::check_lose() const{
	// Returns true when player runs out of lives
	if (p.get_num_lives() <= 0) {
		std::cout << "Game over!" << std::endl;
		return true;
	}
	return false;
}

bool game::is_direction(char c) {
	// Returns true when direction is valid
	return c == 'w' ||
	c == 'a' ||
	c == 's' ||
	c == 'd';
}

char game::to_lower(char direction) {
	// Function that changes uppercase to lowercase
	if (direction >= 'A' && direction <= 'Z') {
		return direction + ('a' - 'A');
	}
	return direction;
}

bool game::can_move_in_direction(char direction) {
	// Makes sure that movement is within boundaries of game board
	if (direction == 'w' && p.get_y() != 1) {
		return true;
	} else if (direction == 'a' && p.get_x() != 1) {
		return true;
	} else if (direction == 's' && p.get_y() != height) {
		return true;
	} else if (direction == 'd' && p.get_x() != width) {
		return true;
	}
	return false;
}

bool game::is_valid_action(char action) {
	// Checks that given action, wasd, or f(shoot) is valid
	if (this->is_direction(action)) {
		char direction = action;
		return this->can_move_in_direction(direction);
	} else if (action == 'f') {
		return p.get_num_arrows() > 0;
	}
	return false;
}

void game::print_action_error(char action) {
	// Error messages for movement out of boundaries, or for invalid inputs
	if (this->is_direction(action)) {
		std::cout << "You can't move in that direction!" << std::endl <<
		std::endl;
	} else if (action == 'f') {
		std::cout << "You're out of arrows!" << std::endl << std::endl;
	} else {
		std::cout << std::endl << "That's an invalid input!" << std::endl
		<< std::endl;
	}
}

char game::get_player_action() {
	// Asks user for action and runs until valid option is given
	char action;
	bool first = true;
	do {
		if (!first) {
			char previous_action = action;
			this->print_action_error(previous_action);
		}
		first = false;

		std::cout << std::endl << std::endl << "What would you like to do?" <<
		std::endl << std::endl;
		std::cout << "w: move up" << std::endl;
		std::cout << "a: move left" << std::endl;
		std::cout << "s: move down" << std::endl;
		std::cout << "d: move right" << std::endl;
		std::cout << "f: fire an arrow" << std::endl;

		std::cin >> action;
		action = this->to_lower(action);
	} while (!this->is_valid_action(action));

	return action;
}

char game::get_arrow_fire_direction() {
	// Asks user for arrow fire direction and runs until valid option is
	// given
	char direction;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "That's an invalid input!" <<
			std::endl << std::endl;
		}
		first = false;

		std::cout << std::endl << std::endl <<
		"What direction would you like to fire the arrow?" << std::endl <<
		std::endl;
		std::cout << "w: up" << std::endl;
		std::cout << "a: left" << std::endl;
		std::cout << "s: down" << std::endl;
		std::cout << "d: right" << std::endl;

		std::cin >> direction;
		direction = this->to_lower(direction);
	} while (!this->is_direction(direction));

	return direction;
}

void game::move(char direction) {
	// Depending on direction, it calls on player functions to move on grid
	if (direction == 'w') {
		p.move_up();
	} else if (direction == 'a') {
		p.move_left();
	} else if (direction == 's') {
		p.move_down();
	} else {
		p.move_right();
	}
}

void game::fire_arrow(char direction) {
	event* arrows = new arrow(); // Event pointer for new arrow object
	int y = p.get_y(); // X and y variables, 
	int x = p.get_x(); // for future reference
	// Depending on direction, if statements will move arrow coordinates
	// 3 spaces in intended direction, up, down, left, or right
	if (direction == 'w') {
		y -= 3;
	} else if (direction == 'a') {
		x -=3;
	} else if (direction == 's') {
		y += 3;
	} else if (direction == 'd') {
		x += 3;
	}
	// Attempts to set arrow at new location based on direction
	// If the function returns false (meaning the location was out of bounds,
	// was occupied by another event, etc.), then a random arrow is created
	if (!(set_event_location(arrows, y, x))) {
		delete arrows;
		random_events<arrow>(1);
	}
	p.set_num_arrows(p.get_num_arrows() - 1); // Removes 1 arrow from player
	// Sets wumpus dead bool based off hit_by_arrow boolean, which
	// checks if wumpus was in arrows path of travel
	wumpus_dead = grid[wumpus_y-1][wumpus_x-1].get_event()->
	hit_by_arrow(wumpus_x, wumpus_y, p, direction);
	// If wumpus was not hit by arrow, wumpus moves
	if (!wumpus_dead) {
		move_wumpus();
	}
}

void game::play_game(){
	while (!this->check_win() && !this->check_lose()) {
		// Print game board
		this->display_game();
		// Displays surrounding percepts
		this->check_percept();
		// Displays results from encounters when avaliable
		if (p.get_result() != "") {
			std::cout << "+++ " << p.get_result() << " +++" << std::endl;
		}
		p.set_result(""); // Resets results for next loop
		
		// Ask player for their action
		char action = get_player_action();

		// Process action
		if (this->is_direction(action)) {
			// W/A/S/D = move player
			char direction = action;
			this->move(direction);
		} else {
			// F = prompt for arrow fire direction and fire arrow
			char direction = this->get_arrow_fire_direction();
			this->fire_arrow(direction);
		}

		// If the user is on a space with an event, trigger its encounter
		int current_lives = p.get_num_lives();
		for (int h = 0; h < this->height; h++) {
			for (int w = 0; w < this->width; w++) {
				if (grid[h][w].get_event() != nullptr 
				&& (h == (p.get_y() - 1) && (w == p.get_x() - 1))) {
					perform_encounter(p);
				}
			}
		}
	}
}

game::~game() {}

