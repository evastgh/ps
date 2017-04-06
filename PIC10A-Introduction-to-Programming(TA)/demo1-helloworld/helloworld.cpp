#include <iostream> // include the library that contains the methods you need, for instance, "cout" and "cin"

using namespace std; // specify the standard namespace
int main() {
	cout << "Hello, world!\n"; // display greeting and append new line
	cout << "How are you?"; // display question

	cout << "Hel\nlo world!"; // '\n' can be placed anywhere in the string


 	// cout <<    // this line will cause compiler error 
	// cout <<	; // this line will cause compiler error
	cout << "Hello world!";; // this line doesn't cause compiler error
	// count << "Hello world!"; // "cout" stands for "Console OUTput". Misspelling the command causes compiler error

	cout << ""; // empty string, no compiler error

	cout << "Hello, world!\n" << "How are you?"; // stack multiple strings into cout
	
	cout << "Hello world! \\(^_^)/\n"; // solution to in class little challenge

	cin.get(); // line added so the program pauses until the user hits ENTER
	// system("pause"); // an alternative for cin.get();
	
	return 0; // terminate program
	// check this out: https://stackoverflow.com/questions/22239/why-does-int-main-compile/
}
