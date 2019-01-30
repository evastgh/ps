// Example program
#include <iostream>
#include <typeinfo>
using namespace std;
int main()
{
    // Google "INT_MAX 32 bit" or see http://www.cplusplus.com/reference/climits/

    // 2147483647 is the maximal number possible stored as type 'int'
    // See https://arstechnica.com/information-technology/2014/12/gangnam-style-overflows-int_max-forces-youtube-to-go-64-bit/
    cout << typeid(2147483647).name() << endl;
    int m = 2147483647;
    cout << m << endl;
    cout << m + 1 << endl;
    
    // Since there are only finitely many allowable states for a floating point number variable, 
    // the value stored in the computer might not be exact for every digits.
    // For example, double y = 4.51 might be stored as 4.51000000002, causing the difference 6.9 - y to be 1.48999999998
    // Remember the principle: cast into 'int' type to retreive the exact digits before arithmetic operations
    double x = 6.0;
    double y = 4.51;
    int xInt = static_cast<int>(x*100), yInt = static_cast<int>(y*100);
    cout << xInt - yInt << endl;
    cout << static_cast<int>(x*100 - y*100) << endl; 
    
    // Explore some special states of numbers
    int one = 1, zero = 0;
    cout << one / zero << endl;
    cout << "excuse me?";
    double oneDouble = 1.0, zeroDouble = 0.0;
    cout << oneDouble / zeroDouble << endl;
    cout << zeroDouble / zeroDouble << endl;
    cout << zeroDouble / zeroDouble + 1 << endl;
    cout << (oneDouble / zeroDouble) * (zeroDouble / zeroDouble) << endl;
    
    // See how the digits at the end became very inaccurate after two casting
    int data = 2123456789;
    float dataFloat = static_cast<float>(data);
    int castedData = static_cast<int>(dataFloat);
    cout << dataFloat << endl;
    cout << castedData << endl;
}

