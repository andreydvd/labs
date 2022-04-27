#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#define CHAR_SIZE 255
#define START_VALUE 1


struct Calculations {
    double max;
    double min;
    double med;
};

typedef struct AppContext {
    int columnNumber;
    char* regionName;
    char* fileName;
    int linesCount;
    bool columnNumberCheck;
    char** headers;
    int fieldsNum;
    char*** regionData;
    char** data;
    int dataLines;
    Calculations calc;
}AppContext;




























struct AppData {
//    char* dataChose;

//    char** year;
//    char** region;
//    char** npg;
//    char** birthRate;
//    char** deathRate;
//    char** gdw;
//    char** urbanization;
};

#endif // APPCONTEXT_H
