#include <stdio.h>
#include<stdlib.h>
#include"mystring.h"

int main()
{
    char* str = inputString();
    removeSpaces(str);
    outputString(str);
    return 0;
}

