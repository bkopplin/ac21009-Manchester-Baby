// Alina Littek: 180016182
// Bjarne Kopplin: 180016866
// Pui-Hin Vincent Lee: 180006178
// Jacque Nalwanga: 180004882
// Andrew Spence: 170018476

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
    string value;
    for (int i = 0; i < registerwidth; i++) 
    {
        value += "0";
    }
    BinaryNum num(value);
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
    string value = "1";
    for (int i = 0; i < registerwidth-1; i++) 
    {
        value += "0";
    }
    BinaryNum one(value);
    this->value = this->value + one;
}

#endif // PROCESSORREGISTER_H