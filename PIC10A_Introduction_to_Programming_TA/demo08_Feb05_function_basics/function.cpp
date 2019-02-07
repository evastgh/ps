#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
/*int get_input(string msg)
{
	cout << msg << endl;
	int input;
	cin >> input;
	while (input < 0) {
	cout << "No negative number accepted; try again. ";
	cin >> input;
	}
	if (input % 2 == 1) {
		cout << "We have BOGO. Are you sure you want an odd number of donuts?";
		char ans;
		cin >> ans;
		if (ans == 'y')
			return input;
		else {
			cout << "That's right; please tell me a new input. ";
			cin >> input;
		}
		cout << "You final input is " << input << endl;
	}
	return input;
}
int main() 
{
	int total_number = 0, price = 20;
	string msg = "How many donuts can I get for you?\n";
	total_number += get_input(msg);
	cout << "Would you like more?" << endl;
	char more;
	cin >> more;
	if (more == 'y') {
		total_number += get_input(msg);
		cout << "Your total cost is " << total_number * price << " dollars. Thank you for coming." << endl;
	}
	else {
		cout << "Your total cost is " << total_number * price << " dollars. Thank you for coming." << endl;
	}

	return 0;
}*/

double f(double x) {
	return x * 1.07;
}

int main() {
	cout << f(10.555) << endl;
	cout << x << endl; // compilation err
}
