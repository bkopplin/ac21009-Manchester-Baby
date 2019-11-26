#ifndef PROCESSORREGISTER_H
#define PROCESSORREGISTER_H

#include "binarynum.h"

using namespace std;

class ProcessorRegister
{
private:
    BinaryNum value;

public:
    ProcessorRegister();
    ~ProcessorRegister();
    BinaryNum getValue() { return this->value; };
    void setValue(BinaryNum newValue) { this->value = newValue; }
    void increment(); // TODO Implement
};

ProcessorRegister::ProcessorRegister()
{
    BinaryNum num("0");
    this->value = num;
}

ProcessorRegister::~ProcessorRegister()
{
}

// increment the CI to point to the next item in the array
void ProcessorRegister::increment()
{
    BinaryNum one("1000 0000 0000 0000 0000 0000 0000 0000");
    this->value = this->value + one;
}

#endif