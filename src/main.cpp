/**
 * Title: Lab 1: Programming Assignment 1
 * Description: Write a program that manipulates data about restaurants and leverages struct variables.
 * Author: Nick Galvez
 * Lab: 1
 * Class: COMSC-260
 */

/**
Requirements:

DONE: Your program should have at least ten (10) different detailed comments
explaining the different parts of your program. 
DONE: Each individual comment should be, at a minimum, a sentence explaining a particular part of your code. 
You should make each comment as detailed as necessary to fully explain your
code. 
DONE: You should also number each of your comments (i.e., comment 1,
comment 2, etc.).

DONE: You should submit screenshots of at least five (5) different sample runs of
your program. 
DONE: Each sample run needs to use a different 2D array, and your
sample runs should NOT be the same as the sample runs that are used in
this write-up for the assignment. 

DONE: You should also number each of your
sample runs (i.e., sample run 1, sample run 2, etc.). Each of your sample
runs should be similar to this format:
int testArray[ROWS][COLS] = {{1, 2, 3, 4, 5},
                             {6, 7, 8, 9, 10},
                             {11, 12, 13, 14, 15},
                             {16, 17, 18, 19, 20}};
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Comment 1: Why not define ROWS here as well?

const int COLS = 5;

int getTotal(int[][COLS], int);
double getAverage(int[][COLS], int);
int getRowTotal(int[][COLS], int);
int getColumnTotal(int[][COLS], int, int);
int getHighestInRow(int[][COLS], int);
int getLowestInRow(int[][COLS], int);

/**
 * Get total value of the array elements
 *
 * @param array
 * @param rows
 * @return int
 */
int getTotal(int array[][COLS], int rows)
{
    int total = 0;
    // Comment 2: Loop over the rows and columns to get the total
    for (int i = 0; i < COLS; i++)
    {
        // call getColumnTotal() to get the total of the column
        total += getColumnTotal(array, i, rows);
    }

    return total;
}

/**
 * Returns the average of the array
 *
 * @param array
 * @param rows
 * @return double
 */
double getAverage(int array[][COLS], int rows)
{
    double average = 0;
    double total = 0;
    // Comment 3: After I did this again, I realized I could just call getTotal(). Oh well.
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            total += array[i][j];
        }
    }
    // Comment 4: I was stumped here until I remembered I have to cast the ints as doubles.
    // I didn't just return the result so I would have a place to put a breakpoint.
    average = total / static_cast<double>(rows * COLS);
    return average;
}

/**
 * Returns the total of a row
 *
 * @param array
 * @param rowToTotal
 * @return int
 */
int getRowTotal(int array[][COLS], int rowToTotal)
{
    int total = 0;
    // Comment 5: Loop over the columns to get the total
    for (int i = 0; i < COLS; i++)
    {
        total += array[rowToTotal][i];
    }

    return total;
}

/**
 * Returns the total of a column
 *
 * @param array
 * @param colToTotal
 * @param rows
 * @return int
 */
int getColumnTotal(int array[][COLS], int colToTotal, int rows)
{
    int total = 0;
    // Comment 6: Loop over the rows to get the total
    for (int i = 0; i < rows; i++)
    {
        total += array[i][colToTotal];
    }

    return total;
}

/**
 * Returns the highest value in a row
 *
 * @param array
 * @param rowToSearch
 * @return int
 */
int getHighestInRow(int array[][COLS], int rowToSearch)
{
    int highest = array[rowToSearch][0];
    // Comment 7: Loop over the columns of the specified row
    for (int i = 1; i < COLS; i++)
    {
        // Comment 8: If the current value is higher than the highest, set the highest to the current value
        if (array[rowToSearch][i] > highest)
        {
            highest = array[rowToSearch][i];
        }
    }

    return highest;
}

/**
 * Returns the lowest value in a row
 *
 * @param array
 * @param rowToSearch
 * @return int
 */
int getLowestInRow(int array[][COLS], int rowToSearch)
{
    int lowest = array[rowToSearch][0];
    // Comment 9: Just to the opposite of the getHighestInRow() function
    for (int i = 1; i < COLS; i++)
    {
        if (array[rowToSearch][i] < lowest)
        {
            lowest = array[rowToSearch][i];
        }
    }

    return lowest;
}

/**
 * Main function
 *
 */
int main()
{

    const int ROWS = 8;
    int testArray[ROWS][COLS] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25},
        {26, 27, 28, 29, 30},
        {31, 32, 33, 34, 35},
        {36, 37, 38, 39, 40}
    };

    // Comment 10: I wanted to use a 3d array of test data but it seemed like that was against the rules of the assignment.
    // Well, I actually was thinking of doing a vector of structs like I would make an object or hash array in PHP.
    // struct TestArray {
    //     int rows;
    //     int cols;
    //     int data[rows][cols];
    //     int totalOfRow;
    //     int totalOfCol;
    //     int highestInRow;
    //     int lowestInRow;`
    // };
    // Maybe that's not a good idea, I'm still getting used to C++ and what is efficient. Hence why I'm in the class!

    cout << "The total of the array elements is "
         << getTotal(testArray, ROWS)
         << endl;
    // I changed the output since the average of a single element doesn't make sense.
    cout << "The average value of the array elements is "
         << fixed << setprecision(1) // Comment: Set precision to 1 decimal place to match
         << getAverage(testArray, ROWS)
         << endl;

    cout << "The total of row 0 is "
         << getRowTotal(testArray, 0)
         << endl;

    cout << "The total of col 3 is "
         << getColumnTotal(testArray, 3, ROWS)
         << endl;

    cout << "The highest value in row 7 is "
         << getHighestInRow(testArray, 7)
         << endl;

    cout << "The lowest value in row 1 is "
         << getLowestInRow(testArray, 1)
         << endl;
    // I ran this on my macbook, I don't have a VM set up on the lappy since it belongs to my work.
    // I tried to add a try/catch block, but I guess system doesn't throw an exception if the command fails.
    system("PAUSE");
    return 0;
}