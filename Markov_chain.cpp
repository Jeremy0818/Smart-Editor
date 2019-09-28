// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#include "Markov_chain.h"

using namespace std;


void Markov::create(string file, unsigned int keyLen) {
    /*
    This function will create the whole Markov chain by reading the training text file
    with the inquired key length (number of string as a key). To do this, it will call
    the function createDictionary after reading all the text in the file and the file
    is not empty.
    Argument:
        file: the training text file name
        keyLen: number of string to be as a key
    */
    ifstream f(file.c_str(), ios_base::in);
    fileBuffer = string((istreambuf_iterator<char>(f)),
                        istreambuf_iterator<char>());
    f.close();
    if (fileBuffer.length() < 1) return;
    createDictionary(keyLen);
}

string Markov::predict_next(string key) {
    /*
    This function weill get the maximum frequency that appear behind the two string (key)
    by getting the heap of that key and get the max as the predicted next word.
    Argument:
        key: the two string
    return:
        astring of word that appear next
    */
    BinaryHeap<string, int> heap = dictionary[key];
    if (heap.size() == 0)
        return "";
    return heap.max().first;
}


string Markov::get_word(string str) {
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


void Markov::createDictionary(unsigned int kl) {
    /*
    This function will get every word by separating the text file with spaces.
    Insert the new word into the dictionary if it does not exist and update the word
    if it exist. Every key will have a heap and is built to mantain the maximum at the
    root.
    Argument:
        kl: keylength of the dictionary
    */
    string w1, key;
    size_t wc = 0, pos, next;
    next = fileBuffer.find_first_not_of(SPACE, 0);
    if (next == string::npos)
        return;
    // get key with inquired number of word(s)
    while (wc < kl) {
        pos = fileBuffer.find_first_of(' ', next);
        w1 = fileBuffer.substr(next, pos - next);
        w1 = get_word(w1);
        key += w1 + " ";
        next = fileBuffer.find_first_not_of(SPACE, pos + 1);
        if (next == string::npos)
            return;
        wc++;
    }
    // remove the extra space at the end
    key = key.substr(0, key.size() - 1);
    while (true) {
        next = fileBuffer.find_first_not_of(SPACE, pos + 1);
        if (next == string::npos)
            return;
        pos = fileBuffer.find_first_of(SPACE, next);
        w1 = fileBuffer.substr(next, pos - next);
        if (w1.size() < 1)
            break;
        w1 = get_word(w1);
        // key as processed word (without upper case, number and symbol)
        int index = dictionary[key].find(w1);
        if (index >= dictionary[key].size())
            dictionary[key].insert(w1, 1);
        else
            dictionary[key].update(index);
        key = key.substr(key.find_first_of(SPACE) + 1) + " " + w1;
    }
}
