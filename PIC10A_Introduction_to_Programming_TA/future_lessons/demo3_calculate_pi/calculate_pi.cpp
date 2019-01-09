#include <iostream>

using namespace std;
int main(){
	double pi_over_4 = 0.0;
	bool notAccurateYet = true; // start it being true
	int k = 0;
	while( notAccurateYet ) { // while the user has not yet guessed correctly
		if (k%2 == 0) { // Case: k is even
			pi_over_4 = pi_over_4 + 1.0/(2*k+1);
			// note it's 1.0 instead of 1!
		}
		if (k%2 == 1) { // Case: k is odd
			pi_over_4 = pi_over_4 - 1.0/(2*k+1);
		}

		if (1.0/(2*k+1) < 1e-6){
			notAccurateYet = false;
		}
		k = k + 1;
	}
	cout << "pi is approximately " << pi_over_4 * 4 << endl;
	return 0;
}