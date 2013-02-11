#include "FileComparer.h"

// functions that creates menus after finding differences in files
// only declaration here
bool mainMenu(FileComparer &fc);
bool blockOperationMenu(FileComparer& fc);
long getNumber(string msg, long range_x, long range_y);
string newFileName();

using namespace std;

int main(int argc, char** argv) {

    // main object, it will compare two files and do all other actions with them
    FileComparer comparer = FileComparer();

    // checking if the number of parameters is correct
    if(argc < 2) {
        cout << " ! error: Not enough parameters!\n";
        cout << endl;
        cout << "   FILE COMPARER" << endl << endl;
        cout << "\tuse:" << endl;
        cout << "\t   " << argv[0] << " <path to pattern file> <path to compared file>" << endl;
        return 1;
    }

    // setting the pattern file and checking if it exist
    if(!comparer.setPatternFile(argv[1])) {
        cout << " ! error: Wront pattern file path!\n";
        return 1;
    }

    // setting the compared file and checking if it exist
    if(!comparer.setComparedFile(argv[2])) {
        cout << " ! error: Wront compared file path!\n";
        return 1;
    }

    // comparing two files
    comparer.compare();
    // printing the differences between them
    comparer.printDif();

    // main menu, if function return false then the error appears
    if(!mainMenu(comparer)) {
        cout << " ! error: Can not write file! Check you write permission!\n";
        return 1;
    }

    return 0;
};

long getNumber(string msg, long range_x, long range_y) {
    long number = long();

    cout << " > " << msg << endl << " : ";
    while(cin >> number, number < range_x || number > range_y)
            cout << " > Wrong number, not in range!\n : ";

    return number;
};

string newFileName() {
    
    char yes_no = char();
    string path_new_file = "new.txt";

    cout << " > Set file name? (y/n)\n";
    while(cout << " : ",
        cin >> yes_no,
        yes_no = tolower(yes_no),
        yes_no != 'y' && yes_no != 'n');

    if(yes_no == 'y') {
        cout << " > Give name for new file.\n";
        cout << " : ";
        cin >> path_new_file;
    }

    return path_new_file;
};

// function that creates menu after finding differences in files
// function definition:
bool mainMenu(FileComparer& fc) {

    // variables to store user decisions
    int decision = -1;

    // menu content
    cout << endl;
    cout << " > What do you want to do with those differences?\n" << endl;
    cout << " +----------------------------------------------------------------------------+\n";
    cout << " | 1. Copy all lines that was missed in compared file to it and overwrite it. |\n";
    cout << " | 2. Copy all additional lines from compared file to pattern file.           |\n";
    cout << " | 3. Create a new file with all lines from both files.                       |\n";
    cout << " +----------------------------------------------------------------------------+\n";
    cout << " | 4. Operations on block of text.                                            |\n";
    cout << " +----------------------------------------------------------------------------+\n";
    cout << " | 0. Nothing, just close the program.                                        |\n";
    cout << " +----------------------------------------------------------------------------+\n\n";

    // taking decision from user until it is correct
    while(decision > 4 || decision < 0) {

        // prompt for user
        cout << " : ";
        cin >> decision;

        // take property action
        switch(decision) {

        case 0: return true;

        case 1:
            if(!fc.overwriteCompared())
                return false;
            cout << " > Your file was successful overwritten.\n";
            break;

        case 2:
            if(!fc.overwritePattern())
                return false;
            cout << " > Your file was successful overwritten.\n";
            break;

        case 3:

            if(!fc.createNew(newFileName()))
                return false;
            cout << " > Your file was successful created.\n";
            break;

        case 4:
            if(!blockOperationMenu(fc))
                return false;
            else return true;

        default:
            cout << " ! error: Wrong option!\n";
            break;

        }
    } 

    return true;
};

