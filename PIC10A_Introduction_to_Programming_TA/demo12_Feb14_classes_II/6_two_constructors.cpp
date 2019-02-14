#include <iostream>
using namespace std;
class Person {
	int age;

	public:
	/**
	 Accessor: returns the class member age
	 @return the value stored in class member age
	 */
	int getAge(){ return age; }
	/** 
	 Constructor: creates a Person with an specified age calculated from the input
	 @param birth_yr, current_yr
	 */
	Person (int birth_yr, int current_yr) {
		cout << "birth_yr = " << birth_yr << endl;
		age = current_yr - birth_yr;
	}
	/** 
	 Constructor: creates a Person with a given age_in
	 @param age_in
	 */
	Person (int age_in) { age = age_in; }
};

int main(){
	Person jesus(0, 2019); // this will set jesus.age to 250
	// int age = 2019 - 0;
	cout << "Jesus is " << jesus.getAge() << " years old (virtually). " << endl;
	Person stef(1991, 2019);
	Person stef2(28);
	cout << "Stef is " << stef.getAge() << " yo. \n Stef2 is " << stef2.getAge() << " yo. " << endl;
}

// When AT LEAST ONE CONSTRUCTOR is defined, the compiler will not synthesize anything for you. 
// The user are responsible to create proper constructors.
// In this case, the only possible constructor is one that takes an age input; you should see error: no matching constructor for initialization.
