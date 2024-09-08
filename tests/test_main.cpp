#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Example function to be tested
void runMainLogic() {
    vector<string> msg{"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    msg.push_back("This is a new line");
    for (const string &word : msg) {
        cout << word << " ";
    }
    cout << endl;
}

// Test case for the main function logic
TEST(MainFunctionTest, HandlesOutput) {
    // Redirect cout to a stringstream to capture the output
    stringstream buffer;
    streambuf *oldCout = cout.rdbuf(buffer.rdbuf());

    // Call the main function logic
    runMainLogic();

    // Restore the original cout buffer
    cout.rdbuf(oldCout);

    // Check the captured output
    string expectedOutput = "Hello C++ World from VS Code and the C++ extension! This is a new line \n";
    EXPECT_EQ(buffer.str(), expectedOutput);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
