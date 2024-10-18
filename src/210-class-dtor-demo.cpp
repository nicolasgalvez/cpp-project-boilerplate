#include <iostream>
using namespace std;
 
const int MIN = 5, MAX = 15;

// simple class that dynamically allocates an array of integers
class DynamicIntArray {
private:
    int* arr; // pointer to a dynamic array of integers
    int size; // size of the array

public:
    // constructor that allocates memory for the array and initializes it
    DynamicIntArray(int s) : size(s) {
        // allocate memory for the array
        arr = new int[size]; 
        for (int i = 0; i < size; ++i)
            // initialize the array with randoms
            arr[i] = rand() % (MAX-MIN+1) + MIN; 
    }

    // destructor that deallocates the dynamically-allocated memory
    ~DynamicIntArray() {
        // deallocate the memory to prevent memory leaks
        delete[] arr; 
        cout << "Destructor called: Memory deallocated.\n";
    }

    void print() {
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
     // declarations
    srand(time(0));

    // create a dynamic array object with 10 elements
    DynamicIntArray myArray(10); 

    myArray.print(); 

    // when main() returns, myArray is destroyed, and its destructor is 
    // automatically called to deallocate memory
    return 0;
}
