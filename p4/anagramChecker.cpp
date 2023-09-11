#include "../libraries.h"
#include "trie.h"
using namespace std;

TrieNode* root = makeTrieNode('\0');
/*
void interruptHandler(int signal) {
    cout << "Runtime interrupt received, freeing trie...\n";
    freeTrieNode(root);
    exit(1);
}
*/
int main() {
    /*
    struct sigaction signalInterruptHandler;
    
    signalInterruptHandler.sa_handler = interruptHandler;
    sigemptyset(&signalInterruptHandler.sa_mask);
    signalInterruptHandler.sa_flags = 0;
    sigaction(SIGINT, &signalInterruptHandler, NULL);
    */
    vector<string> wordPermutations;
    vector<string> textPermutations;

    char continuePrompt;
    bool isAnagram;

    string singleWord, arbitraryText, dictionaryWord;
    stringstream textStream;
    
    ifstream englishDictionary; englishDictionary.open("american-english");

    while(getline(englishDictionary, dictionaryWord)) {
        // for each character in the given word
        for(int i = 0; dictionaryWord[i] != '\0'; i++) {
            // if the character we're looking at is an uppercase letter
            if((dictionaryWord[i] >= 65 && dictionaryWord[i] <= 90) && dictionaryWord[i] != '\0') {
                // convert it to lowercase
                dictionaryWord[i] = tolower(dictionaryWord[i]);
                continue;
            // else if the character we're looking at isn't a letter at all
            } else if(!(dictionaryWord[i] >= 97 && dictionaryWord[i] <= 122) && dictionaryWord[i] != '\0') {
                // erase the invalid character
                dictionaryWord.erase(dictionaryWord.begin() + i);
                i--;
            }
        }

        // insert the word into the trie
        root = trieInsert(root, dictionaryWord);
        dictionaryWord.clear();
    }

    englishDictionary.close();

    /*
    triePrint(root);
    string someString = "programmer";
    printSearch(root, someString);
    */

    while(true) {
        // reset local variables
        singleWord.clear();
        arbitraryText.clear();
        wordPermutations.clear();
        textPermutations.clear();
        textStream.str("");
        textStream.clear();
        isAnagram = false;

        // continue querying the user for a word until they enter a valid word
        while(true) {
            cout << "Enter a single word for anagrammatic analysis: ";
            getline(cin, singleWord);

            if(trieSearch(root, singleWord)) { break; }

            cout << "You've entered an invalid word, please try again." << endl;
        }

        sort(singleWord.begin(), singleWord.end());
        // generate and store every possible permutation of our word
        do {
            if(trieSearch(root, singleWord)) {
                wordPermutations.push_back(singleWord);
            }
        } while(next_permutation(singleWord.begin(), singleWord.end()));

        // reset our word to its original value
        singleWord = wordPermutations[0];

        cout << "Enter the text that you'd like to compare your word against: ";
        getline(cin, arbitraryText);
        textStream << arbitraryText;

        // extract and sort all valid words from the arbitraryText field
        while(getline(textStream, arbitraryText, ' ')) {
            sort(arbitraryText.begin(), arbitraryText.end());

            do {
                if(trieSearch(root, arbitraryText)) {
                    textPermutations.push_back(arbitraryText);
                }
            } while(next_permutation(arbitraryText.begin(), arbitraryText.end()));
        }

        // compare all word permutations and text permutations to find a match
        for(auto& i : wordPermutations) {
            if(isAnagram == true) { break; }

            for(auto& j : textPermutations) {
                if(i == j && j != singleWord) {
                    cout << "Anagram detected!\n" <<
                            "Match found between word permutation \"" << i << "\" " <<
                            "and text permutation \"" << j << ".\"\n";
                    isAnagram = true;
                    break;
                }
            }
        }

        (isAnagram == true) ? cout << "TRUE" << endl : cout << "FALSE" << endl;

        cout << "Would you like to continue making comparisons? (y/n): ";
        cin >> continuePrompt;
        cin.ignore();
        if(tolower(continuePrompt) == 'n') { break; }
    }
    
    freeTrieNode(root);

    return 0;
}
