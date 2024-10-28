/**
 * Title: Lab 23: Goat Manager 3001
 * Description: Goat boy
 * Author: Nick Galvez
 * Class: COMSC-210
 *
 */

// Done Write three more constructors for the Goat class: one that has just the name as an argument; one with name and age; and the last with all parameters.
// Done Write a GM3K1 engine that loops on this menu. Write a main_menu() function that outputs this and then obtains, validates, and returns the user's choice.
// Write functions to add a goat to the trip, delete a goat from the trip, and display the current trip.

// When you're adding a goat, randomly select a name and color from main()'s arrays and select a random age between 0 and MAX_AGE.

// When you're asking the user to select a certain goat, display a submenu in this format, allowing the user to input an integer to reference the correct goat.

/*
        
    [2] Nola (14, Gold)
    [3] Todd (9, Green)
    [4] Faye (13, Silver)
    [5] Lena (12, Teal)
    [6] Owen (11, Magenta)
    [7] Kyle (10, Olive)
    [8] Vern (1, Gold)
    
    */

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

int main_menu() {
    int choice;
    cout << "*** GOAT MANAGER 3001 ***" << endl
         << "[1] Add a goat"  << endl
         << "[2] Delete a goat"  << endl
         << "[3] List goats" << endl
         << "[4] Quit" << endl
         << "Choice --> "  << endl;
    cin >> choice;
    // validate choice, make sure it's between 1 and 4
    if(choice < 1 || choice > 4) {
        cout << "Invalid choice. Try again." << endl;
        return main_menu();
    }

    return choice;
}

int select_goat(list<Goat> trip) {
    // When you're asking the user to select a certain goat, display a submenu in this format, allowing the user to input an integer to reference the correct goat.
    cout << "Select a goat:" << endl;
    int i = 1;
    for (Goat g : trip) {
        cout << "[" << i++ << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")" << endl;
    }

    return 0;
}
void delete_goat(list<Goat> &trip) {
    // select goat
    select_goat(trip);
}

void add_goat(list<Goat> &trip, string [], string []) {
// When you're adding a goat, randomly select a name and color from main()'s arrays and select a random age between 0 and MAX_AGE.

}
void display_trip(list<Goat> trip) {

}


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

    list<Goat> trip;
    int choice = main_menu();
    while (choice != 4) {
        switch (choice) {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
        choice = main_menu();
    }
    return 0;
}