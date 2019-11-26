#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include "console.h"
#include "mainstore.h"
#include "binarynum.h"
#include "processorregister.h"
#include <string.h>

using namespace std;

class Processor
{
private:
    Console *console;                      // I/O
    Mainstore *mainstore;                  // main store of the Baby
    ProcessorRegister *accumulator;        // holds results of arithmetic calculations
    ProcessorRegister *controlInstruction; //
    ProcessorRegister *presentInstruction; // holds the actual instruction opcode which is being executed during that cycle

    void increment();          // increment the current Instruction
    void fetch();              // fetch the line from the main store that the CI is pointing to
    void decodeOperandFetch(); // decodes the line
    void execute(BinaryNum, BinaryNum);            // execute the command
    void display();

    void showState(string);
    void setAccumulator(BinaryNum newValue);
    BinaryNum getAccumulator();

public:
    Processor();
    ~Processor();
    void run();
    Mainstore *getMainStore() { return mainstore; }

    friend ostream &operator<<(ostream &output, const Processor &p)
    {
        output << "Accumulator: \t\t" << p.accumulator->getValue() << endl
               << "Control Instruction: \t" << p.controlInstruction->getValue() << endl
               << "Present Instruction: \t" << p.presentInstruction->getValue() << endl;
        return output;
    }
};

Processor::Processor()
{
    console = new Console();
    mainstore = new Mainstore(32);
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

void Processor::showState(string state)
{
    cout << "current task: " << state << endl;
    cout << *this << endl;
    char c = cin.get();
    if (c == 's')
    {
        cout << *mainstore << endl;
    }
    else
    {
    }
}

//
void Processor::run()
{
    int i = 0;
    bool keepGoing = true;
    do
    {
        cout << "----------"
             << "iteration " << i
             << "----------" << endl;
        increment();
        showState("increment");
        fetch();
        showState("fetch");
        decodeOperandFetch();
        showState("decode and operand fetch");
        display();
        showState("display");
    i++;
    } while (keepGoing);
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
    int location = controlInstruction->getValue().convertToDec();

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
    execute(operand, opcode);
}

// execute the command
void Processor::execute(BinaryNum operand, BinaryNum opcode)
{
    string instruction = opcode.getValue();
    int location = operand.convertToDec();

    cout << "Instruction " << instruction << endl;

    if (instruction == "000") // set CI to content of store location
    {
        // CI = S
        controlInstruction->setValue(mainstore->getLine(location));
    }
    else if (instruction == "100") // add content of store location to CI
    {
        // // CI = CI + S
        controlInstruction->setValue(controlInstruction->getValue() + mainstore->getLine(location));
    }
    else if (instruction == "010") // load accumulator with negative form of store content
    {
        // A = -S
        accumulator->setValue(mainstore->getLine(location).complement());
    }
    else if (instruction == "110") // copy accumulator to store location
    {
        // S = A
        mainstore->setLine(location, accumulator->getValue());
    }
    else if (instruction == "001") // subtract content of store location from accumulator
    {
        // A = A - S
        accumulator->setValue(accumulator->getValue() - mainstore->getLine(location));
    }
    else if (opcode.getValue() == "101") // as previous
    {
        // A = A - S
        accumulator->setValue(accumulator->getValue() - mainstore->getLine(location));
    }
    else if (instruction == "011") // increment CI if accumulator value negative
    {
        // if A < 0 then CI = CI + 1
        if(accumulator->getValue().isNegative())
        {
            increment();
        }
    }
    else if (instruction == "111") // set stop lamp and halt machine
    {
        cout << "Stopped" << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
}

void Processor::display()
{
}

#endif