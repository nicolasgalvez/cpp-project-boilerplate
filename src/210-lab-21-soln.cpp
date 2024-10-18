#include <iostream>
using namespace std;

const int SIZE = 15, MAX_AGE = 20;

class Goat {
private:
    string name, color;
    int age;
    string names[SIZE] = {"Kid", "Baby", "Teen", "Adult", "Senior",
        "Grown", "Mature", "Old", "Veteran", "Elder", "Ancient",
        "Immortal", "Legendary", "Godlike", "God"};
    string colors[SIZE] = {"Black", "White", "Brown", "Red", "Blue",
        "Green", "Purple", "Yellow", "Orange", "Pink", "Gray",
        "Silver", "Gold", "Mauve", "Bronze"};
    
public:
    // constructors
    Goat() { 
        name = names[rand() % SIZE]; 
        color = colors[rand() % SIZE];
        age = rand() % MAX_AGE; 
    }
    Goat(string n, string c, int a) 
        { name = n; color = c; age = a; }
    
    // setters and getters
    void setName(string n)    { name = n;     }
    void setAge(int a)        { age = a;      }
    void setColor(string c)   { color = c;    }
    string getName()          { return name;  }
    int getAge()              { return age;   }
    string getColor()         { return color; }
};

// A node of the doubly linked list
struct Node {
    Goat goat;
    Node* next;
    Node* prev;

    // Constructor
    Node(Goat gt) { goat = gt; next = nullptr; prev = nullptr; }
};

// Class to represent a doubly linked list
class DoublyLinkedList {
public:
    Node* head; // Head of the list

    // Constructor
    DoublyLinkedList() { head = nullptr; }

    // Function to insert a new node at the end of the list
    void append(Goat gt) {
        Node* new_node = new Node(gt);

        if (head == nullptr) { // If the list is empty
            head = new_node;
            return;
        }

        Node* last = head;
        while (last->next != nullptr) { // Traverse to the last node
            last = last->next;
        }

        last->next = new_node;
        new_node->prev = last;
    }

    // Function to delete a node from the list
    void deleteNode(Node* del_node) {
        if (head == nullptr || del_node == nullptr) {
            return; // List is empty or del_node is nullptr
        }

        // If node to be deleted is the head node
        if (head == del_node) {
            head = del_node->next;
        }

        // Change next only if node to be deleted is NOT the last node
        if (del_node->next != nullptr) {
            del_node->next->prev = del_node->prev;
        }

        // Change prev only if node to be deleted is NOT the first node
        if (del_node->prev != nullptr) {
            del_node->prev->next = del_node->next;
        }

        delete del_node; // Finally, free the memory occupied by del_node
    }

    // Function to delete the entire list
    void deleteList() {
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }

        head = nullptr; // Change head to nullptr
    }

    // Function to print the list from the beginning
    void displayForward() {
        Node* temp = head;
        
        cout << "Forward: ";
        if (!temp) {
            cout << "List is empty" << endl;
            return;
        }
        else
            cout << endl;
        
        while (temp != nullptr) {
            cout << "\t" << temp->goat.getName() 
                 << " (" << temp->goat.getColor() << ", "
                 << temp->goat.getAge() << ")\n";
            temp = temp->next;
        }
        cout << endl;
    }

    // Function to print the list in reverse order
    void displayBackward() {
        Node* temp = head;
        cout << "Backward: ";
        if (!temp) {
            cout << "List is empty.\n";
            return;
        }
        else
            cout << endl;

        // Go to the last node
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        // Traverse backward
        while (temp != nullptr) {
            cout << "\t" << temp->goat.getName() 
                 << " (" << temp->goat.getColor() << ", "
                 << temp->goat.getAge() << ")\n";
            temp = temp->prev;
        }
        cout << endl;
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList dll;

    // Append a random number of goats to the list
    int num_goats = rand() % 15 + 4;
    for (int i = 0; i < num_goats; i++)
        dll.append(Goat());

    // Display the lists forward & backward
    dll.displayForward();
    dll.displayBackward();

    // Delete the list, and verify both forward & backward
    dll.deleteList();
    dll.displayForward();
    dll.displayBackward();
    
    return 0;
}
