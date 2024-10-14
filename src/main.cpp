/**
 * Title: Chair Maker 3000
 * Description: Create a chair object
 * Author: Nick Galvez
 * Lab: 20
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <iomanip>

using namespace std;
const int SIZE = 3;

class Chair
{
private:
    int legs;
    double *prices;

public:
    // constructors
    Chair()
    {
        prices = new double[SIZE];
        // Get ye legs
        legs = rand() % 2 + 3;
        for (int i = 0; i < SIZE; i++)
            // Get ye prices
            prices[i] = (rand() % 90000 + 10000) / 100.0;
    }
    Chair(int l, double prices[SIZE] )
    {
        legs = l;
        for (int i = 0; i < SIZE; i++)
            this->prices[i] = prices[i];
    }

    // setters and getters
    void setLegs(int l) { legs = l; }
    int getLegs() { return legs; }

    void setPrices(double p1, double p2, double p3)
    {
        prices[0] = p1;
        prices[1] = p2;
        prices[2] = p3;
    }

    double getAveragePrices()
    {
        double sum = 0;
        for (int i = 0; i < SIZE; i++)
            sum += prices[i];
        return sum / SIZE;
    }

    void print()
    {
        cout << "CHAIR DATA - legs: " << legs << endl;
        cout << "Price history: ";
        for (int i = 0; i < SIZE; i++)
            cout << prices[i] << " ";
        cout << endl
             << "Historical avg price: " << getAveragePrices();
        cout << endl
             << endl;
    }
};

/**
 * Generate random prices
 */
void getPrices(double (&prices)[SIZE])
{
    for (int i = 0; i < SIZE; i++)
        prices[i] = (rand() % 90000 + 10000) / 100.0;
}

int main()
{
    const int MIN = 10000, MAX = 99999;
    double price = (rand() % (MAX - MIN + 1) + MIN) / (double)100;

    cout << fixed << setprecision(2);

    // creating pointer to first chair object
    double prices[SIZE];
    getPrices(prices);
    Chair *chairPtr = new Chair(4, prices);
    chairPtr->setLegs(4);
    chairPtr->print();

    //  Stool!
    Chair *livingChair = new Chair(3, prices);
    livingChair->print();
    delete livingChair;
    livingChair = nullptr;

    // creating dynamic array of chair objects
    Chair *collection = new Chair[SIZE];
    collection[0].setLegs(4);
    collection[0].setPrices(441.41, 552.52, 663.63);
    collection[1].setLegs(4);
    collection[1].setPrices(484.84, 959.59, 868.68);
    collection[2].setLegs(4);
    collection[2].setPrices(626.26, 515.15, 757.57);
    for (int i = 0; i < SIZE; i++)
        collection[i].print();

    return 0;
}