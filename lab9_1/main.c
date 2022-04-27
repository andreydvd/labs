#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dictionary {
    char* word;
    int count;
} dictionary;

void inputString(char* string);
void inputSize(int *size);
char* allocateString(int len);
int countWords(char *string);
char** allocateArray(int size);
void separateAndAddToArray(char** words, char* string, int countWords);
int countRepetitions(char** words, int countWords);
dictionary* allocateArrayWithStruct(int size);
void addToStructure(char** words, dictionary* wordsStruct, int sizeArray);
int findWord(dictionary* wordsStruct, char* wordq, int size);
int searchCountWord(char** words, char* word, int size);
void printStruct(dictionary* wordsStruct, int size);
void freeStruct(dictionary* wordsStruct);
void freeArray(char** string);


void main() {
    int size;
    inputSize(&size);
    char* string = allocateString(size);
    inputString(string);
    int numberOfWords = countWords(string);
    char** words = allocateArray(numberOfWords);
    separateAndAddToArray(words, string, numberOfWords);
    int sizeStruct = numberOfWords - countRepetitions(words, numberOfWords);
    dictionary* wordsStruct = allocateArrayWithStruct(sizeStruct);
    addToStructure(words, wordsStruct, numberOfWords);
    printStruct(wordsStruct, sizeStruct);
    freeStruct(wordsStruct);
    freeArray(words);
    freeArray(string);
}

void inputSize(int *size) {
    printf("Enter size of text: ");
    while ( scanf("%d", size) < 1 || *size < 0) {
        printf("wrong input\n");
        while (getchar() != '\n');
    }
}

char* allocateString(int size){
    return (char *)malloc(size * sizeof(char));
}

void inputString(char* string) {
    printf("Enter text: ");
    getchar();
    gets(string);
}


int countWords(char *string) {
    int count = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == ' ') {
            count += 1;
        }
    }
    return count + 1;
}

char** allocateArray(int size) {
    return (char **)malloc(size * sizeof(char*));
}

void separateAndAddToArray(char** words, char* string, int numberOfWords) {
    char* tok;
    char sign[7] = " .,/!?";
    tok = strtok(string, sign);
    for (int i = 0; i < numberOfWords; i++) {
        strcpy((words + i), tok);
        tok = strtok(NULL, sign); //null - сигнал, что строка продолжается(что это не новая строка)
    }
}

int countRepetitions(char** words, int numberOfWords) { //сколько слов повторяются
    int repetitions = 0;
    for (int i = 0; i < numberOfWords - 1; i++) {
        for (int j = i + 1; j < numberOfWords; j++) {
            if (!strcmp(words + i, words + j)) { //если равны, считаем
                repetitions++;
                break;
            }
        }
    }
    return repetitions;
}

dictionary* allocateArrayWithStruct(int size) { //создается массив, в котором каждый элемент это структура
    return malloc(size * sizeof(dictionary));
}

void addToStructure(char** words, dictionary* wordsStruct, int size) {
    for(int i = 0, j = 0; i < size; i++){
        if ((findWord(wordsStruct, words + i, j))){
            (*(wordsStruct + j)).word = (words + i);
            (*(wordsStruct + j)).count = searchCountWord(words, (words + i), size);
            j++;
        }
    }
}

//чем больше j, тем больше элементов мы сравниваем
//при сравнении первого слова j равна 0, соответственно мы первое слово ни с чем сравнивать не будем
//второе слово уже будем сравнивать с первым(j будет равно 1)

int findWord(dictionary* wordsStruct, char* wordq, int size) {//проверяет есть ли уже такое слово в словаре
    for(int i = 0; i < size; i++) {
        if (!strcmp((*(wordsStruct + i)).word, wordq)) { //сравниваются элемент массива структур с таким же элементом простого массива, если равны, то возвращается ноль
            return 0; //если такое слово есть, то возвращает 0
        }
    }
    return 1;//если слово встретилось впервые, возвращает 1
}

int searchCountWord(char** words, char* word, int size) { // считает количество таких слов
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (!strcmp(word, words + i))
            count++;
    }
    return count;
}

void printStruct(dictionary* wordsStruct, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s - %d\n", (*(wordsStruct + i)).word, (*(wordsStruct + i)).count);
    }
}

void freeStruct(dictionary* wordsStruct) {
    free(wordsStruct);
}

void freeArray(char** string) {
    free(string);
}
