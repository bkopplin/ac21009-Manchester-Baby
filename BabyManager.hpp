#ifndef BABYMANAGER_H
#define BABYMANAGER_H

#include "binarynum.h"
#include "processor.h"
#include <fstream>

using namespace std;

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

/*
reads in a program in Baby mashine code and stores it in the main store
*/
void BabyManager::loadProgram(string filename) {
    ifstream input(filename, ios::in);
    
    if (input.is_open()) {
        string line;
        int l = 0;
        while(getline(input, line)) {
            BinaryNum thisLine(line);
            processor->getMainStore()->setLine(l, thisLine);
            l++;
        }    
    }
    input.close();
}

/*
* starts the Manchester Baby simulation
*/
void BabyManager::startSimulation() {
    this->processor->run();
}
#endif // BABYMANAGER_H