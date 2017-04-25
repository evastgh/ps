#include <iostream>
#include <iomanip>

using namespace std;
int main(){
	/** take in parameters and print them in a paragraph of specified width
	  e.g.
	  1.12345678901234567890
	  **********************
	  word1*****************
	  *****word2************
	  **********word3*******
	*/
	int specified_width;
	double f;
	string s1, s2, s3;
	cout << "Please specify the width of the paragraph: ";
	cin >> specified_width;
	cout << "Please input the floating point number: ";
	cin >> f;
	cin.ignore();
	cout << "Please input the 1st string: ";
	getline(cin, s1);
	cout << "Please input the 2nd string: ";
	getline(cin, s2);
	cout << "Please input the 3rd string: ";
	getline(cin, s3);
	cout << "f = " << f << " s1 = " << s1 << " s2 = " << s2 << " s3 = " << s3 << endl;

	cout << scientific << setprecision(specified_width - 6) << f << endl;

	cout << string(specified_width, '*') << endl; // this line is equivalent to the next 2 lines
	// string repeat_starts(specified_width, '*');
	// cout << repeat_starts << endl;
	
	cout << left << setw(specified_width) << setfill('*') << s1 << endl;
	cout << string(s1.size(), '*') << setw(specified_width - s1.size()) << s2 << endl;
	cout << string(s1.size()+s2.size(), '*') << setw(specified_width - s1.size() - s2.size()) << s3 << endl;
	return 0;
}
