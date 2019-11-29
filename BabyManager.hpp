#ifndef BABYMANAGER_H
#define BABYMANAGER_H

#include "binarynum.h"
#include "processor.h"
//#include "config.hpp"
#include <fstream>

using namespace std;

/**
 * This class is responsible for managing the baby.
 * One can imagine this class to be a person controlling the baby.
 * It's creating an instance of the Processor, loads a program into the main store and then starts the fetch execute cycle
 */
class BabyManager {
    public:
    Processor * getProcessor() {return this->processor;};
    void loadProgram(string);
    void startSimulation();
    BabyManager();

    private:
    Processor *processor; 
};

BabyManager::BabyManager() {
    this->processor = new Processor();
}

/**
* reads in a program in Baby mashine code and stores it in the main store
* @param filename the file where the mashine code is stored
*/
void BabyManager::loadProgram(string filename) {
    ifstream input(filename, ios::in);
    
    if (input.is_open()) {
        string line;
        int l = 0;
        while(getline(input, line)) {
            if ((int)line.size() != registerwidth) 
            {
                cerr << endl << "***** Error:  Line: " << l << " doesn't have the same length as the register width." << endl
                << "***** Should be of length: " << registerwidth << endl << endl;
                exit(-1);
            }
            BinaryNum thisLine(line);
            processor->getMainStore()->setLine(l, thisLine);
            l++;
        }    
    }
    input.close();
}

/**
* starts the Manchester Baby simulation (fetch-execute cycle)
*/
void BabyManager::startSimulation() {
    this->processor->run();
}
#endif // BABYMANAGER_H