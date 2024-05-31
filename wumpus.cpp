#include "wumpus.hpp"
#include <iostream>
#include <cmath>
#include <string>
// TODO Wumpus implementation (define wumpus member functions below)

bool wumpus::encounter(player& p)  {
    // Damages armor if player has it equipped, else damages player
    if (p.get_armor_health() > 0) {
        p.set_armor_health(p.get_armor_health() - 1);
    } else {
        p.take_damage();
    }
    p.set_result("Wumpus got you and is on the move!"); // For encounter
    return true; // Returns true, meaning it wont be deleted
}
void wumpus::print() const {
    std::cout << "W"; // Prints W to grid
}

void wumpus::percept() const {
    std::cout << "You smell a terrible stench" << std::endl; // For proximity
}

void wumpus::check_proximity(int ev_w, int ev_h, int p_x, int p_y) const {
    // Runs when event:
    //1. is in the same column and one row off
    //2. is in the same row and one column off
    if (ev_w == p_x && (ev_h == p_y - 1 || ev_h == p_y + 1) ||
    (ev_h == p_y && (ev_w == p_x - 1 || ev_w == p_x + 1))) {
        this->percept(); // Prints percept
    }
}

bool wumpus::hit_by_arrow(int wump_x, int wump_y, player& p, char direction) {
    // Returns true if wumpus is in the same column and 
    // within 3 rows distance of player
    if (direction == 'w' || direction == 's') {
        if (p.get_x() == wump_x && std::abs(p.get_y() - wump_y) <= 3) {
            return true;
        }
    // Returns true if wumpus is in the same row and within 
    // 3 columns distance of player
    } else if (direction == 'a' || direction == 'd') {
        if (p.get_y() == wump_y && std::abs(p.get_x() - wump_x) <= 3) {
            return true;
        }
    }
    return false; 
}

char wumpus::get_identify() const {
    return 'W'; // Returns W
}

wumpus* wumpus::copy() const {
    return new wumpus(*this); // Returns pointer to this wupus event
}