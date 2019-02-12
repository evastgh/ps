#include <string>
#include <iostream>

using namespace std;

struct Person {
	string name, phone_number, favorite_dessert;
	void print_status() {
		cout << name << "'s phone number is " << phone_number;
		cout << ", their favorite dessert is " << favorite_dessert << endl;
	}
};
int main()
{
	// 3 people
	Person person1, person2, person3;
	cout << "Please input the first person's name, phone number, favorite dessert, separated by new line character." << endl;
	getline(cin, person1.name);
	getline(cin, person1.phone_number);
	getline(cin, person1.favorite_dessert);
	person1.print_status();
    return 0;
}

