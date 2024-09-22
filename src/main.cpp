/**
 * Title: Pointers II
 * Description: Write a program that features a simple dynamic array of structs. The struct definition should itself include a dynamic array as well as other member variables.
 * Author: Nick Galvez
 * Lab: 11
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_EVENTS = 3, MAX_BUTTONS = 3, MAX_DURATION = 10;

/**
 * A control event is a button combination being pressed on a controller.
 *
 * @int id The ID of the event.
 * @string name The name of the event.
 * @double duration The duration the buttons are held for the event to trigger.
 * @int *buttons The buttons that are pressed for the event to trigger.
 */
struct ButtonCombo
{
    int id;
    string name;
    double duration;
    // Array of buttons, the integer corresponds to the GPIO pin on the controller.
    // In reality, they wouldn't be 1-3, but could be any number depending on the pinout of the microcontroller.
    int *buttons;

    ~ButtonCombo()
    {
        if (buttons)
            delete[] buttons;
        buttons = nullptr;
    }
};

void inputButtonCombo(ButtonCombo *, int);
void displayButtonCombo(ButtonCombo *);

int main()
{
    ButtonCombo *combo = new ButtonCombo[MAX_BUTTONS];
    // Get the button combo data. Add curly braces to keep in the habit for my day job...
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        inputButtonCombo(&combo[i], i);
    }
    // Display the button combo data
    cout << "Button combo summary:\n";
    for (int i = 0; i < MAX_EVENTS; i++)
    {
        displayButtonCombo(&combo[i]);
    }

    return 0;
}

/**
 * Input the button combo data.
 *
 * @param eventPointer Pointer to the combo event struct.
 * @param id The ID of the event, this is used to "auto increment" the ID.
 */
void inputButtonCombo(ButtonCombo *eventPointer, int id)
{
    // ID auto increments. I guess there's no way to get the size of the array pointer? At least according to stack exchange.
    cout << "Input data for Button Combo #" << id << ":\n";
    cout << "Name: ";
    getline(cin, eventPointer->name);
    // auto increment the id
    eventPointer->id = id;
    cout << "What button combination is used for this action? Type 1-3 or any other key to end button input." << endl;
    eventPointer->buttons = new int[MAX_BUTTONS];
    // get the buttons, but exit the loop if the user enters a non-integer
    int i = 0;
    while (i < MAX_BUTTONS)
    {
        cout << "Button #" << i + 1 << ": ";
        cin >> eventPointer->buttons[i];
        if (cin.fail())
        {
            cin.clear();
            // Was having issues with invalid multi-character input spilling over into the next question. This seemed to help.
            // @see https://stackoverflow.com/questions/22188867/using-cin-get-to-discard-unwanted-characters-from-the-input-stream-in-c
            // However I would like to be able to do this without having to press enter after a bad input.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Make sure we got at least one button before moving on.
            // A combo implies 2, but I see 1 button + duration as a combo, like long pressing the power button.
            if (i == 0)
            {
                cout << "No buttons entered. You must have at least 1 button for each event." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }
        if (eventPointer->buttons[i] < 1 || eventPointer->buttons[i] > 3)
        {
            cout << "Invalid button number. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // Ensure button hasn't already been used
        for (int j = 0; j < i; j++)
        {
            if (eventPointer->buttons[i] == eventPointer->buttons[j])
            {
                cout << "Button already used. Please try again" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }
        i++;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // get duration in milliseconds
    cout << "How long should the buttons be held for this action to trigger? (s): ";
    cin >> eventPointer->duration;

    // if the value is not a number, try again until a value number is entered
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number from 0 (any duration) to 10. Milliseconds are ok, use .5 for 500ms" << endl;
        cin >> eventPointer->duration;
    }

    // if the value is < 0, set it to 0
    if (eventPointer->duration < 0)
    {
        eventPointer->duration = 0;
    }
    // if the value is more than 10 seconds, set it to 10 seconds
    if (eventPointer->duration > MAX_DURATION)
    {
        eventPointer->duration = MAX_DURATION;
    }
    cin.clear();
    cin.ignore();
    cout << endl;
}

/**
 * Display the button combo data for a combo event.
 *
 * @param eventPointer Pointer to the ButtonCombo event struct.
 */
void displayButtonCombo(ButtonCombo *eventPointer)
{
    cout << "Name: " << eventPointer->name << endl;
    cout << "ID: " << eventPointer->id << endl;
    for (int i = 0; i < MAX_BUTTONS; i++)
    {
        if(eventPointer->buttons[i] == 0) {
            break;
        }
        cout << "Button #" << i + 1 << ": "
             << eventPointer->buttons[i] << endl;
    }

    // Output the duration. I don't know how to set precision without using a stringstream. I tried printf but I'm not sure how to convert the types.
    stringstream durationOutput;
    durationOutput << "Duration: "; // Why can't I do: stringstream durationOutput << "Duration: "; ?
    if (eventPointer->duration == 0)
    {
        durationOutput << "Any";
    }
    else if (eventPointer->duration == 1)
    {
        durationOutput << "1 second";
    }
    else
    {
        durationOutput << setprecision(2) << eventPointer->duration << " seconds";
    }
    cout << durationOutput.str() << endl;
    cout << endl
         << endl;
}