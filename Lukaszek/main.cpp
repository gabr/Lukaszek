#include "FileComparer.h"

bool mainMenu(FileComparer &fc);

using namespace std;

int main(int argc, char** argv) {

    FileComparer comparer = FileComparer();

    if(argc < 2) {
        cout << " ! error: Not enough parameters!\n";
        cout << endl;
        cout << "   FILE COMPARER" << endl << endl;
        cout << "\tuse:" << endl;
        cout << "\t   " << argv[0] << " <path to pattern file> <path to compared file>" << endl;
        return 1;
    }

    if(!comparer.setPatternFile(argv[1])) {
        cout << " ! error: Wront pattern file path!\n";
        return 1;
    }

    if(!comparer.setComparedFile(argv[2])) {
        cout << " ! error: Wront compared file path!\n";
        return 1;
    }

    // comparing two files
    comparer.compare();
    comparer.printDif();

    // main menu
    while(mainMenu(comparer));

    return 0;
}

bool mainMenu(FileComparer& fc) {
    
    int decision = 0;

    return false;
}