/**
 * Title: Lab 7: Dynamic Arrays & Functions II
 * Description: Write a program that will reverse a string array.
 * Author: Nick Galvez
 * Lab: 7
 * Class: COMSC-210
 *
 */

#include <iostream>

using namespace std;

const int SIZE = 5;

// Write a function reverse() which receives the array as an argument, reverses the elements, and returns a pointer to the modified array.
// Is there a difference between string [], string [SIZE], and string a[SIZE]? Is one a better practice?
string *reverse(string []);

int main()
{
    // Stick with the classics.
    string names[SIZE] = {"Janet", "Jeffe", "Jin", "Joe", "Junio"};

    cout << "Original array: ";
    for (size_t i = 0; i < SIZE; i++)
    {
        cout << names[i] << " ";
    }
    cout << endl
         << "Reversed: ";

    // Set up a pointer for the reversed array.
    string *namesPtr = nullptr;
    namesPtr = reverse(names);

    for (size_t i = 0; i < SIZE; i++)
    {
        cout << namesPtr[i] << " ";
    }
    cout << endl;

    delete[] namesPtr;

    return 0;
}

/**
 * Return a reversed array of strings.
 */
string *reverse(string a[SIZE])
{
    string *ptr = nullptr;
    ptr = new string[SIZE];
    // Add the elements to the new array, by counting down from the last.
    for (size_t i = 0; i < SIZE; i++)
    {
        ptr[i] = a[SIZE - i - 1];
    }
    return ptr;
}