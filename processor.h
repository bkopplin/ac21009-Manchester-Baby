#include <iostream>
#include "console.h"
#include "mainstore.h"
#include "binarynum.h"
#include "processorregister.h"
#include <string.h>

class Processor
{
private:
    Console *console;              // I/O
    Mainstore *mainstore;          // main store of the Baby
    ProcessorRegister *accumulator;        // holds results of arithmetic calculations
    ProcessorRegister *currentInstruction; //
    ProcessorRegister *presentInstruction; // holds the actual instruction opcode which is being executed during that cycle

    void increment();          // increment the current Instruction
    void fetch();              // fetch the line from the main store that the CI is pointing to
    void decodeOperandFetch(); // decodes the line
    void execute();            // execute the command
    void display();

    void setAccumulator(BinaryNum newValue);
    BinaryNum getAccumulator();

public:
    Processor();
    ~Processor();
    void run();
    Mainstore * getMainStore() { return mainstore;}

    // friend ostream operator<<(ostream &output, const Processor p) {
    //     output << "TODO: implement" << endl;
    //     return output;
    // }
};

Processor::Processor()
{
    console = new Console();
    mainstore = new Mainstore();
    accumulator = new ProcessorRegister();
    currentInstruction = new ProcessorRegister();
    presentInstruction = new ProcessorRegister();
}

Processor::~Processor()
{
    delete console;
    delete mainstore;
    delete accumulator;
    delete currentInstruction;
    delete presentInstruction;
}

//
void Processor::run()
{

}

// increment the current Instruction
void Processor::increment() 
{
    currentInstruction->increment();
} 

// fetch the line from the main store that the CI is pointing to, store in PI
void Processor::fetch() 
{
    BinaryNum line;
    
    int location;
    location = currentInstruction->convertToDecimal();

    line = mainstore->getLine(location);
    presentInstruction->setValue(line);
}              

// decodes the line
void Processor::decodeOperandFetch() 
{
    BinaryNum lineToDecode;
    lineToDecode = presentInstruction->getValue();
    
    //get substring 0-4 and 13-15
    string operand;
    string opcode;

    operand = lineToDecode.getValue().substr(0, 5);
    opcode = lineToDecode.getValue().substr(13, 3);
} 

// execute the command
void Processor::execute()
{

}  


void Processor::display() 
{

}