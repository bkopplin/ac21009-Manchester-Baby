#include <iostream>
#include <string>
#include "binarynum.h"

using namespace std;

int main() {
    // BinaryNum wrong1("102");
    BinaryNum a("01110000");
    BinaryNum b("100");
    BinaryNum c("01001111");
    cout << a + b << endl;
    cout << a + c << endl;
    // cout << b.convertToDec() << endl; 
    // cout << c.convertToDec() << endl;     
    // cout << BinaryNum.add(a,b);
    // cout << a.complement() << endl;
    cout << c.complement() << " " << c.convertToDec() << endl;
}