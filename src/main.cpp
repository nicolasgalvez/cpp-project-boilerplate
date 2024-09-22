/**
 * Title: STD::array
 * Description: Write a program that will exercise STD::array functions. Code a real-world simulation of something that could be simulated by an array.
 * Author: Nick Galvez
 * Lab: 12
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <algorithm> // for sort(), find()
#include <numeric>   // for accumulate()
#include <array>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int SIZE = 96;      // Weather station is polled at 15 minute intervals. Maximum of 96 readings in a day.
int globalActualSize = 0; // Actual size of the array

/**
 * EnvironmentReading struct
 * 
 * @param time_t time
 * @param double temperature
 * @param double soilMoisture
 * @param double battery
 */
struct EnvironmentReading
{
    time_t time;
    double temperature;
    double soilMoisture;
    double battery;
    ~EnvironmentReading() {}
};

/**
 * Prints the time in a human-readable format.
 *
 * @param time_t time
 * @return string
 */
string printTime(const time_t &time)
{
    // Why is time so hard? Maybe there's a better way to do this, I had to copy this from stackoverflow.
    // In PHP they finally got an STL datetime object in like 2016, and JavaScript just got one I think. Before we'd have to include moment.js in every project.
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&time));
    return buffer;
}

/**
 * Function to read a TSV, based on the restaurant assignment
 *
 * @param string filename
 * @return vector<Restaurant>
 */
array<EnvironmentReading, SIZE> readFromFile(string filename)
{
    array<EnvironmentReading, SIZE> temp;
    // check for valid file
    ifstream file(filename);
    if (!file)
    {
        cout << "File not found." << endl;
        return temp;
    }

    string line;
    int lineCount = 0;
    // get the header
    getline(file, line);
    // Read each line of the file
    while (getline(file, line))
    {

        // cout << "Processing line " << lineCount << endl; // Debug
        EnvironmentReading reading;
        stringstream ss(line);

        // Parse each field using tab as the delimiter
        // Note to self: make sure your TSV actually has tabs, and not 4 spaces. Thanks VSCode.
        string field;
        getline(ss, field, '\t');

        // I thought this would be quick and easy, but it's been like an hour. I guess I need better "time management" har har.
        string timeString = field;
        tm timeStruct = {};
        istringstream iss(timeString);
        iss >> get_time(&timeStruct, "%Y-%m-%d %H:%M:%S");
        // For some reason it's off by an hour. Daylight savings no doubt.
        timeStruct.tm_isdst = -1; // Set the daylight savings time flag to -1
        reading.time = mktime(&timeStruct);
        cout << "Time: " << printTime(reading.time) << endl; // debug

        getline(ss, field, '\t');
        reading.temperature = stod(field);
        // cout << "Temperature: " << reading.temperature << endl; // debug

        getline(ss, field, '\t');
        reading.soilMoisture = stod(field);
        // cout << "Soil Moisture: " << reading.soilMoisture << endl; // debug

        getline(ss, field, '\t');
        reading.battery = stod(field);
        // cout << "Battery: " << reading.battery << endl; // debug

        // Add the restaurant to the array
        temp[lineCount] = reading;
        lineCount++;
    }
    globalActualSize = lineCount;
    return temp;
}

int main()
{
    // Get a new array of EnvironmentReading structs
    // Test file should be in the repo under the src directory.
    array<EnvironmentReading, SIZE> readings = readFromFile("../src/test.tsv");

    // print out the first 5 readings
    cout << "First 5 readings: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "Time: " << readings[i].time << endl;
        cout << "Temperature: " << readings[i].temperature << endl;
        cout << "Soil Moisture: " << readings[i].soilMoisture << endl;
        cout << "Battery: " << readings[i].battery << endl;
        cout << endl;
    }
    cout << "The array thinks it's this big: " << readings.size() << " but it's actually this big: " << globalActualSize << endl;

    // Get average temperature
    // We can't use the size() method, because I've come to learn that it's impossible to resize a std::array once it's been allocated.
    // Confusing since we were able to do that with array pointers... maybe I'm missing something.
    double sumTemperature = 0;
    for (int i = 0; i < globalActualSize; i++)
    {
        sumTemperature += readings[i].temperature;
    }

    cout << setprecision(3) << "Average temperature: " << sumTemperature / globalActualSize << endl;

    // report starting and ending time:
    cout << "Starting time: " << printTime(readings.front().time) << endl;
    cout << "Ending time: " << printTime(readings[globalActualSize - 1].time) << endl;

    // Seach by temperature
    array<EnvironmentReading, SIZE>::iterator readingsIterator;
    cout << "Search by temperature: 80" << endl;
    double target = 80;
    // readingsIterator = find(readings.begin(), readings.end(), target); // seems like this might not work with an array of structs?
    
    // This find_if function is really cool, I didn't know you could have lambda functions in C++.
    // https://en.cppreference.com/w/cpp/algorithm/find
    // The syntax is confusing at first but once I realized it's like array.filter((target)=>{}... in JavaScript, it made sense.
    readingsIterator = find_if(readings.begin(), readings.begin() + globalActualSize, [target] (const EnvironmentReading &reading) {
        return reading.temperature == target;
    });
    
    // print value of readingsIterator
    if (readingsIterator != readings.end())
    {
        cout << "Temperature " << target << " found in position " << readingsIterator - readings.begin() << endl;
        cout << "Time: " << printTime(readingsIterator->time) << endl;
        cout << "Temperature: " << readingsIterator->temperature << "F" << endl;
        cout << "Soil Moisture: " << readingsIterator->soilMoisture << endl;
        cout << "Battery: " << readingsIterator->battery << endl;
    }
    else
    {
        cout << "Temperature " << target << " was not found." << endl;
    }

    // Get the max temperature
    readingsIterator = max_element(readings.begin(), readings.begin() + globalActualSize, [] (const EnvironmentReading &a, const EnvironmentReading &b) {
        return a.temperature < b.temperature; // Compare temperatures
    });
    if(readingsIterator != readings.begin() + globalActualSize) {
        cout << "Max temperature: " << readingsIterator->temperature << "F" << endl;
        cout << "Time: " << printTime(readingsIterator->time) << endl;
    }

    // At what time was the solar battery fully charged?
    readingsIterator = find_if(readings.begin(), readings.begin() + globalActualSize, [] (const EnvironmentReading &reading) {
        return reading.battery >= 1;
    });
    if(readingsIterator != readings.begin() + globalActualSize) {
        cout << "Battery fully charged at: " << printTime(readingsIterator->time) << endl;
    }

    // Use accumulate to get the total number of hours the battery was fully charged, this is a double because we take measurements every 15 minutes
    double hoursFullyCharged = accumulate(readings.begin(), readings.begin() + globalActualSize, 0.0, [] (double sum, const EnvironmentReading &reading) {
        return reading.battery >= 1 ? sum + 0.25 : sum;
    });
    // This is off by .25 hours. To do a proper job we probaly need to use a datetime function to calculate the actual timestamps.
    cout << setprecision(3) << "Battery was fully charged for about " << hoursFullyCharged << " hours." << endl;

    // I'll do the datetime thing tomorrow when I convert to vectors. It's << printTime(bedtime) << endl;
}