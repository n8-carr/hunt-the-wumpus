#include "bats.hpp"
#include "game.hpp"
#include <iostream>
#include <string>

bool bats::encounter(player& p) {
    bool moved = false; // Re-run bool
    // Sets result for display
    p.set_result("The bats have confused your sense of direction!");
    while (moved == false) {
        // Generates random number 1-4 inclusive
        int random = ((rand() % 4) + 1); 
        // Moves player up and ends loop when player is not at the top of grid
        // and random equals 1
        if (random == 1 && p.get_y()!= 1) {
            p.move_up();
            moved = true;
        // Moves player left and ends loop when player is not at the left of 
        // grid and random equals 2
        } else if (random == 2 && p.get_x()!= 1) {
            p.move_left();
            moved = true;
        // Moves player down and ends loop when player is not at the bottom 
        // of grid and random equals 3
        } else if (random == 3 && p.get_y() != p.get_game_h()) {
            p.move_down();
            moved = true;
        // Moves player right and ends loop when player is not at the right 
        // of grid and random equals 4
        } else if (random == 4 && p.get_x() != p.get_game_w()) {
            p.move_right();
            moved = true;
        }
    }
    return true;
}

void bats::print() const {
    std::cout << "B"; // Prints B on grid
}

void bats::percept() const {
    std::cout << "You hear wings flapping" << std::endl; // Prints percept
}

void bats::check_proximity(int ev_w, int ev_h, int p_x, int p_y) const {
    // Runs when event:
    //1. is in the same column and one row off
    //2. is in the same row and one column off
    if (ev_w == p_x && (ev_h == p_y - 1 || ev_h == p_y + 1) ||
    (ev_h == p_y && (ev_w == p_x - 1 || ev_w == p_x + 1))) {
        this->percept(); // Prints percept
    }
}

char bats::get_identify() const {
    return 'B'; // Returns B
}

bats* bats::copy() const {
    return new bats(*this); // Returns pointer to this bat event
}