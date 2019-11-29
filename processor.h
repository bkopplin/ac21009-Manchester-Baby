// Alina Littek: 180016182
// Bjarne Kopplin: 180016866
// Pui-Hin Vincent Lee: 180006178
// Jacque Nalwanga: 180004882
// Andrew Spence: 170018476


#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include "mainstore.h"
#include "binarynum.h"
#include "processorregister.h"
#include <string.h>

using namespace std;

/**
 * This class represents the processor of the Manchester Baby. 
 * It runs the fetch-execute cycle and displays its state to the user
 */
class Processor
{
private:
    Mainstore *mainstore;                  // main store of the Baby
    ProcessorRegister *accumulator;        // holds results of arithmetic calculations
    ProcessorRegister *controlInstruction; //
    ProcessorRegister *presentInstruction; // holds the actual instruction opcode which is being executed during that cycle

    void increment();                   // increment the current Instruction
    void fetch();                       // fetch the line from the main store that the CI is pointing to
    void decodeOperandFetch();          // decodes the line
    void execute(BinaryNum, BinaryNum); // execute the command

    bool keepGoing = true;
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

/**
 * default constructor
 */
Processor::Processor()
{
    mainstore = new Mainstore(registerwidth);
    accumulator = new ProcessorRegister();
    controlInstruction = new ProcessorRegister();
    presentInstruction = new ProcessorRegister();
}

/**
 * deconstructor
 */
Processor::~Processor()
{
    delete mainstore;
    delete accumulator;
    delete controlInstruction;
    delete presentInstruction;
}

/**
 * Show's the state of the Processor. 
 * This includes what operation the Processor is doing (increment, fetch etc. ), state of accumulator, control instruction and present instruction.
 * If the user is pressing enter, the next task in the fetch-execute circle will be performed.
 * If the user presses 's' and enter, the state of the memory will be shown.
 * this function should be called within the fetch-execute cycle.
 */
void Processor::showState(string state)
{
    cout << "\x1B[36m" << state << "\033[0m\t\t" << endl;
    cout << *this << endl;
    char c = ' ';
    do
    {
        c = cin.get();
        if (c == 's')
        {
            cout << *mainstore << endl;
            
        } else if (c == '\n') {
            break;
        }
        cin.clear();
        cin.ignore();
        
    } while (true);
}

/**
 * this functionruns the fetch execute cycle.
 * Moreover it prints out the main store in the beginning and the result of the calculation in the end
 */
void Processor::run()
{
    cout << endl
         << "------- Memmory --------" << endl
         << endl;
    cout << *mainstore << endl;

    int i = 0;
    do
    {
        cout << "----------" << endl
             << "\x1B[44mIteration: " << i << "\033[0m\t\t" << endl
             << "----------" << endl;
        increment();
        showState("increment");
        fetch();
        showState("fetch");
        decodeOperandFetch();
        showState("decode and operand fetch");
        i++;

    } while (keepGoing);

    cout << "    \x1B[41m   \033[0m\t\t" << endl;
    cout << "   \x1B[41m     \033[0m\t\t" << endl;
    cout << "  \x1B[41m  HALT \033[0m\t\t" << endl << endl;

    cout << *mainstore << endl;

    cout << "--------------------------------" << endl
         << endl;
    cout << "\t Result:  " << accumulator->getValue().convertToDec() << endl
         << endl;
    cout << "\t[" << accumulator->getValue() << " ]" << endl
         << endl;
    cout << "--------------------------------" << endl;
}

/**
 * increments the current instruction by one
 */
void Processor::increment()
{
    controlInstruction->increment();
}

/**
 *  fetch the line from the main store that the CI is pointing to, store in PI
 */
void Processor::fetch()
{
    BinaryNum line;
    int location = controlInstruction->getValue().convertToDec();

    line = mainstore->getLine(location);
    presentInstruction->setValue(line);
}

/** 
 * decodes the line into operand and opcode
 */
void Processor::decodeOperandFetch()
{
    BinaryNum lineToDecode;
    lineToDecode = presentInstruction->getValue();

    //get substring 0-12 and 13-16
    BinaryNum operand(lineToDecode.getValue().substr(0, 13));
    //BinaryNum opcode(lineToDecode.getValue().substr(13, 3));
    BinaryNum opcode(lineToDecode.getValue().substr(13, 4));

    execute(operand, opcode);
    showState("execute");
}

/**
 *  execute the commands
 */
void Processor::execute(BinaryNum operand, BinaryNum opcode)
{
    string instruction = opcode.getValue();
    int location = operand.convertToDec();
    cout << "\x1B[35mDecode Present Instruction\033[0m\t\t" << endl
         << "\tOperand: " << operand << " (memory location " << location << ")" << endl
         << "\tOpcode: " << opcode << " | instruction " << opcode.convertToDec() << " -> ";

    if (instruction == "0000") // JMP - set CI to content of store location
    {
        cout << "JMP" << endl;
        // CI = S
        controlInstruction->setValue(operand);
    }
    else if (instruction == "1000") // JRP - add content of store location to CI
    {
        cout << "JRP" << endl;
        // CI = CI + S
        controlInstruction->setValue(controlInstruction->getValue() + operand);
    }
    else if (instruction == "0100") //  LDN -load accumulator with negative form of store content
    {
        cout << "LDN" << endl;
        // A = -S
        accumulator->setValue(mainstore->getLine(location).complement());
    }
    else if (instruction == "1100") // STO - copy accumulator to store location
    {
        cout << "STO" << endl;
        // S = A
        mainstore->setLine(location, accumulator->getValue());
    }
    else if (instruction == "0010") // SUB - subtract content of store location from accumulator
    {
        cout << "SUB" << endl;
        // A = A - S
        accumulator->setValue(accumulator->getValue() - mainstore->getLine(location));
    }
    else if (opcode.getValue() == "1010") // SUB - as previous
    {
        cout << "SUB" << endl;
        // A = A - S
        accumulator->setValue(accumulator->getValue() - mainstore->getLine(location));
    }
    else if (instruction == "0110") // CMP - increment CI if accumulator value negative
    {
        cout << "CMP" << endl;
        // if A < 0 then CI = CI + 1
        if (accumulator->getValue().isNegative())
        {
            increment();
        }
    }
    else if (instruction == "1110") // STP - set stop lamp and halt machine
    {
        cout << "STP" << endl;
        keepGoing = false;
    }
    else if (instruction == "0001") // new instruction: MTP - multiply content of store location with CI
    {
        cout << "MTP" << endl;
        accumulator->setValue(accumulator->getValue() * mainstore->getLine(location));
    }
    else if (instruction == "1001") // new instruction - to extend
    {
        cout << "---" << endl;
    }
    else
    {
        cerr << "Error, operand not definded" << endl;
    }
    cout << endl;
}

#endif