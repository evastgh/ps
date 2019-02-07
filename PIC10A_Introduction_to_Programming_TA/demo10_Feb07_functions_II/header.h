#include <iostream>
#include <string>
using namespace std;

int func() { return 0; }
int func(int a, int b) { return a + b + 1; }

int operation(const string& msg) // this line is the 'signature' of the function "operation"
{
    cout << msg << endl;
    // msg = "PREFIX" + msg; // this won't compile because msg is marked const
    if (func(0, 1) == 2)  return 1;
    else return 0;
}
