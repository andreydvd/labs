#include <stdio.h>
#include<stdlib.h>
#include"mystring.h"

char* inputString()
{
    char* string = (char*)malloc(sizeof (char));
    int length = 1;
    int checker = 0;
    if(string)
    {
        *(string + length - 1) = getchar();
        while(*(string + length - 1) != '\n')
        {
            length += 1;
            string = realloc(string, sizeof(char) * (length));
            if(!string)
            {
                checker = 1;
                break;
            }
            *(string + length - 1) = getchar();
        }
        if(!checker)
            *(string + length - 1) = '\0';
    }
    return string;
}

char* strChr(char* str, char c)
{
    char *p = str;
    for(; (*p) && (*p != c); p++);
    return *p?p:0;
}

char* strStr(char* str, char* pat)
{
    char* q;
    char* p=str;
    char* qs = pat;
    int check = 1;

    while(*p && *qs && check)
    {
        for(q = p, qs = pat; *q && *q == *qs; q++, qs++)
            if(!(*qs && *q))
                check = 0;
        p++;
    }
    return *p?p-1:0;
}

unsigned int strLen(const char* str)
{
    unsigned int len = 0;
    for( ; *(str + len); len++);
    return len;
}

char* strCpy(char* dest, const char* src)
{
    for(int i = 0; (*(dest + i) = *(src + i)); i++);
    return dest;
}

char* strDel(char* p, int count)
{
    strCpy(p, p + count);
    return p;
}

void strCat(char* dest, char* src)
{
    char* p = dest;
    for(;*p;p++);
    for(int i = 0;(*(p + i)= *(src + i)); i++);
}

char* strIns(char* s, const char* subS)
{
    int subSLen = strLen(subS);
    char* temp = (char*)malloc(sizeof (char) * (strLen(s) + 1));
    if(temp)
    {
        strCpy(temp,s);
        strCpy(s,subS);
        strCpy(s + subSLen, temp);
            free(temp);
    }

    return s;
}

char* swapPatterns(char* string, char* pat1, char* pat2)
{
    int pat1Len = strLen(pat1);
    int pat2Len = strLen(pat2);

    int stringLen = strLen(string);
    string = (char*)realloc(string,sizeof (char) * (stringLen + abs(pat2Len - pat1Len)));
    if(string)
    {

        char* firstSpacePos = strChr(string, ' ');
        char* patPos = strStr(string, pat1);
        while(patPos && ((patPos < firstSpacePos) || (firstSpacePos == NULL)))
        {
            strDel(patPos,pat1Len);
            strIns(patPos,pat2);
            patPos = strStr(patPos + pat2Len, pat1);
            firstSpacePos = strChr(string, ' ');
        }
    }
    return string;
}

char* removeSpaces(char* str)
{
    while(*str == ' ')
    {
        strCpy(str, str+1);
    }
    char *p;
    char* startpos = str;
    int len = strLen(str);
    for(int i = 0; i < len; i++)
    {
        while((p = strChr(startpos,' ')) && *(p+1) == ' ')
        {
            strCpy(p,p + 1);
            startpos = p;
            len -= 1;
        }
        startpos = startpos + 1;
    }
    len = strLen(str);
    if(*(str + len -1) == ' ')
    {
        strCpy(str + len -1, str + len);
    }
    return str;

}

void outputString(char* str)
{
    printf("'%s'", str);
}
