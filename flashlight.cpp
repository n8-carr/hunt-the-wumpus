#include "flashlight.hpp"
#include <iostream>

bool flashlight::encounter(player& p) {
    p.set_flash(true); // Sets player flashlight bool to true
    p.set_result("You picked up a flashlight!"); // Sets result for encounter
    return false; // Returns false, meaning it will be deleted
}

void flashlight::print() const {
    std::cout << "F"; // Prints F on grid
}

void flashlight::percept() const {
    std::cout << "You see a light nearby." << std::endl; // For proximity
}

void flashlight::check_proximity(int ev_w, int ev_h, int p_x, int p_y) const {
    // Runs when event:
    //1. is in the same column and one row off
    //2. is in the same row and one column off
    if (ev_w == p_x && (ev_h == p_y - 1 || ev_h == p_y + 1) ||
    (ev_h == p_y && (ev_w == p_x - 1 || ev_w == p_x + 1))) {
        this->percept(); // Prints percept
    }
}

char flashlight::get_identify() const {
    return 'F'; // Returns F
}

flashlight* flashlight::copy() const {
    return new flashlight(*this); // Returns pointer for this flashlight event
}