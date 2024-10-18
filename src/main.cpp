/**
 * Title: Midterm 1
 * Description: 
 * Author: Nick Galvez
 * Lab: 13
 * Class: COMSC-210
 *
 */

// Fully comment each instruction in the code, explaining what's happening on that particular line. 
// I want you to convince me that you understand what's happening with every pointer and line of code.

// Additionally, write a class method every_other_element() that will: 
// output the data structure starting with the first element, 
// skip the second element, output the third, skip fourth, etc. 
// Demo this method in your code.

#include <iostream> // Include necessary libraries. In this case it's just iostream. I built and ran to make sure it compiles.
using namespace std; // Use the std namespace so we don't have to keep typing std:: before the standard library functions.

const int MIN_NR = 10,  // Sets the constant used for
MAX_NR = 99, // Sets the constant used for 
MIN_LS = 5,  // Sets the constant used for
MAX_LS = 20; // Sets the constant used for

/**
 * Create a doubly linked list class to contain the data structure and logic.
 * The naming convention for classes appears to be camelCase with a capital. CapitalCase? My favorite. I think I prefer that over snake case just a tad.
 */
class DoublyLinkedList {
    // Private methods are not accessible to the scope outside of the class.
    // In PHP there are protected methods that are accessible to child classes, but otherwise act live private. Does C++ have that?
private:
    // Create a struct to hold the data for the linked list. One thing I miss is the ablilty to pass any type to a class, but maybe there is a way to do that?
    // The name reflects the fact that a linked list is a collection or series of nodes.
    struct Node {
        // The data that the node will hold. In this case it's an integer.
        int data;
        // Pointer to the next node in the list.
        Node* prev;
        // Pointer to the previous node in the list.
        Node* next;
        // Constructor for the Node struct. It takes an integer value and two pointers to nodes. The default values for the pointers are nullptr.
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // This is the actual data that is being stored. Here is where I'm wondering if we can make this a dynamic type?
            prev = p; // The prev node, set to nullptr by default. Following it will lead to the uh, head? Which confused me. I thought it should go back to the tail...
            next = n; // Points to the next node, 
        }
    };
    // The head of the linked list. Ok, this is what confused me. In git the HEAD is the most recent commmit. but in a linked list, it's the "oldest" node.
    Node* head;
    // The tail of the linked list. This is the most recent node.
    Node* tail;
// Public methods, available outside of the class scope.
public:
    // Constructor, which accepts the two pointers as arguements. They are set to nullptr by default.
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
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

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

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

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}