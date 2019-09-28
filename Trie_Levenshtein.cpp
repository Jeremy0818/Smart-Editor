// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#include "Trie_Levenshtein.h"

using namespace std;


TrieNode::TrieNode(char letter) {
    this->isWord = false;
    this->letter = letter;
    this->word = word;
}


TrieNode* TrieNode::getChild(char letter) {
    /*
    This function will return the child node of the given letter if it exists.
    Null otherwise.
    */
    if (!children.empty()) {
        if (children.find(letter) != children.end()) {
            return children[letter];
        }
    }
    return NULL;
}


Trie::Trie() {
    this->root = new TrieNode(' ');
}

Trie::~Trie() {
    if (this->root != NULL) {
        delete this->root;
        this->root = NULL;
        result.clear();
    }
}


void Trie::insert(string word) {
    /*
    This function will insert the new word letter by letter into the Trie
    by traversing from the root to the leaf, and keep adding new TrieNode
    if there is no child for the current node.
    */
    int length = word.length();
    TrieNode* current = this->root;

    if (length == 0) {
        current->isWord = true;
    }
    for (int index = 0; index < length; index++) {
        char letter = word[index];
        TrieNode* child = current->getChild(letter);

        if (child != NULL) {
            current = child;
        } else {
            current->children[letter] =  new TrieNode(letter);
            current = current->getChild(letter);
        }
        if (index == length - 1) {
            current->isWord = true;
            current->word = word;
        }
    }
}


void Trie::traverseTrie(TrieNode* node, char letter, vector<char>& word,
                        vector<int>& previousRow) {
    /*
    This function is the recursive helper function that traverses the Trie in search of the minimum
    Levenshtein distance and store the word that has a levenshtein distance of smaler than or equal
    3 which is the maxCost into the vector named result with a pair (the word and the levenshtein
    distance).
    Argument:
        node - the current TrieNode
        letter - the current character of the current word we're working with
        word - an array representation of the current word
        previousRow - a row in the Levenshtein Distance matrix
    */
    int size = previousRow.size();
    vector<int> currentRow(size);
    currentRow[0] = previousRow[0] + 1;

    int minimumElement = currentRow[0];
    int insertCost, deleteCost, replaceCost;

    // calculate the levenshtein distance
    for (int i = 1; i < size; i++) {
        insertCost = currentRow[i - 1] + 1;
        deleteCost = previousRow[i] + 1;

        if (word[i - 1] == letter) {
            replaceCost = previousRow[i - 1];
        } else {
            replaceCost = previousRow[i - 1] + 1;
        }

        currentRow[i] = min({insertCost, deleteCost, replaceCost});

        if (currentRow[i] < minimumElement) {
            minimumElement = currentRow[i];
        }
    }

    // get the minimum distance and the word
    if (currentRow[size - 1] <= maxCost && node->isWord) {
        if (currentRow[size - 1] <= minLevDist) {
            // keep track of the smallest levenshtein distance
            minLevDist = currentRow[size - 1];
        }
        // the the word and levenshtein distance calculated
        result.push_back({node->word, currentRow[size - 1]});
    }

    if (minimumElement <= maxCost) {
        for (const auto& c : node->children) {
            traverseTrie(c.second, c.first, word, currentRow);
        }
    }
}


void Trie::computeMinimumLevenshteinDistance(vector<char>& word) {
    /*
    This function is the helper function of calculating the Levenshtein
    distance by calling the function traverseTrie and start the recursion.
    Arguement:
        word: the string that to be used to compare with all the words in Trie
    */
    // always clear the result before calculating so that the previous result
    // will not remain in the vector.
    if (!result.empty())
        result.clear();
    // get a large value from the random library
    minLevDist = RAND_MAX;
    int iWordLength = word.size();
    vector<int> currentRow(iWordLength + 1);
    // initialize the first row
    for (int i = 0; i <= iWordLength; i++) {
        currentRow[i] = i;
    }
    // start traversing the Trie
    for (const auto& c : root->children)
        traverseTrie(c.second, c.first, word, currentRow);
}
