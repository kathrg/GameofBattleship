/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Katherine Gurgenian
 * gurgenia
 *
 * Project 4: Battleship
 *
 * Class of all member functions that relate to a position in battleship
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    row = 0;
    col = 0;
}

Position::Position(int row_in, int col_in) {
    row = check_range(row_in);
    col = check_range(col_in);
}

Position::Position(char row_in, char col_in) {
    int newRow = 0;
    int listOfNumbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    char correspondingNumChars[10] = {'0', '1', '2', '3', '4', '5', '6', '7',
        '8'};
    
    //convert char of row to int of row
    for (int i = 1; i <= 8; ++i) {
        if (correspondingNumChars[i] == row_in) {
            newRow = listOfNumbers[i] - 1;
        }
    }
    
    row = check_range(newRow);
    
    //65 is the ASCII value for 'A'
    col = check_range(int(toupper(col_in)) - 65);
}

int Position::get_row() {
    return row;
}

void Position::set_row(int row_in) {
    //prior to setting, make sure row is in range
    row = check_range(row_in);
    return;
}

int Position::get_col() {
    return col;
}

void Position::set_col(int col_in) {
    //prior to setting, make sure col is in range
    col = check_range(col_in);
    return;
}

void Position::read(istream &is) {
    string position;
    char rowVal = 0;
    char colVal = 0;
    
    //make sure file is good
    if (!is.fail() && is.good()) {
        is >> position;
        
        //goes through an input from file and extracts only number and letter
        for (int i = 0; i < position.size(); ++i) {
            if (isdigit(position.at(i))) {
                rowVal = position.at(i);
            }
            else if (isalpha(position.at(i))) {
                colVal = position.at(i);
            }
        }
        
        int finalRow = 0;
        int listOfNumbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        char correspondingNumChars[10] = {'0', '1', '2', '3', '4', '5', '6',
            '7', '8'};
        
        //converts row's char to int
        for (int i = 0; i <= 8; ++i) {
            if (correspondingNumChars[i] == rowVal) {
                finalRow = listOfNumbers[i] - 1;
            }
        }
        
        row = check_range(finalRow);
        col = check_range(int(toupper(colVal)) - 65);
    }
    
    return;
}

void Position::write(ostream &os) {
    char newCol = 'A';
    
    int listofNumbers[10] = {0, 1, 2, 3, 4, 5, 6, 7};
    char correspondingLetter[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    
    //convert underlying int from grid's index to col's char
        for (int i = 0; i < 8; ++i) {
            if (listofNumbers[i] == col) {
                newCol = correspondingLetter[i];
            }
        }
    //incremement row because every position is one higher than its
    //underlying int from the grid's index
    os << "(" << row + 1 << "," << newCol << ")";

    return;
}

int Position::check_range(int val) {
    if (val >= 0 && val < MAX_GRID_SIZE) {
        return val;
    }
    else if (val < 0) {
        return 0;
    }
    else {
        return MAX_GRID_SIZE - 1;
    }
}


// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}

