#include "processor.h"
#include <iostream>
#include "BabyManager.hpp"

using namespace std;

void usageMessage()
{
    cerr << "USAGE: <inputfile>" << endl;
}

void welcomeMessage()
{
    cout << "press 'Enter' to go to the next step, 's' to see the store"
         << endl;
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        usageMessage();
        return 1;
    }
    welcomeMessage();

    string inputfile = argv[1];
    BabyManager manager;
    manager.loadProgram(inputfile);
    manager.startSimulation();

    return 0;
}