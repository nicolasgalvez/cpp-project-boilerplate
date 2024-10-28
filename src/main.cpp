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

/**
 * Display goats and select one
 */
int select_goat(list<Goat> trip) {
    // When you're asking the user to select a certain goat, display a submenu in this format, allowing the user to input an integer to reference the correct goat.
    cout << "Select a goat:" << endl;
    display_trip(trip);

    int choice;
    cout << "Choose wisely --> ";
    cin >> choice;
    // validate choice
    if (choice < 1 || choice >trip.size()) {
        cout << "Invalid choice. Try again." << endl;
        return select_goat(trip);
    }
    return 0;
}
void delete_goat(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats to delete." << endl;
        return;
    }
    // select goat
    int choice = select_goat(trip);
    // delete goat
    auto it = trip.begin();
    advance(it, choice);
    cout << "Deleted " << it->get_name() << endl;
    trip.erase(it);
    
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
// When you're adding a goat, randomly select a name and color from main()'s arrays and select a random age between 0 and MAX_AGE.
    // get a random name, color
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = 1 + rand() % (MAX_AGE-1); // no 0 year old goats
    
    trip.emplace(trip.end(), Goat(name, age, color));
    cout << "Added " << name << " (" << age << ", " << color << ")" << endl;
}
void display_trip(list<Goat> trip) {
    if (trip.empty()) {
        cout << "No goats to display." << endl;
        return;
    }
    cout << "Gaot list:" << endl;
    int i = 1;
    for (Goat g : trip) {
        cout << "[" << i++ << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")" << endl;
    }
}


int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("../src/names.txt");
    // make sure file could be opened
    if (!fin) {
        cout << "Error opening file." << endl;
        return 1;
    }
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    cout << "Read " << i << " names." << endl;
    fin.close();
    ifstream fin1("../src/colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> trip;
    // add a bunch of temp goats for testing from the names and colors arrays
    // for (int i = 0; i < 10; i++) {
    //     trip.push_back(Goat(names[rand() % SZ_NAMES], rand() % MAX_AGE, colors[rand() % SZ_COLORS]));
    // }


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