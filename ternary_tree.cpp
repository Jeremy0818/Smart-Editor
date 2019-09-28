// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#include "ternary_tree.h"

using namespace std;

bool TSTree::find(string word) {
// this is to find if a given word is in the tree
    int length = word.size();
    if (length == 0)
        return false;
    treeNode *current_node = root;
    int current_index = 0;
    char current_char = word[current_index];

    // traverse the tree from the root to the leaf
    // once we find the word of the last index has the value
    // of terminal as, it means it can be the end of a word
    while (current_node != NULL) {
        if (current_char > current_node->letter) {
            current_node = current_node->right;
        } else if (current_char < current_node->letter) {
            current_node = current_node->left;
        } else {
            if (current_index == length - 1) {
                if (current_node->terminal == 0) {
                    return false;
                } else {
                    return true;
                }
            } else {
                current_node = current_node->mid;
                current_index++;
                current_char = word[current_index];
            }
        }
    }
    return false;
}

void TSTree::insertFirst(string word) {
// this is to insert the first word if the tree is null
    int length = word.size();
    if (length == 0)
        return;
    int current_index = 0;
    char current_char = word[current_index];
    root = new treeNode(current_char, NULL, NULL, NULL, 0);
    if (length == 1) {
        root->terminal = 1;
        return;
    }
    current_index++;
    current_char = word[current_index];
    treeNode *current_node = root;

    while (true) {
        current_node->mid = new treeNode(current_char, NULL, NULL, NULL, 0);
        if (current_index == length - 1) {
            current_node->mid->terminal = 1;
            break;
        } else {
            current_index++;
            current_char = word[current_index];
            current_node = current_node->mid;
        }
    }
}

bool TSTree::insert(string word) {
// this is to insert a new word to the tree. If the word already exists,
//    return false. Else, return true
    int length = word.size();
    // if the word is empty, return false
    if (length == 0)
        return false;
    // if the tree is null currently, set the first character as the root
    if (root == NULL) {
        insertFirst(word);
        return true;
    } else {
        // else, traverse the tree to find the place where the word
        // should insert
        int current_index = 0;
        char current_char = word[current_index];
        treeNode *current_node = root;

        // first traverse the tree until the current node becomes null
        while (current_node != NULL) {
            if (current_char > current_node->letter) {
                // when the letter is greater than the current node's letter
                if (current_node->right != NULL) {
                    current_node = current_node->right;
                } else {
                    if (current_index == length - 1) {
                        current_node->right = new treeNode(current_char, NULL,
                                                           NULL, NULL, 1);
                        return true;
                    } else {
                        current_node->right = new treeNode(current_char, NULL,
                                                           NULL, NULL, 0);
                        current_index++;
                        current_char = word[current_index];
                        current_node = current_node->right;
                        break;
                    }
                }
            } else if (current_char < current_node->letter) {
                if (current_node->left != NULL) {
                    current_node = current_node->left;
                } else {
                    if (current_index == length - 1) {
                        current_node->left = new treeNode(current_char, NULL,
                                                          NULL, NULL, 1);
                        return true;
                    } else {
                        current_node->left = new treeNode(current_char, NULL,
                                                          NULL, NULL, 0);
                        current_index++;
                        current_char = word[current_index];
                        current_node = current_node->left;
                        break;
                    }
                }
            } else {
                if (current_index == length - 1) {
                    if (current_node->terminal == 0) {
                        current_node->terminal = 1;
                        return true;
                    } else {
                        // if it already has the word, return false
                        return false;
                    }
                } else {
                    current_index++;
                    current_char = word[current_index];
                    if (current_node->mid != NULL) {
                        current_node = current_node->mid;
                    } else {
                        break;
                    }
                }
            }
        }

        // insert the remaining characters
        while (true) {
            current_node->mid = new treeNode(current_char, NULL, NULL, NULL, 0);
            if (current_index == length - 1) {
                current_node->mid->terminal = 1;
                break;
            } else {
                current_index++;
                current_char = word[current_index];
                current_node = current_node->mid;
            }
        }
        // return true to indicate that the insertion is successful
        return true;
    }
}


string TSTree::autoCompletion(string word) {
    // this is to guess a word that user may want to type with
    // a given prefix
    int length = word.size();
    if (root == NULL) {
        return "";
    } else {
        int current_index = 0;
        char current_char;
        treeNode *current_node = root;

        // traverse the tree
        while (current_node != NULL && current_index < length) {
            current_char = word[current_index];

            if (current_char > current_node->letter) {
                current_node = current_node->right;
            } else if (current_char < current_node->letter) {
                current_node = current_node->left;
            } else {
                current_index++;
                current_node = current_node->mid;
            }
        }

        // always go to the mid child until finding the closest words
        string suggestion = "";
        while (current_node != NULL) {
            char letter = current_node->letter;
            suggestion += letter;
            if (current_node->terminal) {
                break;
            }
            current_node = current_node->mid;
        }
        return suggestion;
    }
}
