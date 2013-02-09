#include "FileComparer.h"

// function that creates menu after finding differences in files
// only declaration here
bool mainMenu(FileComparer &fc);

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
}

// function that creates menu after finding differences in files
// function definition:
bool mainMenu(FileComparer& fc) {

    // variables to store user decisions
    int decision = -1;
    char yes_no = char();
    string path_new_file = "new.txt";

    // menu content
    cout << endl;
    cout << " > What do you want to do with those differences?" << endl;
    cout << "  ---------------------------------------------------------------------------\n";
    cout << "   1. Copy all lines that was missed in compared file to it and overwrite it.\n";
    cout << "   2. Copy all additional lines from compared file to pattern file.\n";
    cout << "   3. Create a new file with all lines from both files.\n";
    cout << "   -------------------------------------------------------------------------\n";
    cout << "   0. Nothing, just close the program.\n";
    cout << "  ---------------------------------------------------------------------------\n";

    // taking decision from user until it is correct
    while(decision > 3 || decision < 0) {

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
            cout << " > Set file name? (y/n)\n";
            while(cout << " : ",
                cin >> yes_no,
                yes_no = tolower(yes_no),
                yes_no != 'y' && yes_no != 'n');

            if(yes_no == 'y') {
                cout << endl;
                cout << " > Give name for new file.\n";
                cout << " : ";
                cin >> path_new_file;
            }

            if(!fc.createNew(path_new_file))
                return false;
            cout << " > Your file was successful created.\n";
            break;

        default:
            cout << " ! error: Wrong option!\n";
            break;

        }
    } 

    return true;
}