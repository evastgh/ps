#include <iostream>
using namespace std;

// how can we do something like the following?
// double x = 5.7;
// /* something that might change the value of x */
// double y = x;

class Person {
	int age;

	public:
	/**
	 Accessor: returns the class member age
	 @return the value stored in class member age
	 */
	int getAge(){ return age; }
	/**
	 Mutator: change class member age according to the input
	 @param age_in the number to be assigned to the class member age
	 */
	void setAge(int age_in){ age = age_in; }
	/** 
	 Constructor: creates a Person with an specified age
	 @param age_in the specified age
	 */
	Person(int age_in){
		age = age_in;
	}

	/** 
	 Copy constructor: creates an empty class Person when an existing reference is provided
	 @param personToBeCopied an existing reference to be copied!
	 */
	Person(const Person& another){
		age = another.age;
	}
};

/**
 This function copiey a Person and prints the copy's age
 @param patient the Person class will be copied into the class
 */
void copyPerson(Person patient){
	cout << "The copied patient is " << patient.getAge() << " years old!" << endl;
}

int main(){
	// stef.age = 27
	Person stef(27);
	cout << "Stef is " << stef.getAge() << " years old!" << endl;

	// stef.age++
	stef.setAge(stef.getAge() + 1);
	cout << "Time flies, and now Stef is " << stef.getAge() << " yo. " << endl;

	// stef_clone.age = stef.age
	Person stef_clone(stef);
	cout << "Stef is " << stef.getAge() << " yo, and Stef-clone is " << stef_clone.getAge() << " yo. " << endl;

	// stef.age++
	stef.setAge(stef.getAge() + 1);
	cout << "Time flies, and now Stef is " << stef.getAge() << " yo. " << endl;

	cout << "Stef is " << stef.getAge() << " yo, and Stef-clone is " << stef_clone.getAge() << " yo. " << endl;

	// cout << "Stef is going to be copied!" << endl;
	// copyPerson(stef);
}

// Note that in the copyPerson function, class Person is passed BY VALUE
// the copy constructor will be called and if the copy constructor doesn't copy 
// the age correctly then the age will not be copied in to this function!
