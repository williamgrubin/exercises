#include "../libraries.h"
using namespace std;

// since we have 26 english letters, we need 26 children per node
#define N 26

typedef struct TrieNode TrieNode;

struct TrieNode {
    // each node has N children, starting from the root and a flag to check if it's a leaf node
    char data;
    TrieNode* children[N];
    int isLeaf;
};

TrieNode* makeTrieNode(char data) {
    // allocate memory for a TrieNode
    TrieNode* node = (TrieNode*)calloc(1, sizeof(TrieNode));

    // initialize the node's children to NULL
    for(int i = 0; i < N; i++) { node->children[i] = NULL; }

    // the default case is to assume that the node being made is not a leaf node
    // this is because the node we're inserting may be the root node or a child to a leaf
    node->isLeaf = 0;
    node->data = data;

    return node;
}

// free the TrieNode sequence
void freeTrieNode(TrieNode* node) {
    // for each letter in the alphabet (leaf in the trie)
    for(int i = 0; i < N; i++) {
        // if the node (leaf)'s children are not null, free them
        if(node->children[i] != NULL) { freeTrieNode(node->children[i]); }
        else { continue; }
    }

    // finally, free the root node (leaf)
    free(node);
}

// insert a word into the trie
// ASSUMPTION: the desired word(s) for insertion only contain lowercase characters
TrieNode* trieInsert(TrieNode* root, string word) {
    // initialize a temporary copy of the root node
    TrieNode* temp = root;

    // for each letter in the word
    for(int i = 0; word[i] != '\0'; i++) {
        // get the letter's relative position in the alphabet list (subtract 97)
        int idx = (int) word[i] - 'a';

        // if there is no such child node (leaf) at this letter's index
        if (temp->children[idx] == NULL) {
            // intialize a child with that index
            temp->children[idx] = makeTrieNode(word[i]);
        }

        // move our temp down to the newly-added child (leaf node)
        temp = temp->children[idx];
    }

    // since this letter was not previously present in the trie, mark it as a leaf node
    temp->isLeaf = 1;

    return root;
}

// search for a word in the trie
int trieSearch(TrieNode* root, string& word) {
    TrieNode* temp = root;

    // for each letter in the word we're looking for
    for(int i = 0; word[i] != '\0'; i++) {
        // store its position
        int position = word[i] - 'a';

        // if there are no children under our current node with the index of this letter
        if (temp->children[position] == NULL) {
            // the word is not present in the trie
            return 0;
        }

        // move our temp to this next closest word
        temp = temp->children[position];
    }

    if(temp != NULL && temp->isLeaf == 1) { return 1; }

    return 0;
}

// prints the nodes of the trie
void triePrint(TrieNode* root) {
    // if our tree is empty, return
    if(!root) { return; }

    TrieNode* temp = root;
    printf("%c -> ", temp->data);

    // for each node
    for(int i = 0; i < N; i++) {
        // recursively print all of the nodes's children
        triePrint(temp->children[i]);
    }
}

void printSearch(TrieNode* root, string& word) {
    cout << "Searching for \"" << word << "\" in our trie..." << endl;

    if(trieSearch(root, word) == 0) { printf("The word you searched for WAS NOT found in the trie.\n"); }
    else { printf("The word you searched for WAS found in the trie!\n"); }
}
