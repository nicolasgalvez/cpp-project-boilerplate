#include <iostream>
#include <iomanip>

using namespace std;
const int SIZE = 3, MIN = 10000, MAX = 99999;

class Chair {
private:
    int legs;
    double * prices;
public:
    // constructors
    Chair() {
        prices = new double[SIZE];
        legs = rand() % 2 + 3;
        for (int i = 0; i < SIZE; i++)
            prices[i] = (rand() % (MAX-MIN+1) + MIN) / (double)100;
    }
    Chair(int l, double * p) {
        prices = new double[SIZE];
        legs = l;
        for (int i = 0; i < SIZE; i++)
            prices[i] = p[i];
    }

    // setters and getters
    void setLegs(int l)      { legs = l; }
    int getLegs()            { return legs; }

    void setPrices(double *p) { 
        for (int i = 0; i < 3; i++) 
            prices[i] = p[i];
    }

    double getAveragePrices() {
        double sum = 0;
        for (int i = 0; i < SIZE; i++)
            sum += prices[i];
        return sum / SIZE;
    }

    void print() {
        cout << "CHAIR DATA - legs: " << legs << endl;
        cout << "Price history: " ;
        for (int i = 0; i < SIZE; i++)
            cout << prices[i] << " ";
        cout << endl << "Historical avg price: " << getAveragePrices();
        cout << endl << endl;
    }
};

int main() {
    srand(time(0));
    cout << fixed << setprecision(2);

    //creating pointer to first chair object
    Chair *chairPtr = new Chair;
    double prices_tmp1[SIZE] = {121.21, 232.32, 414.14};
    chairPtr->setLegs(4);
    chairPtr->setPrices(prices_tmp1);
    chairPtr->print();

    //creating dynamic chair object with constructor
    double prices_tmp2[SIZE] = {525.25, 434.34, 252.52};
    Chair *livingChair = new Chair(3, prices_tmp2);
    livingChair->print();
    delete livingChair;
    livingChair = nullptr;

    //creating dynamic array of chair objects
    Chair *collection = new Chair[SIZE];
    for (int i = 0; i < SIZE; i++)
        collection[i].print();
    
    return 0;
}