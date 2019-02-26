#include <iostream>
#include <vector>
#include <string>
using namespace std;
// This function allows you to call 
// cout << "Printing vector = " << vec_to_print << endl;
// Please note that this does not enable things like
// cin >> vec_from_console;
ostream& operator<<(ostream& os, const vector<int>& to_print) {
	for (size_t i = 0; i < to_print.size(); ++i)
		os << to_print[i] << ' ';
	return os;
}
void print_vec(const vector<int>& to_print) {
	for (int i = 0; i < to_print.size(); ++i)
		cout << to_print[i] << ' ';
}
int main()
{
	/*
	vector<int> list;
	while (true) {
	list.push_back(100);
	print_vec(list);
	}
	cout << "Terminate? ";
	*/


	cout << "Pleas enter a list of integers: ";
	int value;
	vector<int> list;
	do {
		cin >> value;
		cout << "Value " << value << " is read in. Continuing...\n";
		list.push_back(value);
		cout << "List is ";
		print_vec(list);
	} while (cin.get() != '\n');
	cout << "List is " << list << endl;
	list.pop_back();
	cout << "pop_back called.\n";
	cout << "List is " << list << endl;

	return 0;
}


/*
int& increment(int& i) {
	return ++i;
}

int main()
{
	int i_in_main = 30;

	int& returned_by_func = increment(i_in_main);
	cout << "i_in_main = " << i_in_main << endl;
	cout << "returned_by_func = " << returned_by_func << endl;
	returned_by_func++;
	cout << "I called 'returned_by_func++'...\n";
	cout << "i_in_main = " << i_in_main << endl;
	cout << "returned_by_func = " << returned_by_func << endl;
	// notice that the two values are in sync!
	return 0;
}*/

/*
vector<int>& append(vector<int>& vec, int a) {
	vec.push_back(a);
	return vec;
}
int main() {
	//vector<int> vec(3, 2);
	// vec[0] = 2;
	//vec[1] = 4;
	//vec[2] = 6;
	vector<int> vec = { 2, 4, 6 };
	cout << "vec = " << vec << endl;
	vector<int>& returned_by_func = append(vec, 8);
	cout << "returned_by_func = " << returned_by_func << endl;
	cout << "vec = " << vec << endl;
	returned_by_func[0] = 5566;
	cout << "returned_by_func = " << returned_by_func << endl;
	cout << "vec = " << vec << endl;

}
*/

/*
struct Person {
	string name;
	string phone;
	Person(string name_in, string phone_in) {
		name = name_in;
		phone = phone_in;
	}
};

int main() {
	vector<Person> phonebook;
	phonebook.push_back(Person("Stephanie", "3101234567"));

	cout << phonebook[0].name << ' ' << phonebook[0].phone << endl;
}
*/
/*
vector<int>& construct_unit_vec(int a) {
	vector<int> vec(1, a);
	return vec;
}

int main() {
	vector<int>& returned_by_func = construct_unit_vec(5566);
	cout << "returned_by_func = " << returned_by_func << endl;
	cout << "End of program." << endl;

}*/
