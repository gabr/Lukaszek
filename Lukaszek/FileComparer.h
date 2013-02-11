#pragma once

#include <iostream>     // for i/o operations
#include <string>       // for string operatinos
#include <fstream>      // for file operatins
#include <vector>       // for matrix which is used in files comparing process

using namespace std;

class FileComparer
{
private:

    fstream fs_pattern;     // pattern file stream
    fstream fs_compared;    // compared file stream

    string path_pattern;    // path to pattern file
    string path_compared;   // path to compared file

    vector< vector<bool> > compare_matrix;  // matrix to code differences

    void prepareCompareArray();                       // creating and filling the matrix

    bool isFileExist(string path);                    // checking if file exist

    long getLinePositionInPatternFile(long num);      // getting line position in pattern file
    long getLinePositionInComparedFile(long num);     // getting line position in compared file
    string getLineFromPatternFile(int line_number);   // getting specify line from pattern file
    string getLineFromComparedFile(int line_number);  // getting specify line from compared file

public:
    FileComparer(void);     // default constructor
    ~FileComparer(void);    // destructor

    bool setPatternFile(string path);   // opening the pattern file and setting path_pattern variable
    bool setComparedFile(string path);  // opening the compared file and setting path_compared variable

    long getNumberOfLinesInPattern();   // counting the number of lines in pattern file
    long getNumberOfLinesInCompared();  // counting the number of lines in compared file

    void printPatternFile();    // printing all lines from pattern file
    void printComparedFile();   // printing all lines from compared file


    void compare();     // methond that compare both files
    void printDif();    // method that print results of comparison files

    bool overwritePattern();            // overwrite differences to pattern file
    bool overwriteCompared();           // overwrite differences to compared file
    bool createNew(string path_new);    // save content of both files in new file

    // methods for block operations
    bool block_fromPatternToCompared(long pattern_x, long pattern_y, long compared_x, long compared_y);
    bool block_fromComparedToPattern(long compared_x, long compared_y, long pattern_x, long pattern_y);
    bool block_createNew_fromPatternToCompared(string path, long pattern_x, long pattern_y, long compared_x, long compared_y);
    bool block_createNew_fromComparedToPattern(string path, long compared_x, long compared_y, long pattern_x, long pattern_y);
};