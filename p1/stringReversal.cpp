#include "../libraries.h"
using namespace std;

string simpleStringReversal(string ourString) {
    string reversedString;
    
    for(int i = (ourString.length() - 1); i >= 0; i--) {
        reversedString += ourString[i];
    }

    return reversedString;
}

int main() {
    string ourWord;

    while(true) {
        cout << "Enter a string you'd like reversed: ";
        getline(cin, ourWord);

        cout << "Your string after being reversed: " << simpleStringReversal(ourWord) << endl;
    }

    return 0;
}
