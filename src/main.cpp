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


const int MAXCODES = 20000;
// auto<string> contenders[3] = {vector<string>(), list<string>(), set<string>()}; no work.
vector<string> vectorContender;
list<string> listContender;
set<string> setContender;



void displayResults();


int main()
{
    // Read the data into a basic array
    ifstream fin("../src/codes.txt");
    if (!fin)
    {
        cout << "Error opening file." << endl;
        return 1;
    }
    string codes[MAXCODES];
    int i = 0;
    while (fin >> codes[i++]) ;
    cout << "Read " << i << " codes." << endl;
    fin.close();

    // display the first 10 codes
    cout << "The first 10 codes are: ";
    for (int i = 0; i < 10; i++)
        cout << codes[i] << " ";
    cout << endl
    

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