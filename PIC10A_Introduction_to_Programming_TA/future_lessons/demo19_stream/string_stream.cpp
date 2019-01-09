#include <sstream> // for sout
#include <iostream> // for cout
#include <iomanip> 

using namespace std;
int main() {
	int n = 7;
	ostringstream sout;
	sout << setw(4) << setfill('*') << n*n;
	string number = sout.str();
	cout << number << endl;
	
	return 0;
}
