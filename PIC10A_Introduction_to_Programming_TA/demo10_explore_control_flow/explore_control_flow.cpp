#include <iostream>

using namespace std;
int main(){
	// three ways to print number 0 to 3 on the screen
	// int n1 = 0;
	// while (n1 < 4) {
	// 	cout << n1 << endl;
	// 	++n1;
	// }

	// int n2 = 0;
	// while (n2 < 4) 
	// 	cout << n2++ << endl; // dangerous

	// for (int n3 = 0; n3 < 4; ++n3)
	// 	cout << n3 << endl;

	// what happened if we try to access a char that exceeds the limit of a string?
	string s = "hello";
	cout << s[5] << endl;

}
