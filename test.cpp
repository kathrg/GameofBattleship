/**
 * Copyright 2019 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;


void test_position();
void test_ship();
void test_player();
void test_game();

void startTests() {
    test_position();
    test_ship();
    test_player();
    test_game();
    
    return;
}

void test_position() {
    Position p1;
    cout << "( " << p1.get_row() << ", " << p1.get_col() << " )" << endl;
    
    Position p2(1,6);
    Position p3;
    
    p2.set_row(8);
    p2.set_col(2);
    
    cout << "( " << p2.get_row() << ", " << p2.get_col() << " )" << endl;
    
    //testing read
    ifstream input_file;
    input_file.open("grid1.txt");
    if (input_file.good()) {

        p1.read(input_file);
        p3.read(input_file);
        
        cout << p1 << " " << p3 << endl;
    }
    else {
        cout << "\nError opening grid1.txt\n";
    }
    
    return;
}

void test_ship() {
    Ship s5;
    Ship s1;
    Position start(2, 4);
    Position end(2, 7);
    Position endTwo(4, 4);
    Position endThree(0, 4);
    Position p1(2, 8);
    Position p2(2, 5);
    Ship s2 (start, end);
    Ship s3 (start, endTwo);
    Ship s4 (start, endThree);
    
    
    //default constructor stats
    cout << s5.get_start() << " " << s5.get_end() << " " << s5.get_size() << endl;
    //ship 2 stats
    cout << s2.get_start() << " " << s2.get_end() << " " << s2.get_size() << endl;
    
    //ship 3 stats
    cout << s3.get_start() << " " << s3.get_end() << " " << s3.get_size() << endl;
    
    //ship 4 stats
    cout << s4.get_start() << " " << s4.get_end() << " " << s4.get_size() << endl;
    
    if (s2.is_horizontal()) {
        cout << "s2 is horizontal" << endl;
    }
    else if (s3.is_horizontal()) {
        cout << "s3 is horizontal" << endl;
    }
    else if (s4.is_horizontal()) {
        cout << "s4 is horizontal" << endl;
    }
    else {
        cout << "no ships are horizontal" << endl;
    }
    
    if (s2.has_position(p1)) {
        cout << "s2 has position p1" << endl;
    }
    else if (s2.has_position(p2)) {
        cout << "s2 is position p2" << endl;
    }
    else {
        cout << "s2 has none of the provided positions" << endl;
    }
    
    //test hits
    s2.hit();
    cout << s2.has_sunk() << endl;
    s2.hit();
    cout << s2.has_sunk() << endl;
    s2.hit();
    cout << s2.has_sunk() << endl;
    s2.hit();
    cout << s2.has_sunk() << endl;

    s3.hit();
    s3.hit();
    s3.hit();
    s3.hit();
    s3.hit();
    s3.hit();
    s3.hit();
    s3.hit();
    s3.hit();
    cout << s3.has_sunk();
    

    
    return;
}

void test_player() {
    Ship s2;
    Player p1;
    Player p2("katya");
    Player p3("kat");
    Player p4("rose");
    Player p5("k");
    Player p6("kk");
    
    cout << p2.get_name() << endl;
    
    p2.init_grid();
    p2.print_grid();
    
    Position start(7, 1);
    Position end(7, 2);
    Position startTwo(5, 2);
    Position endTwo(1, 2);
    Position startThree('3', 'B');
    Position endThree('3', 'D');
    Position startExtra(0,0);
    Position endExtra(4,0);
    Position startExtraTwo(0,1);
    Position endExtraTwo(4,1);
    
    p2.add_ship(Ship(start, end));
    p2.add_ship(Ship(startTwo, endTwo));
    p2.add_ship(Ship(startThree, endThree));
    p2.add_ship(Ship(start, start));
    p2.add_ship(Ship(start, startTwo));
    p2.print_grid();
    
    p3.add_ship(Ship(startExtra, endExtra));
    p3.add_ship(Ship(startExtraTwo, endTwo));
    p3.print_grid();
    
    p3.load_grid_file("grid1.txt");
    p3.print_grid();
    cout << endl << p3.get_num_ships() << " " << p3.get_remaining_ships() << endl;
    
    p4.load_grid_file("grid2.txt");
    p4.print_grid();
    cout << endl << p4.get_num_ships() << " " << p4.get_remaining_ships() << endl;
    
    p5.load_grid_file("");
    p5.print_grid();
    cout << endl;
    
    cout << p3.get_grid_at(0, 0) << " " << p3.get_grid_at(7, 1) << endl;
    
    
    p3.attack(p4, Position('1', 'X'));
    p3.attack(p4, Position('1', 'E'));
    p4.attack(p3, Position('8', 'B'));
    p3.attack(p4, Position('2', 'e'));
    p4.attack(p3, Position('8', 'B'));
    p3.attack(p4, Position('3', 'F'));
    p4.attack(p3, Position('8', 'C'));
    
    cout << endl;
    
    //p3 stats
    p3.print_grid();
    p3.print_guess_grid();
    cout << "(should be 4) remaining ships: " << p3.get_remaining_ships() << " ///////tot num of ships: " << p3.get_num_ships() << " ///////old chars: " << p3.get_grid_at(7, 1) << " " << p3.get_grid_at(7, 2) << endl << endl;
    
    //p4 stats
    p4.print_grid();
    p4.print_guess_grid();
    cout << "remaining ships: " << p4.get_remaining_ships() << " ///////tot num of ships: " << p4.get_num_ships() << " ///////old char: " << p4.get_grid_at(2, 5) << endl << endl;

    return;
}

void test_game() {
    Game g3;
    Game g1;
    Game g2;
    Player p1;
    Player p2;
    Player p3;
    Player p4;
    Game(p1, "idk.txt", p2, "");
    p1.print_grid();
    cout << endl;
    p2.print_grid();
    cout << endl;
    
    
    Game(p3, "grid1.txt", p4, "grid2.txt");
    p3.print_grid();
    cout << endl;
    p4.print_grid();
    cout << endl;
    
    cout << g1.get_p1().get_name();
    cout << g2.get_p2().get_name();

    g2.get_move("Katyuh");
    
    
    g1.check_valid_move("YUHHHH");
    g1.check_valid_move("!!");
    g1.check_valid_move("3Q");
    g1.check_valid_move("!D");
    
    //shouldn't cout anything
    g1.check_valid_move("3b");
    g1.check_valid_move("3B");
    
    
    
    
    return;
}

