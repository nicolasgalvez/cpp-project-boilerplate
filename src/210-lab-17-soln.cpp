//  COMSC-210  |  Lab 17 | Linked List

#include <iostream>
using namespace std;
const int SIZE = 7;

struct Node {
    float value;
    Node *next;
};

void output(Node *);

void addNodeFront(Node *&);
void deleteNode(Node *&);
void addNodeTail(Node *&);
void insertNode(Node *&);
void deleteList(Node *&);

int main() {
    Node *head = nullptr;
    int menu = 7;

    // create a linked list of size SIZE with random numbers 0-99
    for (int i = 0; i < SIZE; i++) {
        int tmp_val = rand() % 100;
        Node *newVal = new Node;
        
        // adds node at head
        if (!head) { // if this is the first node, it's the new head
            head = newVal;
            newVal->next = nullptr;
            newVal->value = tmp_val;
        }
        else { // its a second or subsequent node; place at the head
            newVal->next = head;
            newVal->value = tmp_val;
            head = newVal;
        }
    }
    output(head);

    while(menu != 0){
        cout << "What would you like to do"<<endl;
        cout << "1. Add a node to the front of the list" << endl;
        cout << "2. Add a node to the end of the list" << endl;
        cout << "3. Delete a node from the list" << endl;
        cout << "4. Insert a node into the list" << endl;
        cout << "5. Delete the entire list" << endl;
        cout << "6. Print list" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter a number: ";

        cin >> menu;

        while(menu < 0 || menu > 7){
            cout << "Please enter a valid number" << endl;
            cin >> menu;
        }
        

        if(menu==1){
            addNodeFront(head);
            output(head);
        }else if(menu==2){
            addNodeTail(head);
            output(head);
        }else if(menu==3){
            deleteNode(head);
            output(head);
        }else if(menu==4){
            insertNode(head);
            output(head);
        }else if(menu==5){
            deleteList(head);
            output(head);
        }else if(menu==6){
            output(head);
        }else if(menu==7){
            cout << "Good Bye "<<endl;
            return 0;
        }
    }
    return 0;
}

void output(Node * hd) {
    
    if (!hd) {
        cout << "Empty list.\n";
        return;
    }
    int count = 1;
    Node * current = hd;
    while (current) {
        cout << "[" << count++ << "] " << current->value << endl;
        current = current->next;
    }
    cout << endl;
}

void deleteList(Node *& hd){
    
    Node * current = hd;
    
    while (current){
        hd = current -> next;
        delete current;
        current = hd;
    }
    hd = nullptr;
}
// addNodeFront will take a pointer to a Node and add a new node to the front of the list
void addNodeFront(Node *& hd){
    
    int val;
    cout << "Enter a value to add to the front of the list: ";
    cin >> val;
    
    while(cin.fail()){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Pleasea enter a valid number: ";
        cin >> val;
    }
    
    Node * newNode = new Node;
    newNode->value = val;
    newNode->next = hd;
    hd = newNode;
}
// addNodeTail will take a pointer to a Node and add a new node to the end of the list
void addNodeTail(Node * & hd){
    
    int val;
    cout << "Enter a value to add to the end of the list: ";
    cin >> val;

    while(cin.fail()){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Pleasea enter a valid number: ";
        cin >> val;
    }
    Node * curNode = hd;
    Node * newNode = new Node;
    newNode -> value = val;
    newNode -> next = nullptr;

    if(!hd){
        hd = newNode;
        return;
    }
    
    while(curNode -> next){
        curNode = curNode->next;
    }
    curNode->next = newNode;
}
// insertNode will take a pointer to a Node and add a new node to any position in the list.
void insertNode(Node * & hd){
    float val;
    int pos;

    cout << "Enter a value to insert: ";
    cin >> val;
    while(cin.fail()){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Pleasea enter a valid number: ";
        cin >> val;
    }
    cout << "Enter a position to insert at: ";
    cin >> pos;

    while(cin.fail() || pos < 1 ){
        cout << "Invalid position" << endl;
        cin.clear();
        cin.ignore(500,'\n');
        cin >> pos;
    }

    Node * newNode = new Node;
    newNode -> value = val;
    Node * curNode = hd;
    Node * prevNode = hd;
    
    if(pos == 1){
        newNode->next =curNode;
        hd = newNode;
        return;
    }
    for(int i = 0; i < (pos-1); i++){

        if(!curNode){
            cout << "Invalid position" << endl;
            return;
        }
        
    if (i == 0)
        curNode = curNode->next;
    else {
        curNode = curNode->next;
        prevNode = prevNode->next;
    }
    }
    if(curNode){
    newNode->next = curNode;
    prevNode->next = newNode;
    }else{
        cout << "Invalid position" << endl;
    }
}
// deleteNode will take a pointer to a Node and delete anyposition in the list.
void deleteNode(Node *& hd){
    
    Node * curNode = hd;
    Node * prevNode = hd;
    int pos;
    cout << "Which node to delete? " << endl;
    cin >>pos;

    if(cin.fail() || pos < 1){
        cout << "Invalid position" << endl;
        cin.clear();
        cin.ignore(500,'\n');
        return;
    }
    if(pos == 1){
        hd = curNode->next;
        delete curNode;
        return;
    }
    for(int i =0;i < (pos-1);i++){
        if(curNode==nullptr){
            cout << "Invalid position" << endl;
            return;
        }
        if(i==0)
            curNode = curNode->next;
        else{
            curNode = curNode->next;
            prevNode = prevNode->next;
        }
    }
    if(curNode){
        prevNode -> next = curNode -> next;
        delete curNode;
        curNode = nullptr;
    }else{
        cout << "Invalid position" << endl;
    }
}