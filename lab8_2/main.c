#include <stdio.h>
#include<stdlib.h>
#include"mystring.h"

void inputSize(int* size);
char** inputList(int size);
void changeList(char** list, int size, char* pat1, char* pat2);
void outputList(char** list, int size);
void freeList(char** list, int size);


int main()
{
    int size;
    printf("Input patterns \n");
    char* pat1 = inputString();
    char* pat2 = inputString();
    inputSize(&size);
    getchar();
    char** list = inputList(size);
    if((pat1 == NULL) || (pat2 == NULL) || (list == NULL))
    {
        printf("Not enough memory");
        exit(1);
    }
    changeList(list, size, pat1, pat2);
    outputList(list, size);
    freeList(list,size);
    free(pat1);
    free(pat2);

    return 0;
}

void inputSize(int* size)
{
    printf("Input count of lines \n");
    scanf("%d", size);
}

char** inputList(int size)
{
    char** list = malloc(sizeof(char*) * size);
    if(list)
    {
        for(int i = 0; i < size; i++)
        {
            *(list + i) = inputString();
            if(*(list + i) == NULL)
            {
                for(i--; i>=0;i--)
                    free(*(list + i));
                free(list);
                list = NULL;
                break;
            }
        }
    }
    return list;
}

void changeList(char** list, int size, char* pat1, char* pat2)
{
    for(int i = 0; i < size; i++)
        *(list + i) = swapPatterns(*(list + i),pat1, pat2);
}

void outputList(char** list, int size)
{
    printf("your list \n");
    for(int i = 0; i < size; i++)
    {
        printf("%s", *(list + i));
        printf("\n");
    }
}

void freeList(char** list, int size)
{
    for(int i = 0; i< size; i++)
    {
        free(*(list + i));
    }
    free(list);
}
