#ifndef PROCESSORREGISTER_H
#define PROCESSORREGISTER_H

#include "binarynum.h"

using namespace std;

/**
 * This class represents a processor register and provices functions to manipulate it, such as changing the value stored in the register or getting the value
 * The accumulator, PI, and CI all are processor registers.
 */ 
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

/**
 * instanciates a processor register with a register with of the processor.
 */ 
ProcessorRegister::ProcessorRegister()
{
    BinaryNum num("0000 0000 0000 0000 0000 0000 0000 0000");
    this->value = num;
}

/**
 * destructor
 */
ProcessorRegister::~ProcessorRegister()
{
}

/**
 *  increment the CI to point to the next item in the array
 */
void ProcessorRegister::increment()
{
    BinaryNum one("1000 0000 0000 0000 0000 0000 0000 0000");
    this->value = this->value + one;
}

#endif // PROCESSORREGISTER_H