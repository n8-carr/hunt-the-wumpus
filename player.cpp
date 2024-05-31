#include "player.hpp"
#include "game.hpp"
#include <iostream>

// Non-default constructor of player
player::player(int x, int y, int game_w, int game_h) :
   x(x),
   y(y),
   game_w(game_w),
   game_h(game_h) {
}

int player::get_num_lives() const {
   return this->lives; 
}

int player::get_armor_health() const {
   return this->armor_health;
}

void player::set_armor_health(const int& new_health) {
   this->armor_health = new_health;
}

void player::take_damage() {
   this->lives--; // Takes one life away
}

int player::get_num_arrows() const {
   return this->num_arrows;
}

void player::set_num_arrows(const int& new_num) {
   this->num_arrows = new_num;
}

bool player::has_gold() const {
   return gold;
}

void player::set_gold(const bool& new_gold) {
   this->gold = new_gold;
}

bool player::has_flash() const {
   return flashlight;
}

void player::set_flash(const bool& new_flash) {
   this->flashlight = new_flash;
}

int player::get_x() const {
   return this->x;
}

int player::get_y() const {
   return this->y;
}
void player::set_location(const int& x_cord, const int& y_cord) {
   this->x = x_cord; // Sets x and y coordinates of player
   this->y = y_cord;
}

int player::get_game_w() const {
   return this->game_w;
}
int player::get_game_h() const {
   return this->game_h;
}

void player::move_up() {
   if (y>1) { // Checks that player is not at the top of the grid
      this->y--;
   }
}

void player::move_down() {
   if (y < game_h) { // Checks that player is not at the bottom of the grid
      this->y++;
   }
}

void player::move_left() { 
   if (x > 1) { // Checks that player is not at the most left of the grid
      this->x--;
   }
}

void player::move_right() {
   if (x < game_w) { // Checks that player is not at the most right of the grid
      this->x++;
   }
}

std::string player::get_result() const {
   return this->result;
}

void player::set_result(const std::string& new_string) {
   this->result = new_string;
}



