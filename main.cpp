// Alina Littek: 180016182
// Bjarne Kopplin: 180016866
// Pui-Hin Vincent Lee: 180006178
// Jacque Nalwanga: 180004882
// Andrew Spence: 170018476

#include "processor.h"
#include <iostream>
#include "BabyManager.hpp"
#include "config.hpp"

using namespace std;

void usageMessage()
{
    cerr << "USAGE: <inputfile> <register width*> <number of addresses*>" << endl
    << "Where values with a '*' are optional. register width and number of address are set to 32 by default" << endl;
}

void welcomeMessage()
{
    cout << "press 'Enter' to go to the next step, 's' to see the store" << endl;
}

int main(int argc, char **argv)
{
    string inputfile;

    if (argc != 4)
    {
        usageMessage();
        return 1;
    }
    //1 filename (inputfile.txt)
    inputfile = argv[1];

    //2 register registerwidth
    registerwidth = atoi(argv[2]);
    if(atoi(argv[2]) == 0 || registerwidth < 1)
    {
        cerr << "Invalid input for argument 2" << endl;
        return 1;
    }

    //3 number of addresses in mainstore
    numberofaddresses = atoi(argv[3]);
    if(atoi(argv[2]) == 0 || numberofaddresses < 1)
    {
        cerr << "Invalid input for argument 3" << endl;
        return 1;
    }
    
    welcomeMessage();
    
    BabyManager manager;
    manager.loadProgram(inputfile);
    manager.startSimulation();

    return 0;
}