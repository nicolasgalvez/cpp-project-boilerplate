/**
 * Title: Lab 27: Villager Map
 * Description: Lab 27: Villager Map
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <map>
#include <vector>
#include "ansi.h"


using namespace std;
    string trogdor = readAnsiFile("../src/trogdor.ans");

// struct Villager {
//     int friendshipLevel; // 0-10
//     string species;
//     string catchphrase;
// };
// int select_villager(set<villager> trip);
// void delete_villager(set<villager> &trip);
// void add_villager(set<villager> &trip, string[], string[]);
// void display_trip(set<villager> trip);
int main_menu();

int main_menu()
{
    int choice;
    cout << endl
         << "*** villager MANAGER 3001 ***" << endl
         << "[1] Add a villager" << endl
         << "[2] Delete a villager" << endl
         << "[3] List villagers" << endl
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
void burninate( )
{
    if (!trogdor.empty()) {
        displayAnsiArt(trogdor);
    }
    cout << "BURNINATED!!" << endl;
}

int main() {
    // declarations
    
    // Change the data we're storing to friendship level (0-10), the villager's species (string), and the villager's catchphrase (string)
    map<string, tuple<int, string, string>> villagerData; // Finally! PHP style associative arrays!

    villagerData["Audie"] = make_tuple(10, "Peasant", "More Work?");
    villagerData["Raymond"] = make_tuple(2, "Peasant", "Strange women lying in ponds distributing swords is no basis for a system of government.");
    villagerData["Max"] = make_tuple(2, "Wizard", "You rush a miracle man, you get rotten miracles.");
    villagerData["Valerie"] = make_tuple(2, "Witch", "I'm not a witch, I'm your wife! But after what you just said, I'm not even sure sure I want to be that anymore!");
    villagerData["Woman"] = make_tuple(2, "Peasant", "Well, I didn't vote for you."); 

    // insert elements into the map
    // note how the right-hand side of the assignment are the vector elements
    // villagerColors["Audie"] = {"Orange", "Yellow", "Red"};
    // villagerColors["Raymond"] = {"Black", "Gray", "White"};
    // villagerColors.insert({"Marshal", {"Blue", "White", "Black"}});

    // // access the map using a range-based for loop
    // cout << "Villagers and their favorite colors (range-based for loop):" << endl;
    // for (auto pair : villagerColors) {
    //     cout << pair.first << ": ";
    //     for (auto color : pair.second)
    //         cout << color << " ";
    //     cout << endl;
    // }

    // // access the map using iterators
    // cout << "\nVillagers and their favorite colors (iterators):" << endl;
    // for (map<string, vector<string>>::iterator it = villagerColors.begin(); 
    //                                            it != villagerColors.end(); ++it) {
    //     cout << it->first << ": ";
    //     for (auto color : it->second) {
    //         cout << color << " ";
    //     }
    //     cout << endl;
    // }

    // // delete an element
    // villagerColors.erase("Raymond");

    // // search for an element using .find() to avoid errors
    // string searchKey = "Audie";
    // auto it = villagerColors.find(searchKey);
    // if (it != villagerColors.end()) {  // the iterator points to beyond the end of the map
    //                                    // if searchKey is not found
    //     cout << "\nFound " << searchKey << "'s favorite colors: ";
    //     for (auto color : it->second)  // range loop to traverse the value/vector
    //         cout << color << " ";
    //     cout << endl;
    // } else
    //     cout << endl << searchKey << " not found." << endl;

    // // report size, clear, report size again to confirm map operations
    // cout << "\nSize before clear: " << villagerColors.size() << endl;
    // villagerColors.clear();
    // cout << "Size after clear: " << villagerColors.size() << endl;
    int choice = main_menu();
    while (choice != 4)
    {
        switch (choice)
        {
        case 1:
            add_villager(villagerData, names, colors);
            break;
        case 2:
            delete_villager(villagerData);
            break;
        case 3:
            display_village(villagerData);
            break;
        default:
            cout << "Invalid choice, me lord." << endl;
        }
        choice = main_menu();
    }
    return 0;
}