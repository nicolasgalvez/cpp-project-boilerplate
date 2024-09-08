/**
 * Title: Lab 3: Restaurant Struct
 * Description: Write a program that manipulates data about restaurants and leverages struct variables.
 * Author: Nick Galvez
 * Lab: 3
 * Class: COMSC-210
 */

/**
 * Requirements:
 * Create a struct Restaurant with at least five attributes of varying data types (e.g., a string for the restaurant's address).
 * Write a function that will create a temporary struct, receive user input via the console to populate the struct's data, and returns that struct to the main program.
 * Write another function that receives a struct object as its formal parameter and outputs the struct's data in a nice, presentable format. The function is void so it returns nothing.
 * Exercise this struct by creating at least four Restaurant objects and using your functions to manipulate them.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Valdator
{
    bool isValid;
    string message;
};

struct Restaurant
{
    int rating;
    string review;
    string address;
    string name;
    char healthDeptScore;
    bool deliveryAvailable;
};

void outputRestaraunt(const Restaurant &);
Valdator validateRating(string rating);
Valdator validateReview(string review);
Valdator validateAddress(string address);
Valdator validateName(string name);
Valdator validateHealthDeptScore(string healthDeptScore);
Valdator validateDeliveryAvailable(string deliveryAvailable);
vector<Restaurant> readRestaurantsFromFile(string filename);

/**
 * Function to validate the rating
 *
 * @param int rating
 * @return Valdator
 */
Valdator validateRating(string rating)
{
    Valdator validator;
    validator.isValid = true;
    // check if rating is a number
    for (char c : rating)
    {
        if (!isdigit(c))
        {
            validator.isValid = false;
            validator.message = "Rating must be a number.";
            // cout << rating << endl;
            return validator;
        }
    }
    // convert to int
    int ratingInt = stoi(rating);
    if (ratingInt < 0 || ratingInt > 5)
    {
        validator.isValid = false;
        validator.message = "Rating must be between 0 and 5.";
    }
    return validator;
}

/**
 * Function to validate the review
 *
 * @param string review
 * @return Valdator
 */
Valdator validateReview(string review)
{
    Valdator validator;
    validator.isValid = true;
    if (review.empty())
    {
        validator.isValid = false;
        validator.message = "Review cannot be empty.";
    }
    return validator;
}

/**
 * Function to validate the address
 *
 * @param string address
 * @return Valdator
 */
Valdator validateAddress(string address)
{
    Valdator validator;
    validator.isValid = true;
    if (address.empty())
    {
        validator.isValid = false;
        validator.message = "Address cannot be empty.";
    }
    return validator;
}

/**
 * Function to validate the name
 *
 * @param string name
 * @return Valdator
 */
Valdator validateName(string name)
{
    Valdator validator;
    validator.isValid = true;
    if (name.empty())
    {
        validator.isValid = false;
        validator.message = "Name cannot be empty.";
    }
    return validator;
}

/**
 * Function to validate the health department score
 *
 * @param char healthDeptScore
 * @return Valdator
 */
Valdator validateHealthDeptScore(string healthDeptScore)
{
    Valdator validator;
    validator.isValid = true;
    // cast as char
    char healthDeptScoreChar = healthDeptScore[0];
    healthDeptScoreChar = toupper(healthDeptScoreChar);
    if (healthDeptScoreChar < 'A' || healthDeptScoreChar > 'F')
    {
        validator.isValid = false;
        validator.message = "Health Department Score must be between A and F.";
    }
    return validator;
}

/**
 * Function to validate the delivery available, must be 'Y' or 'N'
 *
 * @param bool deliveryAvailable
 * @return Valdator
 */
Valdator validateDeliveryAvailable(string deliveryAvailable)
{
    Valdator validator;
    validator.isValid = true;
    // cast as char
    char deliveryAvailableChar = deliveryAvailable[0];
    deliveryAvailableChar = toupper(deliveryAvailableChar);
    if (deliveryAvailableChar != 'Y' && deliveryAvailableChar != 'N')
    {
        validator.isValid = false;
        validator.message = "Delivery Available must be 'Y' or 'N'.";
    }
    return validator;
}

