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
	int get_age(){
		return age;
	}
};

int main(){
	Person mike;
	cout << "Mike is " <<  mike.getAge() << " years old. " << endl;
}


// When NOT A CONSTRUCTOR is defined, the compiler will synthesize a constructor for you that does NOTHING. 
// As a result, variable age is not initialized and the printed integer makes no sense. 
