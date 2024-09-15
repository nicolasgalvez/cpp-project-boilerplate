/**
 * Title: Lab 5: Pointerify!
 * Description: This code uses reference variables. Cast the "Pointerify" spell on it by rewriting the code such that it uses pointers.
 * Author: Nick Galvez
 * Lab: 5
 * Class: COMSC-210
 *
 */

#include <iostream>

using namespace std;

void swap(int *, int *, int *); // Change to pointers instead of references.

int main()
{
    int x = 5, y = 10, sum;

    cout << "x = " << x << "  | y = " << y << endl;

    cout << "Swapping...\n";
    swap(&x, &y, &sum);
    cout << "x = " << x << " | y = " << y << endl;
    cout << "sum = " << sum << endl;
    return 0;
}
/**
 * Swaps two numbers and provides a sum.
 */
void swap(int *a, int *b, int *sum)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    *sum = *a + *b;
}