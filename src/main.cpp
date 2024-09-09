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
#include <sstream>
#include <iomanip>

using namespace std;

/**
 * Struct to hold the color values
 *
 * @param int red
 * @param int green
 * @param int blue
 */
struct Color
{
    int red;
    int green;
    int blue;
};

/**
 * Function to set the background color
 *
 * @param Color color
 * @return void
 */
void bgColor(const Color &color)
{
    cout << "\033[48;2;" << color.red << ";" << color.green << ";" << color.blue << "m";
}

/**
 * Function to reset the colors
 *
 * @return void
 */
void resetColor()
{
    cout << "\033[0m" << "\033[49m";
}

/**
 * Function to set the text to white or black depending on the background color
 *
 * @param Color color
 * @return void
 */
void textColor(const Color &color)
{
    if (color.red < 128 && color.green < 128 && color.blue < 128)
    {
        cout << "\033[38;2;255;255;255m";
    }
    else
    {
        cout << "\033[38;2;0;0;0m";
    }
}

/**
 * Function to print a color as a swatch
 *
 * @param Color color
 */
void outputColor(const Color &color)
{
    // set ansi color that matches the current color
    bgColor(color);
    textColor(color);

    // If the color is too dark, set the text color to white
    if (color.red < 128 && color.green < 128 && color.blue < 128)
    {
        cout << "\033[38;2;255;255;255m";
    }
    else
    {
        cout << "\033[38;2;0;0;0m";
    }
    // print the color
    cout << " " << setw(7) << left << "Red:" << setw(4) << color.red;
    resetColor(); // if there was a way to pass the cout as a return, so I could something like bgReset() << endl; this might make more sense.
    cout << endl;
    textColor(color);
    bgColor(color);
    cout << " " << setw(7) << left << "Green:" << setw(4) << color.green;
    cout << "\033[49m" << endl;
    textColor(color);
    bgColor(color);
    cout << " " << setw(7) << left << "Blue:" << setw(4) << color.blue;
    // reset the color
    resetColor();

    cout << endl;
}

/**
 * Main function - prints a table of colors
 */
int main()
{
    vector<Color> Colors;
    int n = arc4random() % 25 + 25;
    Color temporary;
    bool ansiColors = false;
    bool swatch = false;

    // Start interaction
    cout << "Would you like some ANSI with your colors? (y/n): ";
    char input;
    cin >> input;
    if (input == 'y' || input == 'Y')
    {
        ansiColors = true;
    }
    if (ansiColors)
    {
        cout << "ANSI colors enabled" << endl;
        cout << "Would you like swatches instead of a table (y/n): ";
        cin >> input;
        if (input == 'y' || input == 'Y')
        {
            swatch = true;
        }
    }

    // Generate the colors
    for (int i = 0; i < n; i++)
    {
        temporary.red = arc4random() % 256;
        temporary.green = arc4random() % 256;
        temporary.blue = arc4random() % 256;
        Colors.push_back(temporary);
    }

    // Output the header
    cout << "Number of colors: " << n << endl;
    if (!swatch) {
        cout << left << " " << setw(5) << "R" << setw(5) << "G" << setw(4) << "B" << endl;
    }

    // Output the colors
    if (swatch)
    {
        for (int i = 0; i < Colors.size(); i++)
        {
            outputColor(Colors[i]);
        }
    }
    else if (ansiColors)
    {
        for (int i = 0; i < Colors.size(); i++)
        {
            // set ansi color that matches the current color
            bgColor(Colors[i]);
            // If the color is too dark, set the text color to white
            textColor(Colors[i]);
            cout << left << " " << setw(5) << Colors[i].red << setw(5) << Colors[i].green << setw(4) << Colors[i].blue;
            // reset the color and background
            cout << "\033[0m" << "\033[49m";
            cout << endl;
        }
    }
    else
    // Must be on Windows...
        for (int i = 0; i < Colors.size(); i++)
        {
            cout << left << " " << setw(5) << Colors[i].red << setw(5) << Colors[i].green << setw(4) << Colors[i].blue;
            cout << endl;
        }

    return 0;
}