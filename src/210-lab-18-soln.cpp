#include <iostream>
using namespace std;

struct Node {
    float value;
    string comments;
    Node *next;
};

void outputReviews(Node *);
Node * addHead(Node *, float, string, int);
Node * addTail(Node *, float, string, int);

int main() {
    float rvw;
    bool enterReview = false;
    char entry;
    Node * myReviews;
    int countOfReviews = 0;
    bool addAtHead;
    int choice;

    cout << "Which linked list method should we use?\n";
    cout << "\t[1] New nodes are added at the head of the linked list\n";
    cout << "\t[2] New nodes are added at the tail of the linked list\n";
    cout << "\tChoice: ";
    cin >> choice;
    while (choice < 1 or choice > 2) {
        cout << "\t> ERROR: 1 or 2 only: ";
        cin >> choice;
    }
    addAtHead = choice == 1? true : false;

    do {
        cout << "Enter review rating 0-5: ";
        cin >> rvw;
        countOfReviews++;
        while (rvw < 0 or rvw > 5) {
            cout << "\t> ERROR: reviews must be between 0-5: ";
            cin >> rvw;
        }
        cout << "Enter review comments: ";
        string cmts;
        cin.ignore();
        getline(cin, cmts);

        if (addAtHead)
            myReviews = addHead(myReviews, rvw, cmts, countOfReviews);
        else
            myReviews = addTail(myReviews, rvw, cmts, countOfReviews);

        cout << "Enter another review? Y/N: ";
        cin >> entry;
        entry = tolower(entry);
        while (entry != 'y' and entry != 'n') {
            cout << "\t> ERROR: Y/N only: ";
            cin >> entry;
            entry = tolower(entry);
        }
        if (entry == 'y') enterReview = true;
        else enterReview = false;

    } while (enterReview);

    outputReviews(myReviews);
}

Node * addTail(Node * allreviews, float val, string cmt, int count) {
    Node * newRvw = new Node;
    Node * last;
    // find and set last
    Node *current = allreviews;
    if (count != 1) {
        while (current != nullptr) {
            last = current;
            current = current->next;
        }
    }
    else {
        allreviews = newRvw;
        last = newRvw;
    }
    newRvw->value = val;
    newRvw->comments = cmt;
    newRvw->next = nullptr;
    if (count != 1)
        last->next = newRvw;
    return allreviews;
}

Node * addHead(Node * allreviews, float val, string cmt, int count) {
    Node * newRvw = new Node;
    if (count == 1) {
        allreviews = newRvw;
        newRvw->next = nullptr;
        newRvw->value = val;
        newRvw->comments = cmt;
    }
    else {
        newRvw->next = allreviews;
        newRvw->value = val;
        newRvw->comments = cmt;
        allreviews = newRvw;
    }
    return allreviews;
}

void outputReviews(Node * allReviews) {
    Node * current = allReviews;
    cout << "Outputting all reviews:\n";
    int count = 1;
    double sum = 0.0;
    while (current != nullptr) {
        sum += current->value;
        cout << "\t> Review #" << count++ << ": " << current->value << ": "
             << current->comments << endl;
        current = current->next;
    }
    double avg = sum / count;
    cout << "\t> Average: " << avg << endl;
}