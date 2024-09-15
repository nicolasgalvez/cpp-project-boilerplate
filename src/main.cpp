/**
 * Title: Lab 6: Dynamic Arrays & Functions I
 * Description: Lab 6: Dynamic Arrays & Functions I
 * Author: Nick Galvez
 * Lab: 6
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <ctime>
using namespace std;

const int SIZE = 5, MIN = 1, MAX = 10;

double *getRandomArray();
void populateArray(double *);
void outputArray(double *);
double sumArray(double *);

/**
 * Write a function that will receive the double array and populate it with values that the user enters via the console.
 */
void populateArray(double *a)
{
    cout << "Data entry for the array:" << endl;
    for (size_t i = 0; i < SIZE; i++) // intellisense generated a for loop with size_t instead of int. But it seems to work ok as an array iterator...
    {
        cout << "> Element #" << i << ": ";
        cin >> a[i];
    }
    cout << "Data entry complete." << endl;
}
/**
 * Print the array on one line
 */
void outputArray(double *a)
{
    cout << "Outputting array elements: ";
    for (size_t i = 0; i < SIZE; i++)
    {
        cout << *(a + i) << " ";
    }
    cout << endl;
}
/**
 * Sum the array, do not output anything.
 */
double sumArray(double *a)
{
    double total = 0;
    for (size_t i = 0; i < SIZE; i++)
    {
        total += *(a + i);
    }
    return total;
}

int main()
{
    // Using dynamic memory allocation, create an array of doubles of size 5.
    double *arrayPtr = nullptr;
    arrayPtr = new double[SIZE];
    
    // For testing, uncomment this:
    // arrayPtr = getRandomArray(); // Test array

    // ...and comment out the next line:
    populateArray(arrayPtr);
    outputArray(arrayPtr);
    cout << "Sum of values: " << sumArray(arrayPtr) << endl;
    // Clean it up. Although doesn't all the dynamic memory get deleted when the program ends?
    delete[] arrayPtr;
    return 0;
}

/**
 * Generate a random array
 */
double *getRandomArray()
{
    double *arr = nullptr;
    arr = new double[SIZE];
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % (MAX - MIN + 1) + MIN;
    return arr;
}