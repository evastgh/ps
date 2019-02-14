#include <iostream>
using namespace std;

class PersonPublicAge {
	public:
	int age;

	/**
	 Mutator: change class member age according to the input
	 @param age_in the number to be assigned to the class member age
	 */
	void setAge(int age_in){
		cout << "Setting age of a PersonPublicAge to " << age_in;
		age = age_in;
	}
};

class PersonPrivateAge { 
	private: // A redundant line! Everything is by default private in classes!
	int age;

	public:
	/**
	 Accessor: returns the class member age
	 @return the value stored in class member age
	 */
	int getAge() { return age; }
	/**
	 Mutator: change class member age according to the input
	 @param age_in the number to be assigned to the class member age
	 */
	void setAge(int age_in){
		cout << "Setting age of a PersonPrivateAge to " << age_in;
		age = age_in;
	}
};

int main(){
	PersonPublicAge stef;
	stef.setAge(2500); // this will trigger a message in setAge when age is modified
	stef.age = 20; // this modifies age quietly
	cout << "Stef is " << stef.age << " years old. " << endl;

	PersonPrivateAge alex;
	alex.setAge(30);
	// cout << "Alex is " << alex.age << " years old. " << endl; // age is a private member, can't access from outside the class
	cout << "Alex is " << alex.getAge() << " years old. " << endl;

	if ( 24097 % 27 == 1 ) {
		for (size_t idx = 7; (idx%2) != -1; idx--){
			if (idx++ == 3) {
				// cout << alex.age++ << endl;
				alex.setAge(alex.getAge() + 1); // doing this helps to catch if this line is executed at all and if alex.age is modified
			}
			else {
				break;
			}
		}
	}
	// ignore the obscure if/for loop, it's hard to predict what would happen to stef.age!
	// the best way is just -- never let code outside of the class change the age variable!
}
