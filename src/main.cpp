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
#include "Goat.h"

using namespace std;
const int SZ_NAMES = 200, SZ_COLORS = 25;
const int CHOICE_MIN = 0, CHOICE_MAX = 6, FREINDSHIP_MIN = 0, FRIENDSHIP_MAX = 10;
const string INVALID_CHOICE = "Invalid choice, me lord.";

// Get the game art
string trogdor = readAnsiFile("../src/trogdor.ans");

// Goated prototypes
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();


// function prototypes
void add_villager(map<string, tuple<int, string, string>> &villagerData);
void delete_villager(map<string, tuple<int, string, string>> &villagerData);
void increase_friendship(map<string, tuple<int, string, string>> &villagerData);
void decrease_friendship(map<string, tuple<int, string, string>> &villagerData);
void display_village(map<string, tuple<int, string, string>> villagerData);
string select_villager(map<string, tuple<int, string, string>> villagerData);
string search(map<string, tuple<int, string, string>> villagerData);
void burninate(string name);
string str_to_lower(const string &str);
int main_menu();

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
/**
 * Display the main menu and return the user's choice
 */
int main_menu()
{
    int choice;
    cout << "Villager Manager 3000" << endl;
    cout << "0. List Villagers" << endl;
    cout << "1. Add Villager" << endl;
    cout << "2. Delete Villager" << endl;
    cout << "3. Increase Friendship" << endl;
    cout << "4. Decrease Friendship" << endl;
    cout << "5. Search for Villager" << endl;
    cout << "6. Exit" << endl;
    cout << "Choice --> ";
    cin.clear();
    cin >> choice;
    // validate choice, make sure it's between 1 and 4
    if (choice < CHOICE_MIN || choice > CHOICE_MAX)
    {
        cout << INVALID_CHOICE << endl;
        return main_menu();
    }
    cout << endl;
    return choice;
}

/**
 * Display the villager data
 */
void show_villager(map<string, tuple<int, string, string>> villagerData, string key)
{
    cout << "Villager: " << key << endl;
    cout << "Friendship Level: " << get<0>(villagerData[key]) << endl;
    cout << "Species: " << get<1>(villagerData[key]) << endl;
    cout << "Catchphrase: " << get<2>(villagerData[key]) << endl;
}

/**
 * Search for a villager by name
 */
string search(map<string, tuple<int, string, string>> villagerData)
{
    string search;
    cout << "Enter the name of the villager you are searching for: ";
    // cin >> search;
    getline(cin >> ws, search);
    // how to make case insensitive? I remember I did it in a previous lab but not with search.
    // if (villagerData.find(search) != villagerData.end()) {
    //     cout <<  endl << "Found: "<< endl;
    //     show_villager(villagerData, search);
    // } else {
    //     cout << "Villager not found." << endl;
    // }

    // NOTE: This was throwing an exception, but I'm not sure why. I ran it again after a while and it worked.
    // Try lambda
    auto it = find_if(villagerData.begin(), villagerData.end(), [&search](const pair<string, tuple<int, string, string>> &item)
                      { return str_to_lower(item.first) == search || false; });
    // return key if found
    if (it != villagerData.end())
    {
        show_villager(villagerData, it->first);
        return it->first;
    }
    cout << "Villager not found." << endl;
    return "";
}

/**
 * Add a villager to the map
 */
