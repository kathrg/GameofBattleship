/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Katherine Gurgenian
 * gurgenia
 *
 * Project 4: Battleship
 *
 * Class of all member functions that relate to a ship in battleship
 */

#include <cmath>

#include "Ship.h"
#include "Position.h"


Ship::Ship() {
    start = Position();
    end = Position();
    size = 0;
    num_hits = 0;
}

Ship::Ship(Position start_in, Position end_in) {
    start = start_in;
    end = end_in;
    num_hits = 0;
    
    //abs value bc end can come before start
    //increment because each row's and col's underlying int differs by 1
    if (is_horizontal()) {
        size = abs(start.get_col() - end.get_col()) + 1;
    }
    else {
        size = abs(start.get_row() - end.get_row()) + 1;
    }
}

Position Ship::get_start() {
    return start;
}

Position Ship::get_end() {
    return end;
}

int Ship::get_size() {
    return size;
}

bool Ship::is_horizontal() {
    if (start.get_row() == end.get_row()) {
        return true;
    }
    else {
        return false;
    }
}

bool Ship::has_position(Position pos) {
    //if ship is horizontal
    if (is_horizontal() && pos.get_row() == start.get_row()) {
        //if start comes before end
        if (start.get_col() < end.get_col()) {
            //checks if pos is in range
            if (pos.get_col() >= start.get_col() &&
                pos.get_col() <= end.get_col()) {
                return true;
            }
            else {
                return false;
            }
        }
        //if end comes before start
        else if (start.get_col() > end.get_col()) {
            //checks if pos is in range
            if (pos.get_col() <= start.get_col() &&
                pos.get_col() >= end.get_col()) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    //if ship is vertical
    else if (start.get_col() == end.get_col() &&
             pos.get_col() == start.get_col()) {
        //if start comes before end
        if (start.get_row() < end.get_row()) {
            //checks if pos is in range
            if (pos.get_row() >= start.get_row() &&
                pos.get_row() <= end.get_row()) {
                return true;
            }
            else {
                return false;
            }
        }
        //if end comes before start
        else if (start.get_row() > end.get_row()) {
            //checks if pos is in range
            if (pos.get_row() <= start.get_row() &&
                pos.get_row() >= end.get_row()) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void Ship::hit() {
    //if hit is made by player, inc hits until hits = size...
    if (num_hits < size) {
        num_hits++;
    }
    return;
}

bool Ship::has_sunk() {
    //... once hits = size, ship has sunk
    if (num_hits == size) {
        return true;
    }
    else {
        return false;
    }
}
