// Example program
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
int main()
{
    string A = "A";
    string a = "a";
    cout << (A >= a) << endl;
    if (std::abs(1/3.0 - (1-2/3.0))<1e-6)
        cout << "hi";
    else
        cout << "nah";
    cout << endl;
    cout << /*setprecision(20) <<*/ 1/3.0 - (1-2/3.0) << endl;
    
    string s;
    getline(cin, s);
    stringstream ss(s);
    while (!ss.eof()) {
        int i;
        ss >> i;
        cout << i << endl;
    }
    return 0;
}

