/**
 * Title: STD::vector
 * Description: Modify your Lab 12 code such that it uses the STD::vector rather than the STD::array.
 * Author: Nick Galvez
 * Lab: 13
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <algorithm> // for sort(), find()
#include <numeric>   // for accumulate()
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

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
 * @param string format
 * @return string
 */
string printTime(const time_t &time, const string &format = "%Y-%m-%d %H:%M:%S")
{
    char buffer[80];
    strftime(buffer, 80, format.c_str(), localtime(&time));
    return buffer;
}

/**
 * Function to read a TSV, based on the restaurant assignment
 *
 * @param string filename
 * @return vector<EnvironmentReading>
 */
vector<EnvironmentReading> readFromFile(string filename)
{
    vector<EnvironmentReading> temp;
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
        // cout << "Time: " << printTime(reading.time) << endl; // debug

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
        temp.push_back(reading);
    }
    return temp;
}

int main()
{
    // Get a new array of EnvironmentReading structs
    // Test file should be in the repo under the src directory.
    vector<EnvironmentReading> readings = readFromFile("../src/test.tsv");

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
    cout << "The array thinks it's this big: " << readings.size() << " but it's actually this big: " << readings.size() << endl;
    cout << endl;
    // Get average temperature
    // We can't use the size() method, because I've come to learn that it's impossible to resize a std::array once it's been allocated.
    // Confusing since we were able to do that with array pointers... maybe I'm missing something.
    double sumTemperature = 0;
    for (int i = 0; i < readings.size(); i++)
    {
        sumTemperature += readings[i].temperature;
    }

    cout << setprecision(3) << "Average temperature: " << sumTemperature / readings.size() << endl;

    // report starting and ending time:
    cout << "Starting time: " << printTime(readings.front().time) << endl;
    cout << "Ending time: " << printTime(readings.back().time) << endl;
    cout << endl;
    // Seach by temperature
    vector<EnvironmentReading>::iterator readingsIterator;
    cout << "Search by temperature: 80" << endl;
    double target = 80;
    readingsIterator = find_if(readings.begin(), readings.end(), [target](const EnvironmentReading &reading)
                               { return reading.temperature == target; });

    // print value of readingsIterator
    if (readingsIterator != readings.end())
    {
        cout << "Temperature " << target << " found in position " << readingsIterator - readings.begin() << endl;
        cout << "Time: " << printTime(readingsIterator->time) << endl;
        cout << "Temperature: " << readingsIterator->temperature << "F" << endl;
        cout << "Soil Moisture: " << readingsIterator->soilMoisture << endl;
        cout << "Battery: " << readingsIterator->battery << endl;
        cout << endl;
    }
    else
    {
        cout << "Temperature " << target << " was not found." << endl;
    }

    // Get the max temperature
    readingsIterator = max_element(readings.begin(), readings.end(), [](const EnvironmentReading &a, const EnvironmentReading &b)
                                   {
                                       return a.temperature < b.temperature; // Compare temperatures
                                   });
    if (readingsIterator != readings.end())
    {
        cout << "Max temperature: " << readingsIterator->temperature << "F";
        cout << " at " << printTime(readingsIterator->time, "%H:%M") << endl;
    }

    // At what time was the solar battery fully charged?
    readingsIterator = find_if(readings.begin(), readings.end(), [](const EnvironmentReading &reading)
                               { return reading.battery >= 1; });
    if (readingsIterator != readings.end())
    {
        cout << "Battery fully charged at: " << printTime(readingsIterator->time) << endl;
    }

    // Use accumulate to get the total number of hours the battery was fully charged, this is a double because we take measurements every 15 minutes
    int hoursFullyCharged = accumulate(readings.begin(), readings.end(), 0, [](int sum, const EnvironmentReading &reading)
                                       { return reading.battery >= 1 ? sum + 1 : sum; });
    // Try to find the start index and end index of the fully charged battery
    size_t timeStartIndex = distance(readings.begin(), readingsIterator);
    time_t endTime = readings.at(timeStartIndex + hoursFullyCharged - 1).time; // I guess we have to subtract 1, otherwise there's an out of bounds exception. 
    // Get the time difference in seconds and convert to hours
    double differenceInSeconds = difftime(endTime, readingsIterator->time) / 60 / 60;
    cout << "End time: " << printTime(endTime) << endl;
    // This is what I expected vs last night's output.
    cout << setprecision(3) << "Battery was fully charged for about " << differenceInSeconds << " hours." << endl;
}