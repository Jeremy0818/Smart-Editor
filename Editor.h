// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#ifndef _EDITOR_H
#define _EDITOR_H

#include <ncurses.h>
#include "Markov_chain.h"
#include "ternary_tree.h"
#include "Trie_Levenshtein.h"

#define TAB 9
#define ESC 27
#define SPACE 32
#define NL 10
#define ESC 27
#define SWITCH 96
#define DEL 127
#define RED 1
#define GREEN 2
#define BLUE 3


class Text_Editor {
public:
    Text_Editor();

    void process_input(WINDOW * win, int c);

private:
    bool word_valid = false;

    string curr_word = "";

    // this is the string that is part of a word for auto completion
    string suggest = "";

    // this will be the string that is predicted for the next word
    string predict = "";

    // list of all words
    vector <string> line;

    Markov m;

    TSTree dict;

    Trie theTrie;

    // list of similar word
    vector<string> result;

    // index for switching between words in result
    unsigned int index = 0;

    unsigned int component(string word, string str);

    void switch_suggession();

    void get_suggession_list(string str);

    string get_word(string str);

    void suggest_next();

    void process_line(int c);

    void print_color(WINDOW * win, const char* input, int color);

    void delete_word();

    void process_word();

    void display(WINDOW * win);

    void write_to_file(WINDOW* win);
};

#endif