/**
 * Function to create a restaurant object from user input
 *
 * @return Restaurant
 */
Restaurant createRestaurantInteractive()
{
    // Temporary restaurant object
    Restaurant restaurant;
    // cin value. I'm not sure if there is a disadvantage to using the same variable for all input?
    string entry;
    // Seems like the console just cuts off extra characters if you enter more than one character
    char healthDeptScore;
    char deliveryAvailable;

    cout << "Enter the restaurant's name: ";
    cin.ignore();
    getline(cin, entry);
    Valdator nameValidator = validateName(entry);
    while (!nameValidator.isValid)
    {
        cout << nameValidator.message << endl;
        cout << "Enter the restaurant's name: ";
        getline(cin, entry);
        nameValidator = validateName(entry);
    }
    restaurant.name = entry;

    cout << "Enter the restaurant's rating (0-5): ";
    getline(cin, entry);
    Valdator ratingValidator = validateRating(entry);
    while (!ratingValidator.isValid)
    {
        cout << ratingValidator.message << endl;
        cout << "Enter the restaurant's rating (0-5): ";
        getline(cin, entry);
        ratingValidator = validateRating(entry);
    }
    restaurant.rating = stoi(entry);

    cout << "Enter the restaurant's review: ";
    getline(cin, entry);
    Valdator reviewValidator = validateReview(entry);
    while (!reviewValidator.isValid)
    {
        cout << reviewValidator.message << endl;
        cout << "Enter the restaurant's review: ";
        getline(cin, entry);
        reviewValidator = validateReview(entry);
    }
    restaurant.review = entry;

    cout << "Enter the restaurant's address: ";
    getline(cin, entry);
    Valdator addressValidator = validateAddress(entry);
    while (!addressValidator.isValid)
    {
        cout << addressValidator.message << endl;
        cout << "Enter the restaurant's address: ";
        getline(cin, entry);
        addressValidator = validateAddress(entry);
    }
    restaurant.address = entry;

    cout << "Enter the restaurant's health department score (A-F): ";
    cin >> entry;
    Valdator healthDeptScoreValidator = validateHealthDeptScore(entry);
    while (!healthDeptScoreValidator.isValid)
    {
        cout << healthDeptScoreValidator.message << endl;
        cout << "Enter the restaurant's health department score (A-F): ";
        cin >> entry;
        healthDeptScoreValidator = validateHealthDeptScore(entry);
    }
    restaurant.healthDeptScore = healthDeptScore;

    if (healthDeptScore == 'F' && restaurant.rating > 0)
    {
        cout << "You sure about that rating, pal? More like a ratting, am I right?" << endl;
    }

    cout << "Is delivery available? (Y/N): ";
    cin >> entry;

    deliveryAvailable = toupper(static_cast<char>(entry[0]));
    Valdator deliveryAvailableValidator = validateDeliveryAvailable(entry);
    while (!deliveryAvailableValidator.isValid)
    {
        cout << deliveryAvailableValidator.message << endl;
        cout << "Is delivery available? (Y/N): ";
        cin >> entry;
        deliveryAvailable = toupper(deliveryAvailable);
        deliveryAvailableValidator = validateDeliveryAvailable(entry);
    }
    // convert to boolean

    restaurant.deliveryAvailable = deliveryAvailable ? true : false;

    return restaurant;
}

/**
 * Function to print the restaurant object
 *
 * @param Restaurant restaurant
 */
void outputRestaraunt(const Restaurant &restaurant)
{
    cout << setw(10) << left << "Name:" << restaurant.name << endl;
    cout << setw(10) << left << "Address:" << restaurant.address << endl;
    cout << setw(10) << left << "Rating:" << restaurant.rating << endl;
    cout << setw(10) << left << "Review:" << restaurant.review << endl;
    cout << setw(10) << left << "Delivery:" << (restaurant.deliveryAvailable ? "Yes" : "No") << endl;
    cout << endl;
}

/**
 * Function to read a pipe seprerated file with one restaurant per line
 * Format: Name|Rating|Review|Address|HealthDeptScore|DeliveryAvailable
 *
 * @param string filename
 * @return vector<Restaurant>
 */
