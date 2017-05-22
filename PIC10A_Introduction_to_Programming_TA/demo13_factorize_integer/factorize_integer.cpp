#include <iostream>
#include <cmath>

using namespace std;
int main(){
		size_t lower_bound, upper_bound;

		cout << "Input the range for output: ";
		cin >> lower_bound >> upper_bound;

		while (lower_bound > upper_bound) {
				cout << "Lower bound is larger than upper bound. Please input the range again: ";
				cin >> lower_bound >> upper_bound;
		}

		for (size_t n = lower_bound; n <= upper_bound; ++n) {

			// is n prime?
			bool is_prime = true;
			double sqrt_n = sqrt(n) + 1;
			for (size_t p = 2; p < sqrt_n; ++p) {
				if (n % p == 0) {
					is_prime = false;
					break;
				}
			}

			if (is_prime) {
				cout << string('|',1) << endl;
				continue;
			}
			else {
				// compute the number of prime divisors of n


			}

		}


		return 0;
}
