/**
 * Title: Lab 24: GM3K2
 * Description: Convert your Lab 23 to a std::set.
 * Author: Nick Galvez
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string[], string[]);
void display_trip(list<Goat> trip);
int main_menu();

int main_menu()
{
    int choice;
    cout << endl
         << "*** GOAT MANAGER 3001 ***" << endl
         << "[1] Add a goat" << endl
         << "[2] Delete a goat" << endl
         << "[3] List goats" << endl
         << "[4] Quit" << endl
         << "Choice --> ";
    cin >> choice;
    // validate choice, make sure it's between 1 and 4
    if (choice < 1 || choice > 4)
    {
        cout << "Invalid choice. Try again." << endl;
        return main_menu();
    }
    cout << endl;
    return choice;
}

/**
 * Display goats and select one
 */
int select_goat(list<Goat> trip)
{
    // When you're asking the user to select a certain goat, display a submenu in this format, allowing the user to input an integer to reference the correct goat.
    display_trip(trip);

    int choice;
    cout << "Delete wisely --> ";
    cin >> choice;
    // validate choice
    if (choice < 1 || choice > trip.size())
    {
        cout << "Invalid choice. Try again." << endl;
        return select_goat(trip);
    }

    return choice;
}
/**
 * Delete a goat from the list
 */
void delete_goat(list<Goat> &trip)
{
    if (trip.empty())
    {
        cout << "No goats to delete." << endl;
        return;
    }
    // select goat
    int choice = select_goat(trip);
    // delete goat
    list<Goat>::iterator it = trip.begin();
    advance(it, choice - 1);
    cout << "Deleted " << it->get_name() << endl;
    trip.erase(it);
}
/**
 * Add a goat to the list
 */
void add_goat(list<Goat> &trip, string names[], string colors[])
{
    // When you're adding a goat, randomly select a name and color from main()'s arrays and select a random age between 0 and MAX_AGE.
    // get a random name, color
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = 1 + rand() % (MAX_AGE - 1); // no 0 year old goats

    trip.emplace(trip.end(), Goat(name, age, color));
    cout << "Added " << name << " (" << age << ", " << color << ")" << endl;
}
/**
 * Display the list of goats
 */
void display_trip(list<Goat> trip)
{
    if (trip.empty())
    {
        cout << "No goats to display." << endl;
        return;
    }
    cout << "Goat list:" << endl;
    int i = 1;
    for (Goat g : trip)
    {
        cout << "[" << i++ << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")" << endl;
    }
}

int main()
{
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("../src/names.txt");
    // make sure file could be opened
    if (!fin)
    {
        cout << "Error opening file." << endl;
        return 1;
    }
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++])
        ;
    cout << "Read " << i << " names." << endl;
    fin.close();
    ifstream fin1("../src/colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++])
        ;
    fin1.close();

    list<Goat> trip;

    int choice = main_menu();
    while (choice != 4)
    {
        switch (choice)
        {
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