#include "filework.h"
#include <string>
#include <fstream>

vector<string> split_line(string line)
{
    vector<string> result;
    string word = "";
    for (int i = 0; i < line.length(); ++i){
        char symbol = line[i];
        if ((symbol == ',') || symbol == '\n'){
            result.push_back(word);
            word = "";
            continue;
        }
        word += symbol;
    }
    result.push_back(word);
    return result;
}

vector<vector<string>> read_csv_file(string path)
{
    vector<vector<string>> result;
    string line;
    ifstream myFile(path);
    if (!myFile.is_open()) {
        runtime_error("Could not open file");
    }

    while(getline(myFile, line)){
        vector<string> line_model = split_line(line);
        result.push_back(line_model);
    }
    return result;
}


