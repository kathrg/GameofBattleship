/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Katherine Gurgenian
 * gurgenia
 *
 * Project 4: Battleship
 *
 * Class of all member functions that relate to a player in battleship
 */

#include <fstream>

#include "Player.h"


Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

void Player::init_grid() {
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            grid[i][j] = EMPTY_LETTER;
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
    return;
}

string Player::get_name() {
    return name;
}

int Player::get_num_ships() {
    return num_ships;
}

int Player::get_remaining_ships() {
    return remaining_ships;
}

char Player::get_grid_at(int row, int col) {
    return grid[row][col];
}

char Player::get_guess_grid_at(int row, int col) {
    return guess_grid[row][col];
}

void Player::add_ship(Ship ship) {
    Position startSpot = ship.get_start();
    Position endSpot = ship.get_end();
    //if there are no more ships to be added, return
    if (num_ships == MAX_NUM_SHIPS) {
        return;
    }
    else {
        //if ship's horizontal
        if (ship.is_horizontal()) {
            //if start comes before end
            if (startSpot.get_col() < endSpot.get_col()) {
                for (int i = startSpot.get_col(); i <= endSpot.get_col(); i++) {
                    grid[startSpot.get_row()][i] = SHIP_LETTER;
                }
            }
            //if end comes before start
            else if (startSpot.get_col() > endSpot.get_col()) {
                for (int i = startSpot.get_col(); i >= endSpot.get_col(); i--) {
                    grid[startSpot.get_row()][i] = SHIP_LETTER;
                }
            }
        }
        //if ship's vertical
        else {
            //if start comes before end
            if (startSpot.get_row() < endSpot.get_row()) {
                for (int i = startSpot.get_row(); i <= endSpot.get_row(); i++) {
                    grid[i][startSpot.get_col()] = SHIP_LETTER;
                }
            }
            //if end comes before start
            else if (startSpot.get_row() > endSpot.get_row()) {
                for (int i = startSpot.get_row(); i >= endSpot.get_row(); i--) {
                    grid[i][startSpot.get_col()] = SHIP_LETTER;
                }
            }
        }
        num_ships++;
        remaining_ships++;
        //add each ship to an array so that they can be referenced
        //by other member functions
        ships[num_ships - 1] = Ship(startSpot, endSpot);
        return;
    }
}

void Player::attack(Player &opponent, Position pos) {
    //conditions that constitute a miss...
    if ((opponent.get_grid_at((pos.get_row()),(pos.get_col())) == HIT_LETTER || opponent.get_grid_at((pos.get_row()),(pos.get_col())) == MISS_LETTER)) {
        cout << name << " " << pos << " miss" << endl;
    }
    // cont..
    else if (opponent.get_grid_at((pos.get_row()),(pos.get_col()))
             == EMPTY_LETTER) {
        opponent.grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
        cout << name << " " << pos << " miss" << endl;
    }
    //conditions that constitute a hit
    else {
        opponent.grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
        cout << name << " " << pos << " hit" << endl;
       
        for (int j = 0; j < MAX_NUM_SHIPS; ++j) {
            //hit if pos is in position of one of the ships in array
            if (opponent.ships[j].has_position(pos)) {
                opponent.ships[j].hit();
                //if enough hits to make a ship sink
                if (opponent.ships[j].has_sunk()) {
                    opponent.remaining_ships = opponent.remaining_ships - 1;
                    
                    announce_ship_sunk(opponent.ships[j].get_size());
                }
            }
        }
    }
    
    return;
}

void Player::announce_ship_sunk(int size) {
    //each size correlates to a type of ship
    if (size == 2) {
        cout << "Congratulations " << name << "! You sunk a Destroyer";
    }
    else if (size == 3) {
        cout << "Congratulations " << name << "! You sunk a Submarine";
    }
    else if (size == 4) {
        cout << "Congratulations " << name << "! You sunk a Battleship";
    }
    else if (size == 5) {
        cout << "Congratulations " << name << "! You sunk a Carrier";
    }
    return;
}

bool Player::load_grid_file(string filename) {
    Position startPoint;
    Position endPoint;
    ifstream positions;
    
    positions.open(filename);
    
    //if issue with opening file
    if (!positions.is_open()) {
        return false;
    }
    else {
        //if no issues with file
        if (positions.good()) {
            //5 represents max num of ships possible in battleship game,
            //if loop will not run if end of necessary info in file reached
            for (int i = 0; i < 5; i++) {
                //same thing as .eof (kind of)
                if (positions >> startPoint >> endPoint) {
                    add_ship(Ship(startPoint, endPoint));
                }
            }
            //close file
            positions.close();
        }
        return true;
    }
    
    return false;
}

bool Player::destroyed() {
    if (remaining_ships == 0) {
        return true;
    }
    else {
        return false;
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}
