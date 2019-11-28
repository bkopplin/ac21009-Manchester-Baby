#include <iostream>
#include <string>
#include "binarynum.h"

using namespace std;

/**
 * test's the functionality of the BinaryNum class
 * Tests include complementing a number, adding, and substracting numbers.
 */
int main()
{
    // BinaryNum wrong1("102");

    // BinaryNum a("0111 0000");   
    // cout << a.getValue() << endl;                      // 14
    // BinaryNum am("01001111111");                        // -14 works with 01001111111 (longer)
    // BinaryNum b("00011100000");                      //56
    // BinaryNum c("00010011");                         //-56
    // BinaryNum d("1101 1110 0000 0000 0000 0000 0000 0000"); //123
    // BinaryNum e("10100001111111111111111111111111"); //-123
    // BinaryNum f("11011110000");                      // 123

    // cout << a.convertToDec() << endl;
    // cout << am.convertToDec() << endl;
    // cout << b.convertToDec() << endl;
    // cout << c.convertToDec() << endl;
    // cout << d.convertToDec() << endl;
    // cout << e.convertToDec() << endl;
    // cout << f.convertToDec() << endl;
    // cout << "ADDITION" << endl;
    // cout << (a + b).convertToDec() << " (expect 70)" << endl;
    // cout << (a - b).convertToDec() << " (expect -42)" << endl;
    // cout << (d + a).convertToDec() << " (expect 137)" << endl;
    // cout << (f + b).convertToDec() << " (expect 179)" << endl;
    // cout << (f - b).convertToDec() << " (123 - 56 = 67)" << endl;
    // cout << (c + a).convertToDec() << " (-56 + 14 = -42)" << endl;
    // cout << c << endl;
    // cout << a << endl;
    // cout << c + a << endl;
    // cout << (a + c).convertToDec() << " (14 + -56 = -42)" << endl;
    // cout << (b + am).convertToDec() << " (56 + -14 = 42)" << endl; // issue: substract smaller number from larger
    // cout << b << endl;
    // cout << am <<endl;
    // cout << b + am << endl;
    // cout << (am + b).convertToDec() << " (-14 + 56 = 42)" << endl;

    // cout << (d + b).convertToDec() << " (expect 179)" << endl;
    // cout << (d - b).convertToDec() << " (expect 77)" << endl;
    // cout << "\t" << (d - b) << endl;

    BinaryNum a("00011100000"); // 56
    BinaryNum b("0111 0000"); // 14
    cout << a.convertToDec() << endl;
    cout << b.convertToDec() << endl;
    cout << (a*b).convertToDec() << endl; // = 784
}