//      COMSC-210  |  Fall 2024
//  Prof Dietrich  |  Lab 6 Solution

#include <iostream>
using namespace std;

void enterArrayData(double *);
void outputArrayData(double *);
double sumArray(double *);
const int SIZE = 5;

int main() {
    // declarations
    double *elem = new double[SIZE];

    // populate array via fx()
    enterArrayData(elem);

    // display array via fx()
    cout << "Outputting array elements: ";
    outputArrayData(elem);

    // sum & display via fx()
    cout << "Sum of values: " << sumArray(elem) << endl;

    // housekeeping
    delete [] elem;
    return 0;
}

// parameters: double array
// returns:    void
void enterArrayData(double *arr) {
    cout << "Data entry for the array:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "\t> Element #" << i << ": ";
        cin >> *arr++;
    }
    cout << "Data entry complete.\n";
}

// parameters: double array
// returns:    void
void outputArrayData(double *arr) {
    for (int i = 0; i < SIZE; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// parameters: double array
// returns:    integer (sum)
double sumArray(double *arr) {
    double sum = 0.0;
    for (int i = 0; i < SIZE; i++)
        sum += arr[i];
    return sum;
}