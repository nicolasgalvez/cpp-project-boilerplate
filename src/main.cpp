/**
 * Title: Lab 4: Vector of Structs
 * Description: Write a program that will create and store a vector of structs.
 * Author: Nick Galvez
 * Lab: 4
 * Class: COMSC-210
 */

/**
 * Requirements:
 * Write a struct Color that will store the red, green, and blue hue values that represent any color.
 * Create an empty vector of type <Color> that will hold these structs.
 * Generate a random number between 25 and 50, and call that n. We will push n colors into the vector.
 * How? Inside a loop running n times, create a temporary struct, populate it with random integers, and push that temporary struct into your container.
 * At the end of your program, output a well-formatted table that uses cout manipulators for column alignment. Output the vector's contents, showing the R/G/B values for each color in the vector.
 * @see https://en.cppreference.com/w/cpp/io/manip
 * @see https://vorbrodt.blog/2019/03/21/ansi-escape-codes/
 * 
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Color
{
    int red;
    int green;
    int blue;
};


/**
 * Function to print a line of colors
 *
 * @param Color restaurant
 */
void outputRestaraunt(const Color &color)
{
    cout << setw(10) << left << "Name:" << color.red << endl;
    cout << setw(10) << left << "Address:" << color.green << endl;
    cout << setw(10) << left << "Rating:" << color.blue << endl;
    cout << endl;
}

/**
 * Main function - entry point of the program. Accepts optional path to a file as an argument.
 * If a file is provided, the program will read the file and output the contents.
 * If no file is provided, the program will prompt the user to enter data for a restaurant object.
 *
 * @param int argc
 * @return 0 for success
 */
int main(int argc, char *argv[])
{
    vector<Color> Colors;
    int n = arc4random() % 25 + 25;
    for(int i = 0; i < n; i++)
    {
        Color temp;
        temp.red = arc4random() % 256;
        temp.green = arc4random() % 256;
        temp.blue = arc4random() % 256;
        Colors.push_back(temp);
    }
    cout << "Number of colors: " << n << endl;
    cout << "R\tG\tB" << endl;
    for(int i = 0; i < Colors.size(); i++)
    {
        // set ansi color that matches the current color
        cout << "\033[48;2;" << Colors[i].red << ";" << Colors[i].green << ";" << Colors[i].blue << "m";

        // If the color is too dark, set the text color to white
        if(Colors[i].red < 128 && Colors[i].green < 128 && Colors[i].blue < 128)
        {
            cout << "\033[38;2;255;255;255m";
        }
        else
        {
            cout << "\033[38;2;0;0;0m";
        }
        // print the color
        cout << Colors[i].red << "\t" << Colors[i].green << "\t" << Colors[i].blue;
        // reset the color
        cout << "\033[0m";
        // reset the background color
        cout << "\033[49m";
        cout << endl;
    }
    return 0;
}