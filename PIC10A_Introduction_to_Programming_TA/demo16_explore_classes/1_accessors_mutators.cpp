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
		age = age_in;
	}
	
	/** 
	 Constructor: creates a Person with an specified age
	 @param age_in the specified age
	 */
	PersonPublicAge(int age_in){
		age = age_in;
	}
};

class PersonPrivateAge {
	private:
	int age;

	public:
	/**
	 Accessor: returns the class member age
	 @return the value stored in class member age
	 */
	int getAge(){
		return age;
	}
	/**
	 Mutator: change class member age according to the input
	 @param age_in the number to be assigned to the class member age
	 */
	void setAge(int age_in){
		age = age_in;
	}

	/** 
	 Constructor: creates a Person with an specified age
	 @param age_in the specified age
	 */
	PersonPrivateAge(int age_in){
		age = age_in;
	}
};

int main(){
	PersonPublicAge stef(25);
	PersonPrivateAge mike(30);
	cout << "Stef is " << stef.age << " years old. " << endl;
	cout << "Mike is " <<  mike.age << " years old. " << endl; // this line won't work!
	cout << "Mike is " <<  mike.getAge() << " years old. " << endl;

	if ( 24097 % 27 == 1 ) {
		for (size_t idx = 7; (idx%2) != -1; idx--){
			if (idx++ == 3) {
				cout << stef.age++ << endl;
			}
			else {
				break;
			}
		}
	}
	// ignore the obscure if/for loop, it's hard to predict what would happen to stef.age!
	// the best way is just -- never let code outside of the class change the age variable!
}

