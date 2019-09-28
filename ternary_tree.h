// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#ifndef _TERNARY_TREE
#define _TERNARY_TREE

#include <string>
#include <iostream>

using namespace std;

struct treeNode{
    treeNode(const char& letter, treeNode *mid = NULL, treeNode *left = NULL, treeNode *right = NULL, int terminal = 0) {
        this->mid = mid;
        this->left = left;
        this->right = right;
        this->letter = letter;
        // terminal indicates whether this character can be the last index of a word
        this->terminal = terminal;
    }
    
    char letter;
    treeNode *left, *right, *mid;
    int terminal;
};

class TSTree
{
public:
    TSTree() {
        root = NULL;
    }
    ~TSTree() {
        if (this->root != NULL) {
            delete this->root;
            
            this->root = NULL;

        }
    }
    
    // find if a word is in the tree
    bool find(string word);

    // insert a word
    bool insert(string word);

    // find a word with the given prefix
    string autoCompletion(string word);

private:
    treeNode *root;

    void insertFirst(string word);
};

#endif
