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


#include <list>
#include <fstream>
#include <iomanip>
#include <set>
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;


const int MAX_CODES = 20000;
// auto<string> contenders[3] = {vector<string>(), list<string>(), set<string>()}; no work.
// vector<string> vectorContender;
// list<string> listContender;
// set<string> setContender;

struct Clock {
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double> duration;
};


struct Contenders {
    vector<string> vectorContender;
    list<string> listContender;
    set<string> setContender;
    ~Contenders() {
        vectorContender.clear();
        listContender.clear();
        setContender.clear();
    }
};
class Race {
    public:
    Contenders contenders;
    Clock clock[3];
    
}


/**
 * The race function takes the contenders, the codes, and a callback (If I can figure that out)
 * https://stackoverflow.com/questions/2298242/callback-functions-in-c
 */
Clock race(Contenders &contenders, string codes[MAX_CODES], function<void(Contenders&, string)> insertFunc) {
    Clock clock;
    clock.start = high_resolution_clock::now();
    for (int i = 0; i < MAX_CODES; i++) {
        insertFunc(contenders, codes[i]);
    }
    clock.end = high_resolution_clock::now();
    clock.duration = duration_cast<duration<double>>(clock.end - clock.start);
    return clock;
}


void displayResults(Clock clock) {
    /**
     *  Operation    Vector      List       Set
      Read      4081      4664     12682
      Sort      6001      5993        -1
    Insert        97       310         5
    Delete       335       665         1
     */
    cout << "Operation" << setw(11) << "Vector" << setw(11) << "List" << setw(5) << "Set" << endl;
    cout << clock.duration.count() << endl;
}



int main()
{
    string codes[MAX_CODES];
    // Read the data into a basic array
    // I don't know if the file system will introduce variance in the timing so I'll do the read challenge using the data

    ifstream fin("../src/codes.txt");
    if (!fin)
    {
        cout << "Error opening file." << endl;
        return 1;
    }
    
    int i = 0;
    while (fin >> codes[i++]) ;
    cout << "Read " << i << " codes." << endl;
    fin.close();

    // display the first 10 codes for sanity check
    // for (int i = 0; i < 10; i++)
    //     cout << codes[i] << " ";
    // cout << endl;

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

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/