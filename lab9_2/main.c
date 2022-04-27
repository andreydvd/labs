#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void addWordlist(wordlist_t **wordlist, char *source){
    while (*wordlist){
        int cmp = strcmp(source, (*wordlist)->source);
        if (cmp == 0){
            (*wordlist)->count++;
            return;
        }
        if (cmp < 1){
            wordlist = &(*wordlist)->left;
        }
        else{
            wordlist = &(*wordlist)->right;
        }
    }
    *wordlist = (wordlist_t*)malloc(sizeof(wordlist_t));
    if (!*wordlist) {
        exit(0);
    }
    (*wordlist)->source = source;
    (*wordlist)->count = 1;
    (*wordlist)->left = NULL;
    (*wordlist)->right = NULL;
}

void outputWordlist(wordlist_t *wordlist){
    if (wordlist){
        outputWordlist(wordlist->left);
        printf("%s => %d\n", wordlist->source, wordlist->count);
        outputWordlist(wordlist->right);
    }
}

int main() {
    char* stopper;
    char* str;
    char* tok;
    wordlist_t *wordlist = NULL;
    stopper = allocateStr();
    *(stopper) = ' ';
    printf("enter str\n");
    str = inputString();
    tok = allocateStr();
    if (str == NULL || tok == NULL || stopper == NULL){
        printf(NULL);
    }
    tok = strtok(str, stopper);
    while (tok){
        addWordlist(&wordlist, tok);
        tok = strtok(NULL, stopper);
    }
    outputWordlist(wordlist);
    putchar('\n');
    free(wordlist);
    free(tok);
    free(str);
    free(stopper);
    return 0;
}

