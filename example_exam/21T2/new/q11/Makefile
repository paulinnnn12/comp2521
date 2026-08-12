# COMP2521 Final Exam
# printWords

CC = clang
CFLAGS = -Wall -Wvla -Werror -gdwarf-4

########################################################################

.PHONY: asan msan nosan

asan: CFLAGS += -fsanitize=address,leak,undefined
asan: all

msan: CFLAGS += -fsanitize=memory,undefined -fsanitize-memory-track-origins
msan: all

nosan: all

########################################################################

all: testTriePrintWords

testTriePrintWords: testTriePrintWords.o printWords.o Trie.o
	$(CC) $(CFLAGS) -o testTriePrintWords testTriePrintWords.o printWords.o Trie.o

testTriePrintWords.o: testTriePrintWords.c Trie.h
printWords.o: printWords.c Trie.h
Trie.o: Trie.c Trie.h

clean:
	rm -f testTriePrintWords *.o core

