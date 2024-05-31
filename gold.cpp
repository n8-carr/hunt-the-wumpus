#include "gold.hpp"
#include <iostream>
#include <string>

bool gold::encounter(player& p) {
    p.set_gold(true); // Sets player has gold bool to true
    p.set_result("You picked up gold!"); // Sets result for encounter
    return false; // Returns false, meaning it will be deleted
}

void gold::print() const {
    std::cout << "G"; // Prints G on grid
}
void gold::percept() const {
    // When player is near, will print
    std::cout << "You see something shimmer nearby." << std::endl; 
}

void gold::check_proximity(int ev_w, int ev_h, int p_x, int p_y) const {
    // Runs when event:
    //1. is in the same column and one row off
    //2. is in the same row and one column off
    if (ev_w == p_x && (ev_h == p_y - 1 || ev_h == p_y + 1) ||
    (ev_h == p_y && (ev_w == p_x - 1 || ev_w == p_x + 1))) {
        this->percept(); // Prints percept
    }
}

char gold::get_identify() const {
    return 'G'; // Returns G
}

gold* gold::copy() const {
    return new gold(*this); // Returns pointer to this gold event
}