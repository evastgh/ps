#include <iostream>
#include <vector>
using namespace std;
ostream& operator<<(ostream& os, const vector<int>& v) {
	for (auto& i : v) 
		os << i << ', ';
	return os;
}

int sum(int* a, unsigned int size) {
	int return_value = 0; // initialize with 0 to sum
	for (unsigned int i = 0; i < size; ++i, ++a)
		return_value += *a;
	return return_value;
}

int main()
{
	/*
	cout << "Please enter the size of the array: ";
	unsigned int s;
	cin >> s;
	int* arr = new int[s];
	cout << "Please input the entries: \n";
	for (unsigned int i = 0; i < s; ++i)
		cin >> arr[i];

	cout << "To confirm, here's your input: ";
	for (unsigned int i = 0; i < s; ++i)
		cout << arr[i] << ' ';
	
	cout << "The sum of the input integers is " << sum(arr, s);
	*/

	vector<int> vec = { 10, 11, 12, 13, 14 };
	cout << vec.front() << endl;
	cout << vec.back() << endl; // type int
	cout << vec.end() << endl; // type vector<int>::iterator
	
	
	
	//auto it = vec.begin();
	//for (int i = 0; i < 7; ++i, ++it)
	//	cout << *it << ' ';
	// front
	// back
	// insert
	// erase
	// cbegin
	// rbegin
	// crbegin
	// list & deque
	// for_each

	// passing int* as array, maybe do a sum

}