// menu for 4th option
// definition:
bool blockOperationMenu(FileComparer& fc) {

    // variables to store user decisions
    int decision = -1;

    // variable to store range
    long pattern_x, pattern_y;
    long compared_x, compared_y;
    pattern_x = pattern_y = compared_x = compared_y = long();

        // menu content
        cout << endl;
        cout << " > Block operation menu:\n" << endl;
        cout << " +----------------------------------------------------------------------------+\n";
        cout << " | 1. Replace a block of data in pattern a block of data from compared file.  |\n";
        cout << " | 2. Replace a block of data in compared file a block of data from pattern.  |\n";
        cout << " +----------------------------------------------------------------------------+\n";
        cout << " | 3. Same as first option but save data to new file.                         |\n";
        cout << " | 4. Same as second option but save data to new file.                        |\n";
        cout << " +----------------------------------------------------------------------------+\n";
        cout << " | 0. Close the program.                                                      |\n";
        cout << " +----------------------------------------------------------------------------+\n\n";


    while(decision > 4 || decision < 0) {
        // prompt for user
        cout << " : ";
        cin >> decision;

        // take property action
        switch(decision) {

        case 0: return true;

        case 1:
            cout << " > Set range for the compared file!\n" << 
                    " > (from which the block of data will be moved to pattern)\n\n";
            compared_x = getNumber("begining line number: ", 1, fc.getNumberOfLinesInCompared());
            compared_y = getNumber("end line number", compared_x, fc.getNumberOfLinesInCompared());

            cout << endl;
            cout << " > Set range for the pattern file!\n" << 
                    " > That lines will be repleaced by just set compared file block of data.\n" << 
                    " > You can set just one line, then data will be added after that line.\n\n";
            pattern_x = getNumber("begining line number: ", 0, fc.getNumberOfLinesInPattern());
            pattern_y = getNumber("end line number", pattern_x, fc.getNumberOfLinesInPattern());
            cout << endl;

            if(!fc.block_fromComparedToPattern(compared_x, compared_y, pattern_x, pattern_y))
                return false;
            break;

        case 2:
            cout << " > Set range for the pattern file!\n" << 
                    " > (from which the block of data will be moved to compared file)\n\n";
            pattern_x = getNumber("begining line number: ", 1, fc.getNumberOfLinesInPattern());
            pattern_y = getNumber("end line number", pattern_x, fc.getNumberOfLinesInPattern());

            cout << endl;
            cout << " > Set range for the compared file!\n" << 
                    " > That lines will be repleaced by just set pattern file block of data.\n" << 
                    " > You can set just one line, then data will be added after that line.\n\n";
            compared_x = getNumber("begining line number: ", 0, fc.getNumberOfLinesInCompared());
            compared_y = getNumber("end line number", compared_x, fc.getNumberOfLinesInCompared());
            cout << endl;

            if(!fc.block_fromPatternToCompared(pattern_x, pattern_y, compared_x, compared_y))
                return false;
            break;

        case 3:
            cout << " > Set range for the compared file!\n" << 
                    " > (from which the block of data will be moved to pattern)\n\n";
            compared_x = getNumber("begining line number: ", 1, fc.getNumberOfLinesInCompared());
            compared_y = getNumber("end line number", compared_x, fc.getNumberOfLinesInCompared());

            cout << endl;
            cout << " > Set range for the pattern file!\n" << 
                    " > That lines will be repleaced by just set compared file block of data.\n" << 
                    " > You can set just one line, then data will be added after that line.\n\n";
            pattern_x = getNumber("begining line number: ", 0, fc.getNumberOfLinesInPattern());
            pattern_y = getNumber("end line number", pattern_x, fc.getNumberOfLinesInPattern());
            cout << endl;

            if(!fc.block_createNew_fromComparedToPattern(newFileName(), compared_x, compared_y, pattern_x, pattern_y))
                return false;
            break;

        case 4:
            cout << " > Set range for the pattern file!\n" << 
                    " > (from which the block of data will be moved to compared file)\n\n";
            pattern_x = getNumber("begining line number: ", 1, fc.getNumberOfLinesInPattern());
            pattern_y = getNumber("end line number", pattern_x, fc.getNumberOfLinesInPattern());

            cout << endl;
            cout << " > Set range for the compared file!\n" << 
                    " > That lines will be repleaced by just set pattern file block of data.\n" << 
                    " > You can set just one line, then data will be added after that line.\n\n";
            compared_x = getNumber("begining line number: ", 0, fc.getNumberOfLinesInCompared());
            compared_y = getNumber("end line number", compared_x, fc.getNumberOfLinesInCompared());
            cout << endl;

            if(!fc.block_createNew_fromPatternToCompared(newFileName(), pattern_x, pattern_y, compared_x, compared_y))
                return false;
            break;

        default:
            cout << " ! error: Wrong option!\n";
            break;

        }

        if(decision >= 1 && decision <=4)
            cout << " > Replacement ended successfully.\n";
    } 

    return true;
};