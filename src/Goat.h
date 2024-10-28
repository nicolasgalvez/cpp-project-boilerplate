// Goat.h

#ifndef GOAT_H
#define GOAT_H
#include <iostream>
using namespace std;

class Goat
{
private:
    string name;
    int age;
    string color;

public:
    Goat()
    {
        name = "";
        age = 0;
        color = "";
    }
    // Write three more constructors for the Goat class: one that has just the name as an argument; one with name and age; and the last with all parameters.
    Goat(string n) { name = n; }
    Goat(string n, int goatAge)
    {
        name = n;
        age = goatAge;
    }
    Goat(string n, int goatAge, string goatColor)
    {
        name = n;
        age = goatAge;
        color = goatColor;
    }
    // setters and getters
    void set_name(string n) { name = n; };
    string get_name() const { return name; };
    void set_age(int a) { age = a; };
    int get_age() const { return age; }
    void set_color(string c) { color = c; }
    string get_color() const { return color; }

    // write overloaded < operator for the std::list
};

#endif