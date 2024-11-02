/**
 * Title: Lab 27: Villager Map
 * Description: Lab 27: Villager Map
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> studentGrades;

    // Inserting values
    studentGrades["Alice"] = 88;
    studentGrades.insert(make_pair("Bob", 95));

    // Access and modify
    cout << "Alice's grade: " << studentGrades["Alice"] << endl;
    studentGrades["Alice"] = 91; // Updating Alice's grade

    // Iteration
    for(const auto& pair : studentGrades) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Find
    auto search = studentGrades.find("Bob");
    if(search != studentGrades.end()) {
        cout << "Found Bob's grade: " << search->second << endl;
    }

    // Remove
    studentGrades.erase("Alice");

    return 0;
}