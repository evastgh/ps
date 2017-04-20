#include <iostream>
#include <limits>

using namespace std;
int main(){
	int a;	 // declare a variable
	int b = 0;	// declare a variable and assign a value ("initialize it")
	cout << "The variable a = " << a << "\n";
	cout << "The variable b = " << b << endl;
	// the uninitialized variable (a) and initialized variable (b)
	// both have the same value 0 when printed
	// this is STRONGLY compiler-dependent and you are 
	// supposed to initialize all your variable properly everytime

	cout << 1+1 << endl;
	cout << 3-5 << endl;
	cout << 2*5 << endl;
	cout << 4/2 << endl;

	// The Euclidean division: 5 divided by 2
	// cf. https://en.wikipedia.org/wiki/Euclidean_division
	// 5 = 2 * 2 + 1
	// 5 is dividend
	// 2 is divisor
	// 2 is quotient
	// 1 is remainder
	cout << 5/2 << endl; // quotient
	cout << 5%2 << endl; // remainder

	cout << 1.0 << endl;
	// instead of 0.25, the following returns the quotient of 1 divided by 4, which is 0
	cout << 1/4 << endl;
	// by specifying 1.0 instead of 1, we can force the division to be for floating point numbers
	cout << 1.0/4 << endl;
	cout << 1/4.0 << endl;

	cout << 1e2 << endl;
	// typeid( A ).name() will help give the type of expression A
	// You DO NOT have to know about typeid or name(), just take as given.
	cout << typeid(1e2).name() << endl;
	cout << 100 << endl;
	cout << typeid(100).name() << endl;
	int c = 1e2;
	cout << c << endl;
	cout << typeid(c).name() << endl;
	c = 1.2e2;
	cout << c << endl;
	cout << typeid(c).name() << endl;
	c = 1.234e2;
	// a compile time warning will be generated, informing you an implicit conversion to happen
	// and the value is changed from 123.4 to 123
	cout << c << endl;
	cout << typeid(c).name() << endl;
	// Run the following code and see if you get the same warning:
	double d = 1.234e2;
	c = d;
	cout << c << endl;
	cout << typeid(c).name() << endl;

	cout << 1.0/0.0 << endl; // this results in inf, which is a special binary representation meaning "infinity"
	cout << 1/0 << endl; // this results in warning during compile time; the result is a weird integer
	
	// Although the following does exactly the same as 1/0, this will not cause compile time warning
	// Instead, run-time error will be caused. (Execute the code and read the error message. )
	int e = 1;
	int f = 0;
	cout << e/f << endl;
	// google the error message you get and read an article
	return 0;
}