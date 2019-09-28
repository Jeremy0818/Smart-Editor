// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#ifndef _LEVENSHTEIN_H
#define _LEVENSHTEIN_H


#include <unordered_map>
#include <string>
#include <unordered_set>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdlib>

using namespace std;
/**
 * Computes the minimum Levenshtein Distance between the given word (represented as an array of Characters) and the
 * words stored in theTrie. This algorithm is modeled after Steve Hanov's blog article "Fast and Easy Levenshtein
 * distance using a Trie" and Murilo Vasconcelo's revised version in C++.
 * 
 * http://stevehanov.ca/blog/index.php?id=114
 * http://murilo.wordpress.com/2011/02/01/fast-and-easy-levenshtein-distance-using-a-trie-in-c/
 */


class TrieNode {
public:
    TrieNode(char letter);

    char letter;

    bool isWord;

    string word;

    unordered_map <char, TrieNode*> children;

    TrieNode* getChild(char letter);
};


class Trie {
public:
    Trie();

    ~Trie();

    TrieNode* root;

    int minLevDist;

    const int maxCost = 3;

    vector< pair<string, int> > result;

    void insert(string word);

    void traverseTrie(TrieNode* node, char letter, vector<char>& word, vector<int>& previousRow);

    void computeMinimumLevenshteinDistance(vector<char>& word);
}; 

#endif
