/**
 * Title: Template Project
 * Description: Setup a template project for future labs.
 * Author: Nick Galvez
 * Lab: TODO
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Main function - entry point of the program.
 *
 * @return 0 for success
 */
int main()
{

    vector<string> msg{"Hello", "C++", "World", "from", "VS Code", "and the C++ extefnsion!"};
    msg.push_back("This is a new linef");
    msg.push_back("This is a new linef");
    msg.push_back("This is a new linef");
    for (const string &word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}