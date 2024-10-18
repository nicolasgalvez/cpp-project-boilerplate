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
    // Method to insert a node after another one, takes the value, and the position of the node to target.
    void insert_after(int value, int position) {
        // Check the position. I guess this could happen if you don't have proper range checking when traversing in reverse.
        if (position < 0) {
            // Echo an error message, new line.
            cout << "Position must be >= 0." << endl;
            return; // Does what it says on the box.
        } // Ends the if statement.
        // Creates a pointer to a new object instance of type Node, and passes the value to the constructor.
        Node* newNode = new Node(value);
        // If there is no head...
        if (!head) {
            // This must be new. Point both the head and tail to the new node.
            head = tail = newNode;
            return; // return to the caller
        } // Comment *every* line? :-)
        // Create a temp pointer to head.
        Node* temp = head;
        // Start a loop that runs until the target is reached, or until temp returns a falsy value.
        for (int i = 0; i < position && temp; ++i)
        // point to the next node
            temp = temp->next;
        // If there is no next node, we've reached the end before reaching the target.
        if (!temp) {
            // echo error and use a different type of new line. It's the "endl the line" for \n
            cout << "Position exceeds list size. Node not inserted.\n";
            // Get that thing outta here. Delete the temp node
            delete newNode;
            return; // goto 10
        }
        // Now that temp is pointing to the correct position, copy to the new node so it will be pointing to the next item as well.
        newNode->next = temp->next;
        // Point to temp, which is currently at the existing item.
        newNode->prev = temp;
        // If temp next is truthy...
        if (temp->next)
            temp->next->prev = newNode; // Point the temp pointer to uh ok this part always confused me too. I'll see what the rest of the program does.
        else // if falsy
            tail = newNode; // we must be at the end of the line, so point the tail at the new node.
        temp->next = newNode; // set the pointer to the new node and now it's linked into the chain.
    }
    // Delete a node from the linked list. Takes a value to search for.
    void delete_val(int value) {
        if (!head) return; // This list doesn't have anything in it yet. Return.
        // Create a temp pointer to head
        Node* temp = head;
        // traverse the nodes until value is found.
        while (temp && temp->data != value) // move the pointer to the next item until a match is found or temp is false
            temp = temp->next;
        // got to the end and no match.
        if (!temp) return; // nothing to do.
        // If there is a previous node...
        if (temp->prev)
            temp->prev->next = temp->next; // Point the previous node to the node after the node with the matching value.
        else // if no previous node, 
            head = temp->next; // we're at the head, so point to it.

        if (temp->next) // Check that we have a node next
            temp->next->prev = temp->prev; // Set the next node's previous pointer to the one before the node with the matched value.
        else // there isn't a next node
            tail = temp->prev; // we must be at the tail!
        // At this point the target node is cut out of the list. nothing points to it.
        delete temp; // Now we can get the target node outta here.
        // void, so no return.
        // What happens if there are multiple nodes with the same value?
    }
    // method for deleting by position instead of value.
    void delete_pos(int pos) { // void, so no return.
        if (!head) { // This list has no values, 
            cout << "List is empty." << endl; // let the user know, use the original line break.
            return; // do not return a value.
        } 
    
        if (pos == 1) { // If the position is 1,
            pop_front(); // call the function to pop it.
            return; // return nothing.
        }
    
        Node* temp = head; // create a temp pointer
    
        for (int i = 1; i < pos; i++){ // Traverse the list until you get to the target item.
            if (!temp) { // exit if temp is falsy, we've gone too far
                cout << "Position doesn't exist." << endl; // notify
                return; // exit method
            }
            else // otherwise
                temp = temp->next; // go to the next item
        }
        if (!temp) { // we should be at the position now. If temp is not a Node though...
            cout << "Position doesn't exist." << endl; // return
            return; // and don't return a value
        }
        
        if (!temp->next) { // If temp is pointing to the uh tail... just pop the last item.
            pop_back(); // call the function to return the tail
            return; // And return
        }
    
        Node* tempPrev = temp->prev; // make temp previous pointer, assign temp-prev value
        tempPrev->next = temp->next; // and make this temp
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