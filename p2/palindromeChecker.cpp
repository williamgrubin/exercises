#include "../libraries.h"

bool simplePalindromeChecker(string ourString) {
    // O(n/2)
    for(int i = 0; i < (ourString.length() / 2); i++) {
        // cout << "ourString[i]: " << ourString[i] << "\nourString[(ourString.length() - 1) - i]: " << ourString[(ourString.length() - 1) - i] << endl;
        if(ourString[i] != ourString[(ourString.length() - 1) - i]) { return false; }
    }

    return true;
}

int main() {
    string userInput;
    
    while(true) {
        cout << "Enter a string to determine if it's a palindrome: ";
        getline(cin, userInput);

        (simplePalindromeChecker(userInput) == true) ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    }

    return 0;
}
