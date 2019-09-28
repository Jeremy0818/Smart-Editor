// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#include "Editor.h"

using namespace std;


Text_Editor::Text_Editor() {
    /*
    This is th constructor which will initialize the Markov chain for predict next word
    ,the Trie for calculating levenshtein distance to get a list of similar word as well
    as Ternary tree as a dictionary to check if the word is valid or to complete auto
    completion.
    The Markov chain is created by inserting the training text file while the Trie and
    Ternary tree are both created by inserting words from the random text file which
    contain all the words with random sequence (not sorted alphabetically).
    */
    // initiate Markov chain
    m.create(string("training.txt"), 2);
    // inititate ternary tree and Trie
    ifstream wordsFile("random.txt");
    string line;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, line)) {
            // go trough ever line which has a only one word
            string word = get_word(line);
            dict.insert(word);
            theTrie.insert(word);
        }
        wordsFile.close();
    } else {
        cout << "Error: failed to open words file" << endl;
    }
}


void Text_Editor::process_input(WINDOW * win, int c) {
    /*
    This is the main member funciton for Editor. It will process the input every time
    a character is input by the user and then perform some algorithm before displaying.
    Argument:
        win: the window pointer for displaying output
        c: the ascii number of the character input
    */
    if (c != SWITCH) {
        // clear the similar word list every time input a new charater
        // other than the switch button
        if (!this->result.empty())
            this->result.clear();
    }
    if (c == SPACE || c == NL) {
        // handle every word and every line
        process_line(c);
    } else if (c == DEL) {
        // handle backspace
        delete_word();
        predict = "";
    } else if (c == TAB) {
        // handle auto completion
        if (suggest.length() > 0) {
            curr_word += suggest;
            process_line(SPACE);
            suggest = "";
        } else if (predict.length() > 0) {
            curr_word = predict;
            process_line(SPACE);
            predict = "";
        }
        suggest_next();
    } else if (c == SWITCH) {
        // when switching between words in similar word list
        switch_suggession();
    } else if (c == ESC) {
        // save all the text into a file
        write_to_file(win);
    } else {
        curr_word += c;
        predict = "";
    }
    process_word();
    display(win);
}


unsigned int Text_Editor::component(string word, string str) {
    /*
    This function will count the number of character that string str has is / are
    in the string word. String str is the invalid string that the user insert and
    the string word is the string that is valid.
    Arguement:
        word: valid string to be check if it has all character that str has
        str: invalid string that is input by the user
    return:
        count: number of character that in str appear in word
    */
    int count = 0;
    for (unsigned int i = 0 ; i < str.size() ; i++) {
        if (word.find(str[i]) != string::npos)
            count++;
    }
    return count;
}


void Text_Editor::switch_suggession() {
    /*
    This function will switch the invalid word to the similar words in a cycle.
    */
    if (this->result.size() > 0) {
        line[line.size() - 1] = this->result[index];
        index++;
        if (index == this->result.size())
            index = 0;
    }
}


void Text_Editor::get_suggession_list(string str) {
    /*
    This function will perform the levenshein distance algorithm to obtain a list of
    similar words when the string input by the user (str) is invalid and store the list
    into the vector named result.
    Argument:
        str: the invalid string to be used to find a similar word list
    */
    vector<char> v;
    copy(str.begin(), str.end(), back_inserter(v));

    theTrie.computeMinimumLevenshteinDistance(v);

    // first clear the result before getting the new similar word list
    if (!this->result.empty())
        this->result.clear();
    for (auto s : theTrie.result) {
        // get only word that has the minimum distance or
        // word that has all character in str
        if (s.second <= theTrie.minLevDist)
            this->result.push_back(s.first);
        else if (component(s.first, str) == str.size() &&
                 s.first.size() == str.size())
            this->result.insert(result.begin(), s.first);
    }
}


string Text_Editor::get_word(string str) {
    /*
    This funtion is to filter the string so that they are all lowercase and no character
    other than alphabets and numbers. However, no more than one symbol is allowed and the
    only symbol can only appear at the end of the string.
    Agument:
        str: string to be processed
    return:
        str new string that is processed
    */
    locale loc;
    string alpha;
    string::size_type i = 0;
    while (i < str.length()) {
        alpha.push_back(tolower(str[i], loc));
        i++;
    }
    // handle symbol (eg. . ! ?)
    char last_char = str[str.length() - 1];
    if (!isalnum(last_char)) {
        if (last_char == '.' || last_char == '!' ||
            last_char == '?' || last_char == ',')
            alpha.pop_back();
    }
    return alpha;
}

void Text_Editor::suggest_next() {
    /*
    This function will use the last two words input by the user as a key and call
    the function predict next from the Markov chain to predict the next word. It
    needs atleast two word in the line vector and the words have to be both not
    empty string. If there is a result, the string suggestion will store the result.
    */
    string key = "";
    if (line.size() > 1) {
        string w1 = get_word(line[line.size() - 2]);
        string w2 = get_word(line.back());
        if (w1.size() > 0 && w2.size() > 0) {
            // make sure both word are not empty
            key = w1 + " " + w2;
            predict = m.predict_next(key);
        } else {
            predict = "";
        }
    }
}

