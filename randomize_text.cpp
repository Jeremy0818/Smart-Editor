// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <fstream>


using namespace std;

// random generator function:
int myrandom(int i) { return std::rand()%i; }


void readfile(string filename, vector<string>* myvector) {
    /*
    This function will open the text file given and store every
    line as a word into the vector and shuffle the vector so
    that the string in the vector is not with the sequence how
    it is insert.
    Argument:
        filename: the string of the text file name
        vector: reference of the vector to be used to store words
    */
    ifstream wordsFile1(filename.c_str());
    string line;
    if (wordsFile1.is_open()) {
        while (getline(wordsFile1, line)) {
            myvector->push_back(line);
        }
        wordsFile1.close();
    } else {
        cout << "Error: failed to open words file" << endl;
    }
    // shuffle the vector so that the string in the vector are random
    std::random_shuffle(myvector->begin(), myvector->end(), myrandom);
}


void write_to_file(ofstream& file, vector<string>* myvector) {
    /*
    This function will get the opened file and write the strings
    in the vector into the file.
    */
    if (file.is_open()) {
        for (auto s : *myvector)
            file << s << "\n";
    } else {
        cout << "Unable to open output file" << endl;
    }
}


int main() {
    // this is the main function
    std::srand(unsigned(std::time(0)));
    std::vector<string> myvector;

    // first shuffle the words in word1.txt
    // which is the 100 words that are most commonly used
    readfile("word1.txt", &myvector);

    // input to the final file random.txt
    ofstream file("random.txt");
    write_to_file(file, &myvector);

    // then shuffle the words in word2.txt
    // which is the 1000 words that are most commonly used
    myvector.clear();
    readfile("word2.txt", &myvector);

    // input to the final file random.txt
    write_to_file(file, &myvector);

    // then shuffle the words in word3.txt
    // which is the 3000 words that are most commonly used
    myvector.clear();
    readfile("word3.txt", &myvector);

    // input to the final file random.txt
    write_to_file(file, &myvector);

    // finally shuffle the words in words.txt
    // which is the all the words that are in linux
    myvector.clear();
    readfile("words.txt", &myvector);

    // input to the final file random.txt
    write_to_file(file, &myvector);
    file.close();

  return 0;
}
