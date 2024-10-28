/**
 * Title: Lab 25: Data Structures Races
 * Description: I ran out of time on this one. I keep trying to make patterns that use hash arrays, like PHP and loose typing. I want to be able to make an array of the contenders and then loop through them.
 * Author: Nick Galvez
 * Class: COMSC-210
 *
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

struct Clock
{
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double> duration;
};

struct Contenders
{
    vector<string> vectorContender;
    list<string> listContender;
    set<string> setContender;
    ~Contenders()
    {
        vectorContender.clear();
        listContender.clear();
        setContender.clear();
    }
};
/**
 * Probably a simpler way to do this.
 * This was a fun assignment but I ran out of time!
 * I'll keep working on it though.
 */
class Race
{
public:
    Contenders contenders;
    string codes[MAX_CODES];
    string name;
    // Time keeping, actually we don't need a seperate struct I think.
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double> duration;

    Race(string name)
    {
        this->name = name;
    }
    Race(string name, string codes[])
    {
        this->name = name;
        copy(codes, codes + MAX_CODES, this->codes); // didn't work with just this->codes = codes;
    }
    void race(string name, function<void(Contenders &, string)> insertFunc)
    {

        // start the clock and then run the callback
        start = high_resolution_clock::now();

        for (int i = 0; i < MAX_CODES; i++)
        {
            insertFunc(contenders, codes[i]);
        }
        // end the clock
        end = high_resolution_clock::now();
    }

}

/**
 * The race function takes the contenders, the codes, and a callback (If I can figure that out)
 * https://stackoverflow.com/questions/2298242/callback-functions-in-c
 */

void
displayResults(Clock clock)
{
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
    while (fin >> codes[i++])
        ;
    cout << "Read " << i << " codes." << endl;
    fin.close();

    // display the first 10 codes for sanity check
    // for (int i = 0; i < 10; i++)
    //     cout << codes[i] << " ";
    // cout << endl;

    auto start = high_resolution_clock::now();

    // Example loop to measure
    vector<int> numbers;
    for (int i = 0; i < 1000000; ++i)
    {
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