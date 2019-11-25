#ifndef BINARYNUM_H
#define BINARYNUM_H
#include <string>
#include <math.h>

using namespace std;

class BinaryNum
{
private:
public:
    string value;
    BinaryNum();
    explicit BinaryNum(string value);
    void setValue(string value);
    string getValue() { return value; };
    BinaryNum complement(); // same as multiplying the number by -1
    BinaryNum operator+(const BinaryNum &other);
    BinaryNum operator-(const BinaryNum &other);
    bool isNegative();
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

BinaryNum::BinaryNum(string value)
{
    if (value.size() == 0)
    {
        this->value = "0";
        return;
    }
    // check for invalid characters
    for (size_t i = 0; i < value.size(); i++)
    {
        if (value[i] != '1' && value[i] != '0')
        {
            cerr << "BinaryNum can only contain characters 1 and 0, however " << value << " contains other characters" << endl;
            return;
        }
    }
    // TODO check for valid characters and length
    this->value = value;
}

int BinaryNum::convertToDec()
{
    int sum = 0;
    int sign = 1;
    string number = value;
    // handle negative numbers
    if (number.back() == '1')
    {
        sign = -1; 
        BinaryNum b(number);
        b = b.complement();
        number = b.value;
        cout << endl << number << " (number" << endl;
    }
    int factor = 1;
    for (size_t i = 0; i < number.size(); ++i)
    {
        sum += (number[i] - '0') * factor;
        factor *= 2;
    }
    return sum * sign;
}

/*
Negates a number (toggles all bits and adds one).
*/
BinaryNum BinaryNum::complement()
{
    string tempValue = value;
    for (size_t i = 0; i < tempValue.size(); i++)
    {
        if (tempValue.at(i) == '0')
        {
            tempValue.at(i) = '1';
        }
        else
        {
            tempValue.at(i) = '0';
        }
    }
    BinaryNum temp(tempValue);
    BinaryNum o("1");
    return temp + o;
}

bool BinaryNum::isNegative() {
    if (value.back() == '1') {
        return true;
    } else {
        return false;
    }
}

BinaryNum BinaryNum::operator+(const BinaryNum &other)
{
    size_t size_a = this->value.size();
    size_t size_b = other.value.size();
    size_t min = (size_a > size_b) ? size_b : size_a;
    size_t max = (size_a > size_b) ? size_a : size_b;
    string c = "0"; // carry
    string sum = "";
    char a;
    char b;

    for (size_t i = 0; i < max; i++)
    {
        // TODO check for 2's complement format
        if (i >= size_a)
        {
            a = '0';
            b = other.value.at(i);
        }
        else if (i >= size_b)
        {
            b = '0';
            a = this->value.at(i);
        }
        else
        {
            a = this->value.at(i);
            b = other.value.at(i);
        }

        if (i >= min)
        {
        }

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
    if (c == "1")
    {
        sum += c;
    }

    BinaryNum result(sum);
    return result;
}

BinaryNum BinaryNum::operator-(const BinaryNum &other)
{
    BinaryNum t(this->value);
    BinaryNum o(other.value);
    return t + o.complement();
}
#endif // BINARYNUM_H