void add_villager(map<string, tuple<int, string, string>> &villagerData)
{
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
        else if (friendshipLevel < FREINDSHIP_MIN || friendshipLevel > 10)
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

/**
 * Increase the friendship level of a villager
 */
void increase_friendship(map<string, tuple<int, string, string>> &villagerData)
{
    // select villager
    string key = select_villager(villagerData);
    // increase friendship
    // get the name from the tuple
    int friendship = get<0>(villagerData[key]);
    if (friendship < 10)
    {
        friendship++;
        get<0>(villagerData[key]) = friendship;
        cout << key << "'s friendship level increased to " << friendship << "." << endl;
    }
    else
    {
        cout << key << " already thinks you are a wise ruler." << endl;
    }
}

/**
 * Decrease the friendship level of a villager
 */
void decrease_friendship(map<string, tuple<int, string, string>> &villagerData)
{
    string key = select_villager(villagerData);
    int friendship = get<0>(villagerData[key]);
    if (friendship > FREINDSHIP_MIN)
    {
        friendship--;
        get<0>(villagerData[key]) = friendship;
        cout << key << "'s friendship level decreased to " << friendship << "." << endl;
    }
    else
    {
        cout << key << " is already planning revolt!" << endl;
    }
}

/**
 * Select a villager from the map
 */
string select_villager(map<string, tuple<int, string, string>> villagerData)
{
    // When you're asking the user to select a certain villager, display a submenu in this format, allowing the user to input an integer to reference the correct villager.
    display_village(villagerData);

    int choice;
    cout << "Choose wisely, me lud. --> ";
    cin >> choice;
    // validate choice
    if (choice < 1 || choice > villagerData.size())
    {
        cout << "Invalid choice, me lord." << endl;
        return select_villager(villagerData);
    }
    // Find the villager and return the key
    map<string, tuple<int, string, string>>::iterator it = villagerData.begin();
    advance(it, choice - 1);
    cout << "Selected " << it->first << endl;

    return it->first;
}

/**
 * Display the village data
 */
void display_village(map<string, tuple<int, string, string>> villagerData)
{
    cout << endl;
    if (villagerData.empty())
    {
        cout << "No goats to display." << endl;
        return;
    }
    cout << "Villager list:" << endl;
    // make a table with setw(15) for the first two items
    cout << setw(7) << left << "Index" << setw(15) << left << "Name" << setw(11) << "Friendship" << setw(8) << "Species" << setw(15) << "Catchphrase" << endl;
    // display villager names, species, and catchphrases
    for (map<string, tuple<int, string, string>>::iterator it = villagerData.begin();
         it != villagerData.end(); ++it)
    {
        // get iterator index, seems like maybe i++ would be more performant
        int index = distance(villagerData.begin(), it) + 1;
        // cast int as string
        string indexStr = to_string(index);
        indexStr.append(". ");
        cout << setw(7) << right << indexStr << left << setw(15) << it->first << setw(11) << left << get<0>(it->second) << setw(8) << left << get<1>(it->second) << setw(15) << left << get<2>(it->second) << endl;
    }
    cout << endl;
}

/**
 * Delete a villager from the map with dragon fire
 */
void delete_villager(map<string, tuple<int, string, string>> &villagerData)
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

/**
 * What it says on the tin
 */
void burninate(string name)
{
    if (!trogdor.empty())
    {
        displayAnsiArt(trogdor);
    }
    cout << name << " was BURNINATED!!" << endl;
}

/**
 * Main function, no args
 */
int main()
{
    // https://stackoverflow.com/questions/77740577/is-there-a-way-to-block-macos-terminal-resize-sys-calls
    signal(SIGWINCH, handleSigwinch);
    // declarations
    map<string, tuple<int, string, string>> villagerData; // Finally! PHP style associative arrays!
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
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
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
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;



    // populate the village
    villagerData["Audie"] = make_tuple(10, "Peasant", "More Work?");
    villagerData["Raymond"] = make_tuple(2, "Peasant", "Strange women lying in ponds distributing swords is no basis for a system of government.");
    villagerData["Max"] = make_tuple(2, "Wizard", "You rush a miracle man, you get rotten miracles.");
    villagerData["Valerie"] = make_tuple(2, "Witch", "I'm not a witch, I'm your wife! But after what you just said, I'm not even sure sure I want to be that anymore!");
    villagerData["Woman"] = make_tuple(2, "Peasant", "Well, I didn't vote for you.");

    int choice = main_menu();
    while (choice != 6)
    {
        switch (choice)
        {
        case 0:
            display_village(villagerData);
            break;
        case 1:
            add_villager(villagerData);
            break;
        case 2:
            delete_villager(villagerData);
            break;
        case 3:
            increase_friendship(villagerData);
            break;
        case 4:
            decrease_friendship(villagerData);
            break;
        case 5:
            search(villagerData);
            break;
        default:
            cout << INVALID_CHOICE << endl;
        }
        choice = main_menu();
    }
    return 0;
}