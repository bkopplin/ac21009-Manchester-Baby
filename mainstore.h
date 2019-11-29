// Alina Littek: 180016182
// Bjarne Kopplin: 180016866
// Pui-Hin Vincent Lee: 180006178
// Jacque Nalwanga: 180004882
// Andrew Spence: 170018476

#ifndef MAINSTORE_H
#define MAINSTORE_H

#include "binarynum.h"
#include <array>
#include <vector>
#include "config.hpp"

using namespace std;

/**
 * This class represents the mainstore of the Baby. An array is used as the underlaying datastructure.
 */
class Mainstore
{
private:
    int size;
    BinaryNum *grid;

public:
    Mainstore();
    ~Mainstore();
    explicit Mainstore(int size);
    BinaryNum getLine(int location);
    void setLine(int location, BinaryNum content);

    friend ostream &operator<<(ostream &output, const Mainstore &s)
    {
        for (int i = 0; i < s.size; i++)
        {
            cout << "\x1B[40m";
            if (i < 10)
            {
                output << " ";
            }
            output << i << " " << s.grid[i] << "\033[0m\t\t" << endl;
        }
        return output;
    }
};

/**
 * default constructor
 * Set's the size of the main store to 32 by default
 */
Mainstore::Mainstore()
{
    size = registerwidth;
    grid = new BinaryNum[size];
}

/**
 * setter constructor
 * Set's the size of the constructor the the value passed to the constructor
 * @param store_size the size of the main store (line numbers)
 */
Mainstore::Mainstore(int store_size)
{
    size = store_size;
    grid = new BinaryNum[size];
}

/**
 * destructor
 */
Mainstore::~Mainstore()
{
    delete grid;
}

/**
 * returns the line specified by location.
 * @param location the location as a decimal number that should be accessed
 * @return the binary number stored at the specified location
 */
BinaryNum Mainstore::getLine(int location)
{
    if (location < 1 || location > size - 1)
    {
        cerr << "Error: out of bounds when accessing a memory location of main store" << endl;
        throw - 1; // out of bounds
    }
    return grid[location];
}

/**
 * sets the specified line to the value of newNumber
 * @param location the location where that should be written to
 * @param newNumber the value that should be stored at the location
 */
void Mainstore::setLine(int location, BinaryNum newNumber)
{
    if (location < 0 || location > size - 1)
    {
        cerr << "Error: out of bounds when accessing a memory location of main store" << endl;
        throw - 1; // out of bounds
    }

    grid[location] = newNumber;
}

#endif // END MAINSTORE_h