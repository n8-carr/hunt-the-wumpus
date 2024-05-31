#include "room.hpp"

room::room() {}; // Default constructor

room::~room() {
    if (this->current_event != nullptr) {
        delete this->current_event; // Deletes current event if present
        this->current_event = nullptr; // Sets current event to nullptr
    }
}

void room::set_event(event* new_event) {
    if (this->current_event != nullptr) {
        delete this->current_event; // Deletes current event if present
    }
    this->current_event = new_event; // Sets current event to new event
}

event* room::get_event() const {
    return this->current_event; // Returns pointer to current event of room
}

room::room(const room& copy) {
    if(copy.current_event != nullptr) { 
        // Copies events of rooms when current event of copied room is nullptr
        this->current_event = copy.current_event->copy(); 
    } else {
        // Sets current event to nullptr
        this->current_event = nullptr;
    }
}

room& room::operator=(const room& copy) {
    if (this == &copy) { // Check that room isnt being copied to itself
		return *this;
	}
    delete current_event; // deletes current event of room
    // Same code as copy constructor
    if(copy.current_event != nullptr) {
        this->current_event = copy.current_event->copy();
    } else {
        this->current_event = nullptr;
    }
    return *this; // Returns pointer to room
}




