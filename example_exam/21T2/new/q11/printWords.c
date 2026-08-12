// printWords.c ... implementation of printWords function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Trie.h"


void helper(Trie t, char *word, int level) {
    if (t->isEndOfWord == true) {
        int length = level;
        printf("%.*s\n", length, word);
    }

    for (int i = 0; i < 26; i ++) {
        if (t->children[i] != NULL) {
            // record into array
            word[level] = (char) ('a' + i);
            // go deeper
            helper(t->children[i], word, level + 1);
        }
    }
}


void printWords(Trie t) {
    char *word = calloc(64, sizeof(char) * 64);
    int level = 0;
    helper(t, word, level);
    free(word);
}

