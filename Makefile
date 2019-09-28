# - - - - - - - - - - - - - - - - - - - -
#   Name : Jeremy Choo, Siyuan Liu
#   ID : 1602380, 1589879
#   CMPUT 275, Winter 2019
#
#   project: Text Editor
# - - - - - - - - - - - - - - - - - - - -
CC = g++
CFLAGS = -c -Wall -O2 -std=c++11
LFLAGS = -std=c++11
PROGS = text_editor random
OBJS = ternary.o text_editor.o Editor.o Trie_Levenshtein.o Markov_chain.o

text_editor: $(OBJS)
	$(CC) $(OBJS) -o text_editor $(LFLAGS) -lncurses

text_editor.o: text_editor.cpp Editor.h Trie_Levenshtein.h Markov_chain.h
	$(CC) text_editor.cpp -o text_editor.o $(CFLAGS)

ternary.o: ternary_tree.cpp ternary_tree.h          
	$(CC) ternary_tree.cpp -o ternary.o $(CFLAGS)

Editor.o: Editor.cpp Editor.h          
	$(CC) Editor.cpp -o Editor.o $(CFLAGS)

Trie_Levenshtein.o: Trie_Levenshtein.cpp Trie_Levenshtein.h          
	$(CC) Trie_Levenshtein.cpp -o Trie_Levenshtein.o $(CFLAGS)

Markov_chain.o: Markov_chain.cpp Markov_chain.h          
	$(CC) Markov_chain.cpp -o Markov_chain.o $(CFLAGS)

random: randomize_text.cpp
	$(CC) randomize_text.cpp -o random $(LFLAGS)

.PHONY: clean
clean:
	@rm -f $(OBJS) $(PROGS)
