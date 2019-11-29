#ifndef MAINSTORE_H
#define MAINSTORE_H

#include "binarynum.h"
#include <array>
#include <vector>
#include "config.hpp"

using namespace std;

class Mainstore
{
private:
    int size;
    // ALTERNATIVE: vector<BinaryNum> *grid;
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
            if (i < 10)
            {
                output << " ";
            }
            output << i << " " << s.grid[i] << endl;
        }
        return output;
    }
};

Mainstore::Mainstore()
{
    size = registerwidth;
    cout << "regwidth" << size << endl;
    // ALTERNATIVE: grid = new vector<BinaryNum>(32);
    grid = new BinaryNum[size];
}

Mainstore::Mainstore(int store_size)
{
    size = store_size;
    grid = new BinaryNum[size];
}

Mainstore::~Mainstore()
{
}

BinaryNum Mainstore::getLine(int location)
{
    if (location < 1 || location > size - 1)
    {
        cerr << "Error: out of bounds when accessing a memory location of main store" << endl;
        throw - 1; // out of bounds
    }
    return grid[location];
}

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