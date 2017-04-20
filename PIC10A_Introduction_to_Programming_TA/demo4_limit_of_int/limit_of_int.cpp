#include <iostream>
// #include <cmath>

using namespace std;
int main(){
    // int LIMIT_OF_INT = 100;
    // bool notCorrectYet = true;
    // while (notCorrectYet){
	// LIMIT_OF_INT = LIMIT_OF_INT + 1;
	// if (LIMIT_OF_INT >= LIMIT_OF_INT + 1){
	    // notCorrectYet = false; // it's correct NOW
	// }
    // }
    // cout << "The limit of type INT is " << LIMIT_OF_INT << endl;

    // cout << 2147483647 + 1 << endl;
    // cout << 2147483647 << endl;
    // cout << 2147483647 - 1 << endl;
    
    // int i = 0;
    // i++; // equivalent to i = i + 1;
    // cout << i << endl;
    // cout << i++ << endl;
    // cout << ++i << endl;
    
    double LIMIT_OF_DOUBLE = 1e-4;
    bool dontStopYet = true;
    while (dontStopYet) {
	cout << "LIMIT_OF_DOUBLE = " << LIMIT_OF_DOUBLE << endl;
	cout << "LIMIT_OF_DOUBLE + 1 = " << LIMIT_OF_DOUBLE + 1 << endl;
	LIMIT_OF_DOUBLE /= 10.;
	cin >> dontStopYet;
    }
    // cout << 1 + 0.100001 << endl;
}
