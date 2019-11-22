#include <iostream>
#include "console.h"
#include "mainstore.h"
#include "binarynum.h"
#include "processorregister.h"

class Processor
{
private:
    Console *console;              // I/O
    Mainstore *mainstore;          // main store of the Baby
    ProcessorRegister *accumulator;        // stores temporary values
    ProcessorRegister *currentInstruction; //
    ProcessorRegister *presentInstruction; // opcode / function

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
}

void Processor::run()
{
}

void Processor::increment() {}          // increment the current Instruction
void Processor::fetch() {}              // fetch the line from the main store that the CI is pointing to
void Processor::decodeOperandFetch() {} // decodes the line
void Processor::execute() {
}            // execute the command
void Processor::display() {}