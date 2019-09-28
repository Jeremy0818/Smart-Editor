# Smart-Editor
This is a group project in course CMPUT 275

Name: Jeremy Choo, Siyuan Liu
CMPUT 275 WI19

project: Text Editor

Included Files:
    * text_editor.cpp
    * Editor.h
    * Editor.cpp
    * Trie_Levenshtein.h
    * Trie_Levenshtein.cpp
    * Markov_chain.h
    * Markov_chain.cpp
    * ternary_tree.h
    * ternary_tree.cpp
    * heap.h
    * randomize_text.cpp
    * words.txt
    * word1.txt
    * word2.txt
    * word3.txt
    * random.txt
    * training txt
    * README
    * Makefile

Running Instructions:
    Before running program, you can create your own words text file and training text file.
        1. Run "make random" to create the random text file (can be momdified and use different text file but four text files are provided)
        2. Put as much text in the training text file as possible but make sure there is a space between every two word and also after the last word (otherwise the program will stuck in an infinity loop waiting for another space)

    To start the program:
        1. Run "make text_editor" to create the executable file.
        2. Run "./text_editor" to start the program.

    How to use:
        1. spelling checker
            (i) When an invalid word is entered, it will display in red, black otherwise. Press back space to delete the word.
        2. auto completion
            (i) When there is a word with the prefix the user entered, it will display the following character in blue. Press tab to get the suggested word.
        3. predict next word
            (i) When there is a predicted word, it will display in green. Press tab to get the predicted word.
        4. switching
            (i) When the user type an invalid word and press space, the program will try to get a list of similar words and replace the invalid word. If there is no similar word that have a levenshtein distance less than or equal to 3, then no option is provided, else the user can use the tilde button to switch between the words in the list.
        Note: 
        * Do not use arrow key in this program.
        * Blue and green color words are just options to complete the text, ignore them if the user does not want to use the word suggested. The cursor might seems a little weird when suggestion provided.
        * Extra function, if the user want to insert a word that is not already in the dictionary, press enter after entering the word instead of pressing space. It will automatically add the new word into the dictionary.
        * When typing in the program, one punctuation is allowed (for example . ? ! ,) as the last character of the word, other than that, it will be considered as an invalid word.

Notes and Assumptions:
    * The heap.h file is modified from the previous version of the heap.h file in assignment 2 in the course. It is modified to be a max heap instead of min heap (the root is the max and the children of the node is always smaller than or equal to the node). New functions are added to maintain the heap, which are update and find. The find function is done in O(n) and the update function is done in O(log n) as it needs to implement fix down or fix up to maintain the property.

    * The key length for the Markov chain is two string as one string by adding a space in between to be the key in the unordered map with a value of heap data structure so that it can get the most frequent word appear next of the two string. We choose two word as a key is because it is less accuracy using one word, and too difficult to predict the next word with three words as a key.

    * The program set a maximum levenshtein distance of value 3 to get the list of similar words so that it is more accurate for the user and prevent providing too many options to the user. This maximum value can be changed for the user to get more options or less options.

    * We have a text file with all the words in a random order. This is to make both the ternary search tree and trie as much balanced as possible so that when we try to insert or find a word, the running time can be approximately to log(n). Moreover, we have words with higher frequency at the top. This can make the autoCompletion() in tenary_tree.cpp more reliable since we just find a word by going straight to mid child until getting the first one when it finds the current node and it would be easier to get a word which is inserted early.


************************************************************ Extra Important ******************************************************************
    
    * We use ncurses library to create a window in the terminal for our output. When compiling the c++ file, it has to link the library (can be found in makefile). If the user haven't download this library. The user may need to download the library.
    Instruction to install the ncurses library:
        Type the command in terminal "sudo apt-get install libncurses5-dev" and it should be ready to run the program.


Reference:
    * https://rosettacode.org/wiki/Markov_chain_text_generator
    * https://stackoverflow.com/questions/4868969/implementing-a-simple-trie-for-efficient-levenshtein-distance-calculation-java
    * Youtube:
        ncurses tutorial c++
    * Wikipedia:
        Ternary Tree
    * http://www.cplusplus.com/reference/algorithm/

To improve in the future:
    1. Markov chain updating in a faster way
    2. Trie can be more space efficient
    3. Ternary tree can use Breath first search to get the nearest word
