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
    ProcessorRegister *controlInstruction; //
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
    controlInstruction = new ProcessorRegister();
    presentInstruction = new ProcessorRegister();
}

Processor::~Processor()
{
    delete console;
    delete mainstore;
    delete accumulator;
    delete controlInstruction;
    delete presentInstruction;
}

//
void Processor::run()
{

}

// increment the current Instruction
void Processor::increment() 
{
    controlInstruction->increment();
} 

// fetch the line from the main store that the CI is pointing to, store in PI
void Processor::fetch() 
{
    BinaryNum line;
    
    int location;
    
    //location = currentInstruction->convertToDecimal();

    line = mainstore->getLine(location);
    presentInstruction->setValue(line);
}              

// decodes the line
void Processor::decodeOperandFetch() 
{
    BinaryNum lineToDecode;
    lineToDecode = presentInstruction->getValue();
    
    //get substring 0-4 and 13-15
    BinaryNum operand(lineToDecode.getValue().substr(0, 5));
    BinaryNum opcode(lineToDecode.getValue().substr(13, 3));

    // store operand and opcode

    // TODO where operand?
    presentInstruction->setValue(opcode);
    controlInstruction->setValue(operand);
} 

// execute the command
void Processor::execute()
{
    BinaryNum opcode(presentInstruction->getValue());
    BinaryNum operand(controlInstruction->getValue());
    string instruction = opcode.getValue();
    //int location = mainstore->getLine().getDecimal();

    if(instruction == "000") // set CI to content of store location
    {
        // // CI = S
        // // TODO get location in mainstore as decimal
        // controlInstruction->setValue(mainstore->getLine(location));
    }
    else if(instruction == "100") // add content of store location to CI
    {
        // // CI = CI + S
        // controlInstruction->setValue();
    }
    else if(instruction == "010") // load accumulator with negative form of store content
    {
        // // A = -S
        // TODO get negative content of store
        // accumulator->setValue(mainstore->getLine(location))
    }
    else if(instruction == "110") // copy accumulator to store location
    {
        // // S = A
        // int location = 0; // TODO location = operand
        // int location = controlInstruction->getValue().getDecimal();
        // mainstore->setLine(location, accumulator->getValue())
    }
    else if(instruction == "001") // subtract content of store location from accumulator
    {
        // // A = A - S
        // int location = 0;
        // accumulator->setValue(accumulator->getValue() - mainstore->getLine(location));
    }
    else if(opcode.getValue() == "101") // as previous
    {
        // 
    }
    else if(instruction == "011") // increment CI if accumulator value negative 
    {
        // // if A < 0 then CI = CI + 1
        // if(accumulator->getValue() < 0)
        // {
        //     increment();
        // }
    }
    else if(instruction == "111") // set stop lamp and halt machine
    {
        
    }
    else
    {
        cout << "Error" << endl;
    }
    
}  


void Processor::display() 
{

}