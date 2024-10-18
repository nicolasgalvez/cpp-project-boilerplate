//  COMSC-210  |  Lab 16 | Color Class with Constructors

#include <iostream>
#include <iomanip>
using namespace std;

const int WIDTH = 10;

class Color{
private: 
    int red;
    int blue;
    int green;

public:
    // constructors
    Color()                       { red = 0;blue = 0;green = 0; }
    Color(int r, int g ,int b)    { red = r;blue = b;green = g; }
    Color(int r)                  { red = r;green = 0;blue = 0; }
    Color(int r, int g)           { red = r;green = g;blue = 0; }

    // setters and getters
    int getRed() const            { return red; }
    int getBlue() const           { return blue; }
    int getGreen() const          { return green; }
    void setRed(int r)            { red = r; }
    void setBlue(int b)           { blue = b; }
    void setGreen(int g)          { green = g; }

    // other methods
    void print() const{
        cout << setw(WIDTH) << "Red: " << red << endl;
        cout << setw(WIDTH) << "Blue: " << blue << endl;
        cout << setw(WIDTH) << "Green: " << green << endl;
        cout << endl;
    }
};

int main() {
    // Default constructor
    Color color1;
    color1.setRed(255);
    color1.setBlue(100);
    color1.setGreen(30);
    color1.print();
    // Default constructor
    Color color2;
    color2.setRed(100);
    color2.setBlue(100);
    color2.setGreen(100);
    color2.print();
    // Default constructor
    Color color3;
    color3.setRed(1);
    color3.setBlue(10);
    color3.setGreen(100);
    color3.print();
    // Default constructor
    Color color4;
    color4.setRed(50);
    color4.setBlue(100);
    color4.setGreen(150);
    color4.print();
    
    // Default constructor
    Color color5;
    color5.print();
    
    // partial constructor
    Color color6(125);
    color6.print();
    
    // parameter constructor
    Color color7(1,2,3);
    color7.print();
    
    // partial constructor
    Color color8(10,11);
    color8.print();

}