void Text_Editor::process_line(int c) {
    /*
    This function will store the current word in vector line and make the current
    word empty to store another word. Keep doing this when the user press space to
    get the input word by word. If the user press enter, store the current word too
    but also the new line feed so that when displaying it will display the enter.
    Argument:
        c: the ascii number of the character (space or enter when calling this function)
    */
    word_valid = false;
    string word = get_word(curr_word);
    if (dict.find(word))
        word_valid = true;
    if (c == NL) {
        if (curr_word.length() > 0)
            line.push_back(curr_word);
        if (word_valid || curr_word.size() == 0) {
            line.push_back("\n");
        } else {
            dict.insert(word);
            theTrie.insert(word);
        }
    } else {
        if (!word_valid && curr_word.size() > 0) {
            get_suggession_list(get_word(curr_word));
            this->result.push_back(curr_word);
            index = 0;
            curr_word = this->result[index];
            index++;
        }
        line.push_back(curr_word);
        if (curr_word.size() == word.size())
            suggest_next();
    }
    curr_word = "";
}

void Text_Editor::print_color(WINDOW * win, const char* input, int color) {
    /*
    This function will print the char pointer in the color inquired
    and refresh the window.
    Argument:
        win: the window pointer use to print the output
        input: char pointer that stored the word to be printed
        color: an integer that indicate the color
    */
    wattron(win, COLOR_PAIR(color));
    wprintw(win, input);
    wattroff(win, COLOR_PAIR(color));
    wrefresh(win);
}

void Text_Editor::delete_word() {
    /*
    This function will handle deletion when the user press back space.
    There are a few cases:
    1. when current word is not empty, just pop_back to delete the last character
    2. when curent word is empty, let the last word in vector line be the current word
    3. if current word and vector line are both empty, do nothing.
    */
    if (curr_word.length() > 0) {
        curr_word.pop_back();
    } else {
        if (!line.empty()) {
            // make sure new line character is handle properly
            // so that the user do not need to delete twice
            // to go back to the previous line
            if (line.back() == "\n") {
                line.pop_back();
                if (line.size() > 0 && line.back() != "\n") {
                    curr_word = line.back();
                    line.pop_back();
                } else {
                    curr_word = "";
                }
            } else {
                curr_word = line.back();
                line.pop_back();
            }
        }
    }
}

void Text_Editor::process_word() {
    /*
    This function will first check whether the current word valid and do
    the auto completion.
    */
    word_valid = false;
    suggest = "";
    string word = get_word(curr_word);
    if (dict.find(word)) {
        word_valid = true;
    }
    // get auto complete word
    if (word.length() > 0 && curr_word != "\n")
        if (curr_word.size() == word.size())
            suggest = dict.autoCompletion(word);
}

void Text_Editor::display(WINDOW * win) {
    /*
    This function will handle all displaying work.
    It will first display all the words that is stored in vector line
    and then the current word. After that it will display the suggestion
    for auto completion or the predicted next word.
    Color:
    if the word is valid: black
    if the word is invalid: red
    suggestion (auto completion): blue
    predicted next word: green
    */
    const char* space = " ";
    wclear(win);
    const char * input;
    // display the line of words that were entered
    for (auto const& w : line) {
        input = w.c_str();
        if (w != "\n" && !dict.find(get_word(w))) {
            print_color(win, input, RED);
        } else {
            wprintw(win, input);
            wrefresh(win);
        }
        if (w != "\n") {
            wprintw(win, space);
            wrefresh(win);
        }
    }

    // display the current word
    input = curr_word.c_str();
    if (!word_valid && curr_word.length() > 0) {
        print_color(win, input, RED);
    } else {
        wprintw(win, input);
        wrefresh(win);
    }
    // display auto completion
    if (suggest.length() > 0) {
        print_color(win, (suggest).c_str(), BLUE);
    } else if (predict.length() > 0) {
        print_color(win, predict.c_str(), GREEN);
    }
}

void Text_Editor::write_to_file(WINDOW* win) {
    /*
    This function will let the user to choose to save the text into a file.
    The file is fixed to be named "out.txt".
    Argument:
        win: the window pointer to display the output
    */
    // get screen size
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    // print warning message to make sure the user really want to save it
    mvwprintw(win, yMax / 4, xMax / 4, " ------------------------------ ");
    mvwprintw(win, yMax / 4 + 1, xMax / 4, " - Are you sure to save this? - ");
    mvwprintw(win, yMax / 4 + 2, xMax / 4, " -  (press enter to save it)  - ");
    mvwprintw(win, yMax / 4 + 3, xMax / 4, " -  (press any key to cancel) - ");
    mvwprintw(win, yMax / 4 + 4, xMax / 4, " ------------------------------ ");
    wrefresh(win);
    int c = getch();
    // write the text to the file named "out.txt"
    // if the file has some text in it, it will overwrite everything
    if (c == NL) {
        ofstream file("out.txt");
        if (file.is_open()) {
            for (unsigned int i = 0 ; i < line.size() ; i++) {
                if (i > 0) {
                    if (line[i - 1] != "\n" && line[i] != "\n")
                        file << " ";
                }
                file << line[i];
            }
            if (line.size() > 0) {
                if (line[line.size() - 1] != "\n")
                    file << " " << curr_word;
                else
                    file << curr_word;
            } else {
                file << curr_word;
            }
            file.close();
        } else {
            cout << "Unable to open output file" << endl;
        }
    }
}
