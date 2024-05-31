#include "arrow.hpp"
#include <iostream>
#include <string>

bool arrow::encounter(player& p) {
    p.set_num_arrows(p.get_num_arrows() + 1); // Adds 1 arrow to num arrows
    p.set_result("You picked up an arrow!"); // Sets message for encounter
    return false;
}


void arrow::print() const {
    std::cout << "A"; // Prints A
}

void arrow::percept() const {
    std::cout << "You see an arrow on the ground in an adjacent room." 
    << std::endl; // Prints percept
}

void arrow::check_proximity(int ev_w, int ev_h, int p_x, int p_y) const {
    // Runs when event:
    //1. is in the same column and one row off
    //2. is in the same row and one column off
    if (ev_w == p_x && (ev_h == p_y - 1 || ev_h == p_y + 1) ||
    (ev_h == p_y && (ev_w == p_x - 1 || ev_w == p_x + 1))) {
        this->percept(); // Prints percept
    }
}

char arrow::get_identify() const {
    return 'A'; // Returns A
}

arrow* arrow::copy() const {
    return new arrow(*this); // Returns pointer to this arrow event
}
