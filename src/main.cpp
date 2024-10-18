/**
 * Title: Midterm 2
 * Description: Simulate a line at a coffee shop. Your simulation should run for 20 time periods (minutes) and display the current line at the coffee shop.
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

using namespace std;

const int TIME_PERIODS = 20;
vector<string> customers;
int num_customers;

class DoublyLinkedList
{
private:
    struct Node
    {
        string data;
        bool vip = false;
        Node *prev;
        Node *next;
        Node(string val, Node *p = nullptr, Node *n = nullptr)
        {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void insert_after(string value, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }

        Node *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value)
    {
        if (!head)
            return;

        Node *temp = head;

        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp)
            return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1)
        {
            pop_front();
            return;
        }

        Node *temp = head;

        for (int i = 1; i < pos; i++)
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next)
        {
            pop_back();
            return;
        }

        Node *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v)
    {
        Node *newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << v << " joined the line." << endl;
    }

    void push_front(string v)
    {
        Node *newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front()
    {

        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head;

        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;

        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
        cout << "(at the rear) left the line." << endl;
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print()
    {
        Node *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        cout << "Resulting line: " << endl;
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse()
    {
        Node *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};
// Load the names
void loadNames()
{
    ifstream file("../src/names.txt");
    if (!file)
    {
        cout << "File not found." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        customers.push_back(line);
        num_customers++;
    }
}


// Random number generator
int probability(int prob)
{
    return rand() % prob + 1;
}

int main()
{
    DoublyLinkedList line;
    loadNames();
    cout << "Welcome to SterBooks!" << endl;
    // try catch since my new m2 mac is having issues with the debugger path
    try
    {
        // add 5 customers to the line right away
        for (int i = 0; i < 5; i++)
        {
            int prob = rand() % num_customers;
            line.push_back(customers[prob]);
        }

        line.print();

        // Start the simulation
        for (int i = 0; i < TIME_PERIODS; i++)
        {
            // A customer being helped at the beginning of the line and ordering their coffee is 40%
            if (probability(100) <= 40)
            {
                line.pop_front();
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}