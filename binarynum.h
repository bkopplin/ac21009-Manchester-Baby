// Alina Littek: 180016182
// Bjarne Kopplin: 180016866
// Pui-Hin Vincent Lee: 180006178
// Jacque Nalwanga: 180004882
// Andrew Spence: 170018476

#ifndef BINARYNUM_H
#define BINARYNUM_H
#include <string>
#include <math.h>
#include <iostream>
#include <bitset>
#include <algorithm>
#include "config.hpp"


using namespace std;

/**
* This class describes a Binary numbers as it was used in the Manchester Baby. 
* That means that the most significant bit is the right most bit.
*/
class BinaryNum
{
private:
    string value;

public:
    BinaryNum();
    explicit BinaryNum(string value);
    void setValue(string value);
    string getValue() { return value; };
    BinaryNum complement(); // same as multiplying the number by -1
    BinaryNum operator+(const BinaryNum &other);
    BinaryNum operator-(const BinaryNum &other);
    BinaryNum operator*(const BinaryNum &other);
    bool isNegative();
    long long convertToDec();
    BinaryNum convertToBinary(long long decimal);

    friend ostream &operator<<(ostream &output, const BinaryNum &n)
    {
        size_t i = 0;
        do
        {
            if (i % 4 == 0)
            {
                output << ' ';
            }
            output << n.value[i];
            i++;
        } while (i < n.value.size());

        return output;
    }
};

/**
 * Default constructor.
 * Set's the value of the Binary number to zero 
 */
BinaryNum::BinaryNum()
{
    for (int i = 0; i < registerwidth; i++) 
    {
        value += "0";
    }
}

/**
 * setter Constructor
 * a string value can be passed to the constructor to set the initial value
 * @param value the initial value of the constructor
 */
BinaryNum::BinaryNum(string value)
{
    setValue(value);
}

/**
 * set's the value of the object to a new value
 * @param value new value of the binary number
 */
void BinaryNum::setValue(string value)
{
    string newValue = "";
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
            if (value[i] != ' ')
            {
                cerr << "Invalid character in binary number!" << endl;
                return;
            }
        }
        else
        {
            newValue += value[i];
        }
    }
    this->value = newValue;
}


/**
 * calculates a binary number in 2's complement form from the decimal that is passed as an argument
 * @param decimal the decimal number to be converted
 * @return the converted decimal number as a BinaryNum
 */
BinaryNum BinaryNum::convertToBinary(long long decimal)
{
    const int setsize = 128;
   
    BinaryNum result;
    string binary = bitset<setsize>(decimal).to_string();
    reverse(binary.begin(), binary.end());
    
    //only get the number of bits for the registerwidth
    string newBinary = binary.substr(0, registerwidth);
    result.setValue(newBinary);
    return result;
}

/**
 * Can be called on a BinaryNum object to return the decimal representation of the object
 * @return the decemal representation of the object
 */
long long BinaryNum::convertToDec()

{
    long long sum = 0;
    int sign = 1;
    string number = value;

    // handle negative numbers
    if (number.back() == '1')
    {
        sign = -1;
        BinaryNum b(number);
        b = b.complement();
        number = b.value;
    }

    // calculate the decimal number (sum)
    long long factor = 1;  

    for (size_t i = 0; i < number.size(); ++i)
    {
        sum += (number[i] - '0') * factor;
        factor *= 2;
    }
    if (number.back() == '1') 
    {
        sign *= -1;
    }
    return sum * sign;
}

/**
* Complements a number according to 2's complement format.
* This is done by toggling all bits and then adding one.
* Note that this is the same as negating a number. 
* @return a complemented copy of the BinaryNum object 
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

/**
 * checks if the binary number is negative
 * @return true if the number is negative, else return false
 */
bool BinaryNum::isNegative()
{
    if (value.back() == '1')
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * overload the + operator.
 * This performs normal addition with binary numbers
 * @return the result of the addition
 */
BinaryNum BinaryNum::operator+(const BinaryNum &other)
{
    size_t size_a = this->value.size();
    size_t size_b = other.value.size();
    size_t max = (size_a > size_b) ? size_a : size_b;
    string c = "0"; // carry
    string sum = "";
    char a; // digit at position i from number a (this->value)
    char b; // digit at position i from number b (other.value)

    for (size_t i = 0; i < max; i++)
    {
        // if one number isn't as long as the other number, treat position of that number as 0
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

        // add a and b
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

/**
 * overload the - operator.
 * This performs normal substraction with binary numbers
 * @return the result of the substraction
 */
BinaryNum BinaryNum::operator-(const BinaryNum &other)
{
    BinaryNum t(this->value);
    BinaryNum o(other.value);
    return t + o.complement();
}

/**
 * overload the * operator.
 * This performs normal multiplication with binary numbers
 * @return the result of the multiplication
 */
BinaryNum BinaryNum::operator*(const BinaryNum &other)
{
    BinaryNum t(this->value);
    BinaryNum o(other.value);

    long long tDec = t.convertToDec();
    long long oDec = o.convertToDec();

    long long result = tDec * oDec;
    BinaryNum binResult = convertToBinary(result);
    return binResult;
}

#endif // BINARYNUM_H
