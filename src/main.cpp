/**
 * Title: 210-lab-23-starter
 * Description: Goat boy
 * Author: Nick Galvez
 * Class: COMSC-210
 *
 */

// When the store opens (i.e. in first time period), add 5 customers to the line right away.

/**
In subsequent time periods, the probability of:

A customer being helped at the beginning of the line and ordering their coffee is 40%
A new customer joining the end of the line is 60%
The customer at the end of the line deciding they don't want to wait and leaving is 20%
Any particular customer can decide they don't want to wait and leave the line: 10%
A VIP (very important person) customer with a Coffee House Gold Card gets to skip the line and go straight to the counter and order: 10%


The status reporting should look like:

A customer joins the line:

Jean joined the line
A customer leaves the line before being served:

Jean left the line
A VIP customer joins the front of the line:

Jean (VIP) joins the front of the line
A customer is served:

Jean is served
The end customer gets frustrated and leaves the line:

Jean (at the rear) left the line
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    return 0;
}