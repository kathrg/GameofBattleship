/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Katherine Gurgenian
 * gurgenia
 *
 * Project 4: Battleship
 *
 * Class of all necessary member functions in order to play a game of battleship
 */

#include <fstream>

#include "Game.h"


Game::Game() {
    p1 = Player();
    p2 = Player();
}

Game::Game(Player player1, string grid1, Player player2, string grid2) {
    p1 = player1;
    p2 = player2;
    
    //generate random grids if issue with files
    if (!p1.load_grid_file(grid1) || grid1 == "") {
        generate_random_grid(p1);
        cout << "Generating random grid for " << p1.get_name() << endl;
    }
    
    if (!p2.load_grid_file(grid2) || grid1 == "") {
        generate_random_grid(p2);
        cout << "Generating random grid for " << p2.get_name() << endl;
        
    }
}

Player Game::get_p1() {
    return p1;
}

Player Game::get_p2() {
    return p2;
}

string Game::get_move(string player_name) {
    string move;
    
    cout << player_name << " enter your move: ";
    cin >> move;
    cout << endl;
    
    return move;
}

bool Game::check_valid_move(string move) {
    //move must be only size of 2
    if (move.size() != 2) {
        cout << p1.get_name() << " you entered an invalid input";
        return false;
    }
    //move must be [1-8] and [A-H] or [a-h] to be valid
    else if ((move.at(0) <= '8' && move.at(0) >= '1') && ((move.at(1) <= 'H' &&
        move.at(1) >= 'A') || (move.at(1) <= 'h' && move.at(1) >= 'a'))) {
        return true;
    }
    else {
        cout << p1.get_name() << " you entered an invalid position" << endl;
        return false;
    }
}

void Game::start(char difficulty, int max_num_rounds) {
    string playerMove;
    //start with zero rounds
    int completedRounds = 0;

    if (difficulty == EASY) {
        //continue playing the game until max rounds is reached or p1 or p2
        //have no more ships
        while ((completedRounds != max_num_rounds) && (! p1.destroyed()) &&
               (! p2.destroyed())) {
            
            //get move
            playerMove = get_move(p1.get_name());
            
            cout << endl;
            
            //check validity of move
            while (!check_valid_move(playerMove)) {
                playerMove = get_move(p1.get_name());
                
                cout << endl;
            }
            
            //p1 attacks
            p1.attack(p2, Position(playerMove.at(0), playerMove.at(1)));
            
            //if both players have remaining ships or p2 has remaining
            //ships, cont round
            if ((p2.get_remaining_ships() != 0 && p1.get_remaining_ships() != 0)
                || (p2.get_remaining_ships() != 0)) {
                
                opponent_make_move(EASY);
                
                //print grids after attacks
                cout << "Your grid" << endl;
                p1.print_grid();
                cout << "CPU's grid" << endl;
                p1.print_guess_grid();
                
                completedRounds++;
            }
        }
        
        //if p2 or p1 has zero remaining ships or max rounds reached,
        //game is finished
        if (p2.get_remaining_ships() == 0) {
            //to account for last round
            cout << endl << endl << "Your grid" << endl;
            p1.print_grid();
            cout << "CPU's grid" << endl;
            p1.print_guess_grid();
            completedRounds++;
            
            cout << endl << "Game over, winner is " << p1.get_name() <<
            " in " << completedRounds << " rounds";
        }
        else if (p1.get_remaining_ships() == 0) {
            cout << endl << "Game over, winner is " << p2.get_name() <<
            " in " << completedRounds << " rounds";
        }
        else {
            cout << endl << "Game over, winner is no one in " <<
            max_num_rounds << " rounds";
        }
    }
    //if irl p2 wants to be "CPU". Also, good for testing and sample runs
    else if (difficulty == EMULATE) {
        while ((completedRounds != max_num_rounds) &&
               (! p1.destroyed()) && (! p2.destroyed())) {
            
            //get player move
            playerMove = get_move(p1.get_name());
            
            cout << endl;
            
            //get valid player move
            while (!check_valid_move(playerMove)) {
                playerMove = get_move(p1.get_name());
                
                cout << endl;
            }
            
            
            //player attacks
            p1.attack(p2, Position(playerMove.at(0), playerMove.at(1)));
            
            if ((p2.get_remaining_ships() != 0 &&
                 p1.get_remaining_ships() != 0) ||
                (p2.get_remaining_ships() != 0)) {
                
                opponent_make_move(EMULATE);
                
                //print grids after attacks
                cout << "Your grid" << endl;
                p1.print_grid();
                cout << "CPU's grid" << endl;
                p1.print_guess_grid();
                
                completedRounds++;
            }
        }
        
        
        if (p2.get_remaining_ships() == 0) {
            //to account for last round
            cout << endl << endl << "Your grid" << endl;
            p1.print_grid();
            cout << "CPU's grid" << endl;
            p1.print_guess_grid();
            completedRounds++;
            
            cout << "Game over, winner is " << p1.get_name() << " in " <<
            completedRounds << " rounds";
        }
        else if (p1.get_remaining_ships() == 0) {
            cout << "Game over, winner is " << p2.get_name() << " in " <<
            completedRounds << " rounds";
        }
        else {
            cout << endl << "Game over, winner is no one in " <<
            max_num_rounds << " rounds";
        }
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

