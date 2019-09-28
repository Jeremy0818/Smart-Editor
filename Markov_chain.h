// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#ifndef _MARKOV_H_
#define _MARKOV_H_


#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "heap.h"


#define SPACE 32


class Markov {
public:
    void create(string file, unsigned int keyLen);

    string predict_next(string key);

private:
    string fileBuffer;

    unordered_map< string, BinaryHeap<string, int> > dictionary;

    string get_word(string str);

    void createDictionary(unsigned int kl);
};

#endif