vector<Restaurant> readRestaurantsFromFile(string filename)
{
    vector<Restaurant> restaurants;
    // check for valid file
    ifstream file(filename);
    if (!file)
    {
        cout << "File not found." << endl;
        return restaurants;
    }

    string line;
    int lineCount = 0;
    // Read each line of the file
    while (getline(file, line))
    {
        lineCount++;
        // cout << "Processing line " << lineCount << endl; // Debug
        // Create a temp Restaurant object
        Restaurant restaurant;
        stringstream ss(line);
        string ratingStr, review, address, healthScore, deliveryAvailableStr;

        // Parse each field using the pipe '|' as a delimiter
        getline(ss, restaurant.name, '|');
        getline(ss, ratingStr, '|');
        getline(ss, review, '|');
        getline(ss, address, '|');
        getline(ss, healthScore, '|');
        getline(ss, deliveryAvailableStr, '|');

        // Validate each field. I dislike how I basically copied this from the interactive function.
        Valdator nameValidator = validateName(restaurant.name);
        if (!nameValidator.isValid)
        {
            cout << "Error on line " << lineCount << ": " << nameValidator.message << endl;
            continue;
        }
        Valdator addressValidator = validateAddress(address);
        if (!addressValidator.isValid)
        {
            cout << "Error on line " << lineCount << ": " << addressValidator.message << endl;
            continue;
        }
        Valdator reviewValidator = validateReview(review);
        if (!reviewValidator.isValid)
        {
            cout << "Error on line " << lineCount << ": " << reviewValidator.message << endl;
            continue;
        }
        Valdator healthDeptScoreValidator = validateHealthDeptScore(healthScore);
        if (!healthDeptScoreValidator.isValid)
        {
            cout << "Error on line " << lineCount << ": " << healthDeptScoreValidator.message << endl;
            continue;
        }
        Valdator deliveryAvailableValidator = validateDeliveryAvailable(deliveryAvailableStr);
        if (!deliveryAvailableValidator.isValid)
        {
            cout << "Error on line " << lineCount << ": " << deliveryAvailableValidator.message << endl;
            continue;
        }

        Valdator ratingValidator = validateRating(ratingStr);
        if (!ratingValidator.isValid)
        {
            cout << "Error on line " << lineCount << ": " << ratingValidator.message << endl;
            continue;
        }

        restaurant.rating = stoi(ratingStr); // Convert rating from string to int
        restaurant.review = review;
        restaurant.address = address;
        restaurant.healthDeptScore = healthScore[0];                                                 // Convert to char
        restaurant.deliveryAvailable = (deliveryAvailableStr == "Y" || deliveryAvailableStr == "y"); // Convert to boolean

        // Add to the vector of restaurants
        restaurants.push_back(restaurant);
    }

    return restaurants;
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
    vector<Restaurant> restaurants;

    // Test file:
    // restaurants = readRestaurantsFromFile("test.csv"); // Doesn't exist, should output "File not found."
    // restaurants = readRestaurantsFromFile("../src/test.csv"); // Does exist, should output the contents of the file
    // If a file is provided, read the file and output the contents
    if (argc > 1)
    {
        cout << "Reading file: " << argv[1] << endl;

        // If I specify a binary file, for some reason the validator for rating doesn't work, and stoi will throw an exception
        try
        {
            restaurants = readRestaurantsFromFile(argv[1]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Unable to parse file. Got error: " << e.what() << endl;
        }
    }
    // If no file is provided, prompt the user to enter data for a restaurant object
    else
    {
        while (true)
        {
            cout << "Would you like to enter a restaurant? (Y/N): ";
            char entry;
            cin >> entry;
            if (entry == 'N' || entry == 'n')
            {
                break;
            }
            restaurants.push_back(createRestaurantInteractive());
        }
    }
    if (restaurants.size() == 0)
    {
        cout << endl
             << "No restaurants to display." << endl;
        return 0;
    }
    else
    {
        cout << endl
             << "Restaurants:" << endl;
        cout << setfill('-') << setw(20) << "" << endl
             << endl
             << setfill(' ');
    }
    for (Restaurant restaurant : restaurants)
    {
        outputRestaraunt(restaurant);
    }
}