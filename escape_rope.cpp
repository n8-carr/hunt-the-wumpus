#include "escape_rope.hpp"
#include <iostream>

bool escape_rope::encounter(player& p) {
    return true; // Returns true, meaning it won't delete
}


void escape_rope::print() const {
    std::cout << "E"; // Prints E on grid
}

void escape_rope::percept() const { // No percept
}

void escape_rope::check_proximity(int ev_w, int ev_h, int p_x, int p_y) const {
} // No need for proximity

char escape_rope::get_identify() const {
    return 'E'; // Returns E
}

escape_rope* escape_rope::copy() const {
    return new escape_rope(*this); // Returns pointer to this escape rope event
}