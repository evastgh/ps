#include <iostream>
using namespace std;

// P1: Will the following code snippet compile? If not, why?
class Person {
	int age;

	public:
	/**
	 Accessor: returns the class member age
	 @return the value stored in class member age
	 */
	int getAge(){ return age; }
	void setAge(int age_in) { age = age_in; }
};

int main(){
	Person mike;
	// mike.setAge(3000); // without this line, mike.getAge() will return an uninitialized value
	cout << "Mike is " <<  mike.getAge() << " years old. " << endl;
}


// When NOT A CONSTRUCTOR is defined, the compiler will synthesize a constructor for you that does NOTHING. 
// As a result, variable age is not initialized and the printed integer makes no sense. 
