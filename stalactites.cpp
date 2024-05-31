#include "stalactites.hpp"
#include <iostream>
#include <string>

bool stalactites::encounter(player& p) {
    if (rand() % 2 == 0) { // Runs 1 in 2 chances
        if (p.get_armor_health() > 0) { // If player has armor, damage armor
            p.set_armor_health(p.get_armor_health() - 1);
        } else {
            p.take_damage(); // Damage player if player doesn't have armmor
        }
        p.set_result("You were hit!"); // Result for encounter
    } else {
        // Runs when player is not hit by the 1 in 2 chance
        p.set_result("You feel water dripping on your head...");
    }
    return true; // Returns true, meaning it won't be deleted
}

void stalactites::print() const {
    std::cout << "S"; // Prints S to the grid
}

void stalactites::percept() const {
    std::cout << "You hear water dripping." << std::endl; // For proximity
}

void stalactites::check_proximity(int ev_w, int ev_h, int p_x, int p_y) const {
    // Runs when event:
    //1. is in the same column and one row off
    //2. is in the same row and one column off
    if (ev_w == p_x && (ev_h == p_y - 1 || ev_h == p_y + 1) ||
    (ev_h == p_y && (ev_w == p_x - 1 || ev_w == p_x + 1))) {
        this->percept(); // Prints percept
    }
}

char stalactites::get_identify() const {
    return 'S'; // Returns S
}

stalactites* stalactites::copy() const {
    return new stalactites(*this); // Returns pointer to this stalactites event
}