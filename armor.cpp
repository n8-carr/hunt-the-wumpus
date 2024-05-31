#include "armor.hpp"
#include <iostream>
#include <string>

bool armor::encounter(player& p) {
    p.set_armor_health(2); // Sets player health to 2 lives
    p.set_result("You picked up armor!"); // Prints message from encounter
    return false;
}


void armor::print() const {
    std::cout << "M"; // Prints M
}

void armor::percept() const {
    std::cout << "You feel the power." << std::endl; // Prints percept
}

void armor::check_proximity(int ev_w, int ev_h, int p_x, int p_y) const {
    // Runs when event:
    //1. is in the same column and one row off
    //2. is in the same row and one column off
    if (ev_w == p_x && (ev_h == p_y - 1 || ev_h == p_y + 1) ||
    (ev_h == p_y && (ev_w == p_x - 1 || ev_w == p_x + 1))) {
        this->percept(); // Prints percept
    }
}

char armor::get_identify() const {
    return 'M'; // Returns M
}

armor* armor::copy() const {
    return new armor(*this); // Returns copy of this event
}