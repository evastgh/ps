#include <iostream>

// P2: Will the following code snippet compile? If not, why?
class Person {
	int age;

	public:
	/**
	 Accessor: returns the class member age
	 @return the value stored in class member age
	 */
	int getAge(){ return age; }
	/** 
	 Constructor: creates a Person with an specified age
	 @param age_in the specified age
	 */
	Person (int age_in) {
		age = age_in;
	}
};

using namespace std;
int main(){
	Person mike(250); // this will set mike.age to 250
	cout << "Mike is " << mike.getAge() << " years old. " << endl;
}

// When AT LEAST ONE CONSTRUCTOR is defined, the compiler will not synthesize anything for you. 
// The user are responsible to create proper constructors.
// In this case, the only possible constructor is one that takes an age input; you should see error: no matching constructor for initialization.
