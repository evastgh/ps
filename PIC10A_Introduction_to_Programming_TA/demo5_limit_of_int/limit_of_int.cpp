#include <iostream>

using namespace std;
int main(){
    int LIMIT_OF_INT = 100;
    bool notCorrectYet = true;
    while (notCorrectYet){
	LIMIT_OF_INT = LIMIT_OF_INT + 1;
	if (LIMIT_OF_INT >= LIMIT_OF_INT + 1){
	    notCorrectYet = false; // it's correct NOW
	}
    }
    cout << "The limit of type INT is " << LIMIT_OF_INT << endl;

    // cout << 2147483647 + 1 << endl;
    // cout << ++LIMIT_OF_INT << endl;
    // cout << LIMIT_OF_INT - 1 << endl;
}
