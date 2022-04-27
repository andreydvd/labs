#ifndef MYSTRING_H
#define MYSTRING_H



char* inputString();
unsigned int strLen(const char* str);
char* strChr(char* str, char c);
char* strCpy(char* dest, const char* src);
void strCat(char* dest, char* src);
char* strDel(char* p, int count);
char* strStr(char* str, char* pat);
char* strIns(char* s, const char* subS);
char* swapPatterns(char* str, char* pat1, char* pat2);
char* removeSpaces(char* str);
void outputString(char* str);

#endif // MYSTRING_H
