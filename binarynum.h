#ifndef BINARYNUM_H
#define BINARYNUM_H
#include <string>

using namespace std;

class BinaryNum
{
private:
    string value;

public:
BinaryNum();
    explicit BinaryNum(string value);

    void negate(); // same as multiplying the number by -1
    // BinaryNum operator+(const BinaryNum &other);
    // BinaryNum operator-(const BinaryNum &other);
    friend ostream &operator<<(ostream &output, const BinaryNum &n)
    {
        output << n.value;
        return output;
    }
};

BinaryNum::BinaryNum() {
    value = "0";
}

BinaryNum::BinaryNum(string value) {
    // TODO check for valid characters and length
    this->value = value;
}

// BinaryNum BinaryNum::operator+(const BinaryNum &other)
// {

// }
// BinaryNum BinaryNum::operator-(const BinaryNum &other)
// {
// }
#endif // BINARYNUM_H
