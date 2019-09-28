// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <ncurses.h>
#include <vector>
#include <locale>  // std::isalnum std::locale std::tolower
#include "Editor.h"


using namespace std;

#define RED 1
#define GREEN 2
#define BLUE 3


void setup() {
    /*
    Set up for everything about the tools needed for output and color attribute.
    */
    // ncurses start
    initscr();
    noecho();
    cbreak();

    if (!has_colors()) {
        printw("This terminal does not support color");
        getch();
        return;
    }

    //start_ncurses(true, true);
    use_default_colors();
    start_color();
    init_pair(GREEN, COLOR_GREEN, -1);
    attron(COLOR_PAIR(2));
    init_pair(RED, COLOR_RED, -1);
    init_pair(BLUE, COLOR_BLUE, -1);
}


int main() {
    /*
    This is the main function of the program.
    */
    setup();

    // get screen size
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    //program start message
    WINDOW * startWindow = newwin(4, 30, yMax / 4, xMax / 4);
    box(startWindow, 0, 0);
    refresh();
    mvwprintw(startWindow, 1, 1, "Program Start...\n press any key to continue");
    wrefresh(startWindow);

    getch();
    clear();

    // create a window for output
    WINDOW * outputBox = newwin(yMax, xMax, 0, 0);

    // prpgram start
    Text_Editor Editor;
    while (true) {
        int c = getch();
        // process input every time the user input
        Editor.process_input(outputBox, c);
    }

    getch();
    attroff(COLOR_PAIR(2));
    endwin();
    return 0;
}
