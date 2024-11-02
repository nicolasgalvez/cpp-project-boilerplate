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
// int select_villager(map<string, tuple<int, string, string>> villagerData);
// void delete_villager(map<string, tuple<int, string, string>> villagerData);
void add_villager(map<string, tuple<int, string, string>> &villagerData);
void display_village(map<string, tuple<int, string, string>> villagerData);
void burninate(string name);
int main_menu();

int main_menu()
{
    int choice;
    cout << "Villager Manager 3000" << endl;
    cout << "1. Add Villager" << endl;
    cout << "2. Delete Villager" << endl;
    cout << "3. Increase Friendship" << endl;
    cout << "4. Decrease Friendship" << endl;
    cout << "5. Search for Villager" << endl;
    cout << "6. Exit" << endl;
    cout << "Choice --> ";

    cin >> choice;
    // validate choice, make sure it's between 1 and 4
    if (choice < 1 || choice > 6)
    {
        cout << "Invalid choice. Try again." << endl;
        return main_menu();
    }
    cout << endl;
    return choice;
}

void add_villager(map<string, tuple<int, string, string>> &villagerData) {
    string name;
    int friendshipLevel;
    string species;
    string catchphrase;

    while (true)
    {
        cout << "Enter the name of the villager: ";
        getline(cin >> ws, name);
        if (name.empty())
        {
            cout << "Species cannot be empty. Try again." << endl;
        }
        else if (villagerData.find(name) != villagerData.end())
        {
            cout << "Villager already exists. Try again." << endl;
        }
        else
        {
            break;
        }
    }

    // TODO: Move to another function
    while (true)
    {
        cout << "Friendship level: ";
        cin >> friendshipLevel;
        // check for integer input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Friendship level must be an integer. Try again." << endl;
        }
        else if(friendshipLevel < 0 || friendshipLevel > 10)
        {
            cout << "Friendship level must be between 0 and 10. Try again." << endl;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "Species: ";
        cin >> species;
        if (species.empty())
        {
            cout << "Species cannot be empty. Try again." << endl;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "Catchphrase: ";
        getline(cin >> ws, catchphrase);
        if (catchphrase.empty())
        {
            cout << "Catchphrase cannot be empty. Try again." << endl;
        }
        else
        {
            break;
        }
    }

    cout << name << " added." << endl;


    villagerData[name] = make_tuple(friendshipLevel, species, catchphrase);

}

string select_villager(map<string, tuple<int, string, string>> villagerData)
{
    // When you're asking the user to select a certain villager, display a submenu in this format, allowing the user to input an integer to reference the correct villager.
    display_village(villagerData);

    int choice;
    cout << "Delete wisely --> ";
    cin >> choice;
    // validate choice
    if (choice < 1 || choice > villagerData.size())
    {
        cout << "Invalid choice. Try again." << endl;
        return select_villager(villagerData);
    }
    // Find the villager and return the key
    map<string, tuple<int, string, string>>::iterator it = villagerData.begin();
    advance(it, choice - 1);
    cout << "Selected " << it->first << endl;

    return it->first;
}
/**
 * Display the set of goats
 */
void display_village(map<string, tuple<int, string, string>> villagerData)
{
    cout << endl;
    if (villagerData.empty())
    {
        cout << "No goats to display." << endl;
        return;
    }
    cout << "Goat list:" << endl;
    // display villager names, species, and catchphrases
    for (map<string, tuple<int, string, string>>::iterator it = villagerData.begin();
         it != villagerData.end(); ++it)
    {   
        // get iterator index, seems like maybe i++ would be more performant
        int index = distance(villagerData.begin(), it) + 1;
        cout << index << ". " << it->first << ": " << get<1>(it->second) << " - " << get<2>(it->second) << endl;
    }
    cout << endl;
}

void delete_villager(map<string, tuple<int, string, string>> villagerData)
{
    if (villagerData.empty())
    {
        cout << "Village is Empty." << endl;
        return;
    }
    // select villager
    string key = select_villager(villagerData);
    // delete villager
    // get the name from the tuple
    // string name = get<2>(villagerData[key]); // Whoops! This is the quote not the name
    villagerData.erase(key);
    burninate(key);
}
void burninate(string name)
{
    if (!trogdor.empty())
    {
        displayAnsiArt(trogdor);
    }
    cout << name << " was BURNINATED!!" << endl;
}

int main()
{
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

    // // report size, clear, report size again to confirm map operations
    // cout << "\nSize before clear: " << villagerColors.size() << endl;
    // villagerColors.clear();
    // cout << "Size after clear: " << villagerColors.size() << endl;
    int choice = main_menu();
    display_village(villagerData);
    while (choice != 6)
    {
        switch (choice)
        {
        case 7:
            display_village(villagerData);
        case 1:
            add_villager(villagerData);
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
        display_village(villagerData);
        choice = main_menu();
    }
    return 0;
}