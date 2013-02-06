#include "FileComparer.h"

FileComparer::FileComparer(void)
{

};

FileComparer::~FileComparer(void)
{
    fs_pattern.close();
    fs_compared.close();
};

bool FileComparer::setPatternFile(string path) {
    fs_pattern.close();
    fs_pattern.open(path, ios::in);

    if(!fs_pattern.is_open()) return false;

    path_pattern = path;
    return true;
};

bool FileComparer::setComparedFile(string path) {
    fs_compared.close();
    fs_compared.open(path, ios::in);

    if(!fs_compared.is_open()) return false;

    path_compared = path;
    return true;
};

void FileComparer::printPatternFile() {
    string line;
    long position = fs_pattern.tellp();

    fs_pattern.seekp(0, ios_base::beg);
    cout << "pattern file [" << path_pattern << "] :\n";
    while(fs_pattern.good()){
        getline(fs_pattern, line);
        cout << line << endl;
    }

    setPatternFile(path_pattern);
    fs_pattern.seekp(position);
};

void FileComparer::printComparedFile() {
    string line;
    long position = fs_compared.tellp();

    fs_compared.seekp(0, ios_base::beg);
    cout << "compared file [" << path_compared << "] :\n";
    while(fs_compared.good()){
        getline(fs_compared, line);
        cout << line << endl;
    }

    setComparedFile(path_compared);
    fs_compared.seekp(position);
};

long FileComparer::getNumberOfLinesInPattern() {
    string line;
    long lines = 0;

    setPatternFile(path_pattern);
    while(fs_pattern.good()) {
        getline(fs_pattern, line);
        ++lines;
    }

    return lines;
};

long FileComparer::getNumberOfLinesInCompared() {
    string line;
    long lines = 0;

    setComparedFile(path_compared);
    while(fs_compared.good()) {
        getline(fs_compared, line);
        ++lines;
    }

    return lines;
};

string FileComparer::getLineFromPatternFile(int line_number){
    int lines;
    string line;
    long position = fs_pattern.tellp();

    setPatternFile(path_pattern);
    for(lines = 0; lines < line_number; lines++)
        getline(fs_pattern, line);

    setPatternFile(path_pattern);
    fs_pattern.seekp(position);

    return line;
};

string FileComparer::getLineFromComparedFile(int line_number){
    int lines;
    string line;
    long position = fs_compared.tellp();

    setComparedFile(path_compared);
    for(lines = 0; lines < line_number; lines++)
        getline(fs_compared, line);

    setComparedFile(path_compared);
    fs_compared.seekp(position);

    return line;
};

void FileComparer::prepareCompareArray() {
    int rows = (int) getNumberOfLinesInPattern();
    int columns = (int) getNumberOfLinesInCompared();
    compare_matrix.resize(rows, vector<bool>(columns, false));
};

void FileComparer::compare() {
    long position = 0;
    prepareCompareArray();

    setPatternFile(path_pattern);
    setComparedFile(path_compared);

    for(int i = 0; i < compare_matrix.size(); i++)
        for(int j = position; j < compare_matrix[i].size(); j++)
            if(getLineFromPatternFile(i+1) == getLineFromComparedFile(j+1)) {
                compare_matrix[i][j] = true;
                position=j+1;
                break;
            } else
                compare_matrix[i][j] = false;

    // wypisuje tablice porównañ
    //for(int i = 0; i < compare_matrix.size(); i++) {
    //    for(int j = 0; j < compare_matrix[i].size(); j++)
    //        if(compare_matrix[i][j]) {
    //            cout << "1 ";
    //        } else
    //            cout << "0 ";
    //        cout << endl;
    //}
};

void FileComparer::printDif() {
    long position = 0;

    setPatternFile(path_pattern);
    setComparedFile(path_compared);

    for(int i = 0; i < compare_matrix.size(); i++){
        if(compare_matrix[i][position]) {
            cout << i+1 << " " << position+1 << " " << getLineFromPatternFile(i+1) << endl;
            ++position;
        } else
            for(int j = position; j < compare_matrix[i].size(); j++)
                if(compare_matrix[i][j]) {
                    for(int k = position; k < j; k++)
                        cout << "+ " << k+1 << " " << getLineFromComparedFile(k+1) << endl;
                    position = j;
                    cout << i+1 << " " << position+1 << " " << getLineFromPatternFile(i+1) << endl;
                    ++position;
                    break;
                } else if(j == compare_matrix[i].size()-1)
                    cout << i+1 << " - " << getLineFromPatternFile(i+1) << endl;
        if(i == compare_matrix.size()-1 && position < compare_matrix[i].size())
            for(int j = position; j < compare_matrix[i].size(); j++)
                cout << "+ " << j+1 << " " << getLineFromComparedFile(j+1) << endl;
        else if(position == compare_matrix[i].size() && i != compare_matrix.size()-1) {
            for(int j = i; j < compare_matrix.size(); j++)
                cout << j+1 << " - " << getLineFromPatternFile(j+1) << endl;
            break;
        }
    }
};