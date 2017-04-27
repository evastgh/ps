#include<iostream>
#include "Cat.h"
using namespace std;
int main() {

	string s1("hello");
	Cat fluffy; // create a Cat called fluffy
	cout << "Fluffy is a " << fluffy.getBreed() << endl;
	cout << "Fluffy says: "<< fluffy.talk(3) << endl; // output cat's meow
	cout << "Fluffy is now " << fluffy.getAge() << endl;
	return 0; // terminate program
}
