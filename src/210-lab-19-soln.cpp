// COMSC-210  |  Lab 19  | Abstract & Automate Lab

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>
using namespace std;

const int MAX = 5;
const int MIN = 1;
const int NUMBEROFREVIEWS = 2;

// Movie class will have 2 linklist one for review and rating
// and string for title.
class Movie {
    struct rateList {
        double rate;
        rateList * next;
    };

    struct reviewList {
        string comments;
        reviewList * next;
    };

    private:
        string movieTitle;
        rateList * rateHead = nullptr;
        reviewList * reviewHead = nullptr;

    public:
        Movie();
        Movie(string title) { movieTitle = title; }

    string getTitle() { return movieTitle; }
    void setTitle(string title) { movieTitle = title; }

    // addRate function will add a new rate to the front of the rate list.
    void addRate(double rate) {
        rateList * newRate = new rateList;
        newRate -> rate = rate;
        newRate -> next = rateHead;
        rateHead = newRate;
    }
    // addReviews will add review to the front of the review list.
    void addReviews(string review) {
        reviewList * newReview = new reviewList;
        newReview -> comments = review;
        newReview -> next = reviewHead;
        reviewHead = newReview;
    }
    // printMovie will print the title reviews and the rating
    void printMovie() {
        cout << "Movie Title: " << movieTitle << endl;
        while (reviewHead) {
            cout << "Review: " << reviewHead -> comments << endl;
            cout << "Rating: " << rateHead -> rate << endl;
            reviewHead = reviewHead -> next;
            rateHead = rateHead -> next;
        }
        cout << endl;
    }
};

double getRandom();

int main() {
    // create a vector of Movie objects
    //srand is so numbers are random each time.
    srand(time(0));
    ifstream inputFile;
    vector < Movie > movieList;
    string tempReview;

    inputFile.open("input.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    Movie movieOne("Lord of the Rings");
    Movie movieTwo("The Godfather");

    for (int i = 0; i < NUMBEROFREVIEWS; i++) {
        getline(inputFile, tempReview);
        movieOne.addReviews(tempReview);
        movieOne.addRate(getRandom());
    }
    for (int i = 0; i < NUMBEROFREVIEWS; i++) {
        getline(inputFile, tempReview);
        movieTwo.addReviews(tempReview);
        movieTwo.addRate(getRandom());
    }
    inputFile.close();
    movieList.push_back(movieOne);
    movieList.push_back(movieTwo);

    for (int i = 0; i < movieList.size(); i++) {
        movieList.at(i).printMovie();
    }

}
// Function to gererate a random double bewteen Min and Max. 
double getRandom() {
    double randomRate = rand() % ((MAX * 10) -
        (MIN * 10) + 1) + (MIN * 10);
    randomRate = randomRate / 10;
    return randomRate;
}