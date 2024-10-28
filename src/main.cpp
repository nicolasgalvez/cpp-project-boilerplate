/**
 * Title: Lab 25: Data Structures Races
 * Description: We will code data structures at the races!
 * Author: Nick Galvez
 * Class: COMSC-210
 *
 */

/**
 * The starter code has a data file that is 20,000 lines long and contains random strings representing codes or IDs.

Which data structure is fastest?

We will code data structures at the races! In each race, the contestants (a vector, list, and set) will all compete against each other. There will be four various races! Write a program that will time, record, and report how long it takes each contestant to run these four races:

The first race is READING. The challenge is to read the 20,000 data elements into each of these data structures: vector, list, set
The second race is SORTING. Sort the vector and sort the list. Set the set's value to -1 since a set is already sorted.
The third race is INSERTING. Insert the value "TESTCODE" into the middle of the vector or the middle of the list, or into the set
The fourth race is DELETING. Delete the middle-ish element of the vector, the list, or the set
Use the cool time features of the <chrono> library. You'll just be using a stopwatch on these operations.
 */



#include <fstream>
#include <iomanip>
#include <set>
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;


const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string[], string[]);
void display_trip(set<Goat> trip);
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
int select_goat(set<Goat> trip)
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
 * Delete a goat from the set
 */
void delete_goat(set<Goat> &trip)
{
    if (trip.empty())
    {
        cout << "No goats to delete." << endl;
        return;
    }
    // select goat
    int choice = select_goat(trip);
    // delete goat
    set<Goat>::iterator it = trip.begin();
    advance(it, choice - 1);
    cout << "Deleted " << it->get_name() << endl;
    trip.erase(it);
}
/**
 * Add a goat to the set
 */
void add_goat(set<Goat> &trip, string names[], string colors[])
{
    // When you're adding a goat, randomly select a name and color from main()'s arrays and select a random age between 0 and MAX_AGE.
    // get a random name, color
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = 1 + rand() % (MAX_AGE - 1); // no 0 year old goats

    // search for an existing goat with the same name, if found check the age and color to make sure the new record is unique
    for (Goat g : trip)
    {
        if (g.get_name() == name && g.get_age() == age && g.get_color() == color)
        {
            // cout << "Goat already exists, rerolling goat." << endl;
            age = 1 + rand() % (MAX_AGE - 1);
            color = colors[rand() % SZ_COLORS];
            name = names[rand() % SZ_NAMES];
        }
    }

    trip.emplace(Goat(name, age, color));
    // trip.emplace(Goat(name, age, color)); // try to trigger a unique error, why doesn't this fail?

    cout << "Added " << name << " (" << age << ", " << color << ")" << endl;
}
/**
 * Display the set of goats
 */
void display_trip(set<Goat> trip)
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

    auto start = high_resolution_clock::now();

    // Example loop to measure
    vector<int> numbers;
    for(int i = 0; i < 1000000; ++i) {
        numbers.push_back(i);
    }

    // End timing
    auto end = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<milliseconds>(end - start);

    // Output the duration in milliseconds
    std::cout << "Time taken: " << duration.count() << " milliseconds\n";

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

    set<Goat> trip;

    // try to trigger a unique error
    // for (int i = 0; i < 10000; i++)
    // {
    //     add_goat(trip, names, colors);
    // }

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

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/