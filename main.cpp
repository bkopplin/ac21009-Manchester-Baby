#include "processor.h"

using namespace std;

void usageMessage() {
    cerr << "USAGE: <inputfile>" << endl;
}

int main(int argc, char** argv) {

    if (argc != 2) {
        usageMessage();
        return 1;
    }
    string inputfile = argv[1];
    Processor processor;


    

    // read in file
    // ignore everything behind = or ;

    // set content of memory to the input file

    // run fetch execute cycle until halted
    
    return 0;
}