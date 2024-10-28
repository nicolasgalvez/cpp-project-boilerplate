/**
 * Title: Lab 23: Goat Manager 3001
 * Description: Goat boy
 * Author: Nick Galvez
 * Class: COMSC-210
 *
 */

// Write three more constructors for the Goat class: one that has just the name as an argument; one with name and age; and the last with all parameters.
// Write a GM3K1 engine that loops on this menu. Write a main_menu() function that outputs this and then obtains, validates, and returns the user's choice.
/**
*** GOAT MANAGER 3001 ***
[1] Add a goat
[2] Delete a goat
[3] List goats
[4] Quit
Choice --> 
 */
// Write functions to add a goat to the trip, delete a goat from the trip, and display the current trip.

// When you're adding a goat, randomly select a name and color from main()'s arrays and select a random age between 0 and MAX_AGE.

// When you're asking the user to select a certain goat, display a submenu in this format, allowing the user to input an integer to reference the correct goat.

/*
[1] Vida (14, Red)
    [2] Nola (14, Gold)
    [3] Todd (9, Green)
    [4] Faye (13, Silver)
    [5] Lena (12, Teal)
    [6] Owen (11, Magenta)
    [7] Kyle (10, Olive)
    [8] Vern (1, Gold)*/

// Task 4: Polish your output so it looks neatly laid out and flows intuitively.


#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    return 0;
}