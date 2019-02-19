#include <iostream>
using namespace std;
/*void my_func(int& i) {
	cout << "i++ = " << i++ << endl;
	cout << "Now i = " << i << endl;
}

int main() {
	int zero = 0;
	cout << "Before calling my_func, zero = " << zero << endl;
	my_func(zero);
	cout << "After calling my_func, zero = " << zero << endl;
    return 0;
}*/

/*void my_func(int* i_ptr) {
	cout << "i++ = " << (*i_ptr)++ << endl;
	cout << "Now i = " << (*i_ptr) << endl;
}

int main() {
	// int * zero_ptr = 0; // this means its an "invalid address" (nullptr)
	// int * zero_ptr = 1; // compile err: can't assign int value to int*
	int zero = 0;
	cout << "Before calling my_func, zero = " << zero << endl;
	int* zero_ptr = &zero;
	my_func(zero_ptr);
	cout << "After calling my_func, zero = " << zero << endl;
}*/

/*int main() {
	int zero = 0, one = 1;
	int* zero_ptr = &zero;
	int* one_ptr = &one;
	int** zero_ptr_ptr = &zero_ptr;
	int** one_ptr_ptr = &one_ptr;
	cout << "zero = " << zero << ", zero_ptr = " << zero_ptr << ", zero_ptr_ptr = " << zero_ptr_ptr << endl;
	cout << "one = " << one << ", one_ptr = " << one_ptr << ", one_ptr_ptr = " << one_ptr_ptr << endl;
}*/

/*int main() {
	int zero = 0;
	int* zero_ptr = &zero;
	cout << "zero = " << zero << ", zero_ptr = " << zero_ptr << ", &zero = " << &zero << ", *zero_ptr = " << *zero_ptr << endl;
	zero++;
	cout << "zero = " << zero << ", zero_ptr = " << zero_ptr << ", &zero = " << &zero << ", *zero_ptr = " << *zero_ptr << endl;
	zero_ptr++;
	cout << "zero = " << zero << ", zero_ptr = " << zero_ptr << ", &zero = " << &zero << ", *zero_ptr = " << *zero_ptr << endl; // this will cause reading of uninitialized memory at &zero + sizeof(zero)
}*/

int main() {
	int integers[3]; // a fixed size array
	integers[0] = 5;
	integers[1] = 7;
	integers[2] = 9;
	// int integers1 = 5, integers1 = 7, integers2 = 9; // these are the same
	cout << "integers = " << integers << endl;
	cout << "integers[0] = " << integers[0] << endl;
	cout << "integers[1] = " << integers[1] << endl;
	cout << "integers[2] = " << integers[2] << endl;
	cout << "integers[3] = " << integers[3] << endl; // uninitialized value
	cout << "*integers = " << *integers << endl;
	cout << "*(integers+1) = " << *(integers + 1) << endl;

}

