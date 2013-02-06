#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class FileComparer
{
private:

    fstream fs_pattern;
    fstream fs_compared;

    string path_pattern;
    string path_compared;

    vector< vector<bool> > compare_matrix;

public:
    FileComparer(void);
    ~FileComparer(void);

    bool setPatternFile(string path);
    bool setComparedFile(string path);

    void printPatternFile();
    void printComparedFile();
    long getNumberOfLinesInPattern();
    long getNumberOfLinesInCompared();
    string getLineFromPatternFile(int line_number);
    string getLineFromComparedFile(int line_number);

    void prepareCompareArray();
    void compare();
    void printDif();
};