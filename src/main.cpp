/**
 * Title: Lab 27: Villager Map
 * Description: Lab 27: Villager Map
 * Class: COMSC-210
 *
 */
#include <csignal>
#include <iostream>
#include <map>
#include <vector>
#include "ansi.h"
#include <fstream>
#include <iomanip>
#include <list>
#include <random>
#include "Goat.h"

using namespace std;
const int SZ_NAMES = 200, SZ_COLORS = 25;
const int CHOICE_MIN = 0, CHOICE_MAX = 11, FREINDSHIP_MIN = 0, FRIENDSHIP_MAX = 10;
const string INVALID_CHOICE = "Invalid choice, me lord.";



// Goated prototypes
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();


// function prototypes
// void add_villager(map<string, tuple<int, string, string>> &villagerData);
// void delete_villager(map<string, tuple<int, string, string>> &villagerData);
// void increase_friendship(map<string, tuple<int, string, string>> &villagerData);
// void decrease_friendship(map<string, tuple<int, string, string>> &villagerData);
// void display_village(map<string, tuple<int, string, string>> villagerData);
// string select_villager(map<string, tuple<int, string, string>> villagerData);
// string search(map<string, tuple<int, string, string>> villagerData);
// void burninate(string name);
// string str_to_lower(const string &str);
// int main_menu();

// Do nothing on terminal resize
void handleSigwinch(int signal)
{
}

/**
 * Convert a string to lowercase, you would think this is part of the string library.
 * @see https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
 **/
string str_to_lower(const string &str)
{
    string result = "";

    for (char ch : str)
    {
        // Convert each character to lowercase using tolower
        result += tolower(ch);
    }

    return result;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void clear(list<Goat> &trip) {
    // ask user for confirmation
    cout << "Are you sure you want to clear the trip? (y/n) ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        trip.clear();
        cout << "Trip cleared.\n";
    }

}

void copy(list<Goat> &trip) {
    list<Goat> tempTrip;
    // copy using copy stl
    copy(trip.begin(), trip.end(), back_inserter(tempTrip));
    // append the copy to the original
    trip.insert(trip.end(), tempTrip.begin(), tempTrip.end()); 
}

void erase(list<Goat> &trip) {
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat erased. New trip size: " << trip.size() << endl;
}

void reverse(list<Goat> &trip) {
    trip.reverse();
    cout << "New Goat Order:" << endl;
    display_trip(trip);
}

void sort(list<Goat> &trip) {
    trip.sort();
    cout << "Goats sorted." << endl;
    display_trip(trip);
}

void unique(list<Goat> &trip) {
    display_trip(trip);
    sort(trip); // doesn't work unless sorted
    auto newEnd = unique(trip.begin(), trip.end());
    trip.erase(newEnd, trip.end());
    display_trip(trip);
    cout << "Childs: So, how do we know who's a goat? If I was an imitation, a perfect imitation, how would you know if it was really me?" << endl;

}
void shuffle(list<Goat> &trip) {
    // copy to vector
    vector<Goat> tripVec(trip.begin(), trip.end());
    // shuffle vector
    shuffle(tripVec.begin(), tripVec.end(),
    default_random_engine());
    // copy back to list
    trip.assign(tripVec.begin(), tripVec.end());
    display_trip(trip);
}

void transform(list<Goat> &trip) {
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat goat) { 
        // there is a 1 in 4 chance that the goat is a thing
        if (rand() % 4 == 0) {
            goat.set_name(goat.get_name() + " is a THING!!!");
            goat.set_color("Gross");
            goat.set_age(1000);
        }
        return goat;
    });
    display_trip(trip);
}

/**
 * Display the main menu and return the user's choice
 */
int main_menu() {

    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";

    cout << "[4] Clear" << endl;
    cout << "[5] Copy" << endl;
    cout << "[6] Erase" << endl;
    cout << "[7] Reverse" << endl;
    cout << "[8] Sort" << endl;
    cout << "[9] Unique" << endl;
    cout << "[10] Shuffle" << endl;
    cout << "[11] Transform" << endl;

    cout << "[0] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < CHOICE_MIN || choice > CHOICE_MAX) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}
int main() {
    // Set up signal handler for terminal resize
    signal(SIGWINCH, handleSigwinch);
    // show goat
    string goatboy = readAnsiFile("../src/trogdor.ans");
    displayAnsiArt(goatboy);

    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("../src/names.txt");
    if(!fin) {
        cout << "Error opening file.\n";
        return 1;
    }
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("../src/colors.txt");
        if(!fin1) {
        cout << "Error opening file.\n";
        return 1;
    }
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 30x6 Engine
    int sel = main_menu();
    while (sel != 0) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Clear\n";
                clear(trip);
                break;
            case 5:
                cout << "Copying...\n";
                copy(trip);
                break;
            case 6:
                cout << "Erasing goat.\n";
                erase(trip);
                break;
            case 7:
                cout << "Reversing goat order.\n";
                reverse(trip);

                break;
            case 8:
                cout << "Sorting goats.\n";
                sort(trip);

                break;
            case 9:
                cout << "Removing imposter goats.\n";
                unique(trip);

                break;
            case 10:
                cout << "Shuffling Goats\n";
                shuffle(trip);
                break;
            case 11:
                cout << "Transforming goat data.\n";
                transform(trip);
                break;
            case 0:
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        cout << endl;
        sel = main_menu();
    }
    

    return 0;
}