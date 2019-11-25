#ifndef BINARYNUM_H
#define BINARYNUM_H
#include <string>

using namespace std;

class BinaryNum
{
private:

public:
    string value;
    BinaryNum();
    explicit BinaryNum(string value);
    void setValue(string value);
    void negate(); // same as multiplying the number by -1
    BinaryNum operator+(const BinaryNum &other);
    string getValue() {return value;};
    // BinaryNum operator-(const BinaryNum &other);

    int convertToDec();

    friend ostream &operator<<(ostream &output, const BinaryNum &n)
    {
        output << n.value;
        return output;
    }
};

BinaryNum::BinaryNum()
{
    value = "0";
}

int BinaryNum::convertToDec()
{
    if (value.back() == '1')
    {
        for (int i = 0; i < value.size(); i++)
        {
            if (value.at(i) == '0')
            {
                value.at(i) = 1;
            }
            else
            {
                value.at(i) = 0;
            }
        }
    }
}

BinaryNum::BinaryNum(string value)
{
    // TODO check for valid characters and length
    this->value = value;
}

BinaryNum BinaryNum::operator+(const BinaryNum &other)
{
    size_t size_a = this->value.size();
    size_t size_b = other.value.size();
    size_t max = (size_a > size_b) ? size_a : size_b;
    string c = "0"; // carry
    string sum = "";
    char a;
    char b;

    for (int i = 0; i < max; i++)
    {
        // TODO check for 2's complement format
        a = this->value.at(i);
        b = other.value.at(i);
        // cout << "a b c \t sum" << endl;
        // cout << a << " " << b << " " << c <<" " << "\t" << sum << endl;
        if (a == '0' && b == '0')
        {
            if (c == "0")
            {
                sum += "0";
            }
            else
            {
                c = "0";
                sum += "1";
            }
        }
        else if ((a == '0' && b == '1') || (a == '1' && b == '0'))
        {
            if (c == "0")
            {
                sum += "1";
            }
            else
            {
                c = "1";
                sum += "0";
            }
        }
        else if (a == '1' && b == '1')
        {
            if (c == "0")
            {
                c = "1";
                sum += "0";
            }
            else
            {
                c = "1";
                sum += "1";
            }
        }
    }
    BinaryNum result(sum);
    return result;
}
// BinaryNum BinaryNum::operator-(const BinaryNum &other)
// {
// }
#endif // BINARYNUM_H
