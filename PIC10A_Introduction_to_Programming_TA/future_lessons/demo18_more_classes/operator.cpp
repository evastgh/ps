#include <iostream>
class Person {
	public:
		Person(double height) 
			: height(height)
		{
			setAgeToZero();
		}

		bool operator<(Person& another){
			std::cout << "Left person is of height " << height << std::endl;
			bool isShorter = (height < another.height);
			// expecting some compiler error here? height is private and this class shouldn't be able to access that variable of another class????

			another.height = 0.0;

			return isShorter; // no height is passed in this scope, height here means the class member height
		}

		double getHeight(){
			return height;
		}
	private:
		double height;
		uint age;

		void setAgeToZero(){
			age = 0;
		}

};

using namespace std;
int main(){
	Person stef(1.7);
	Person mike(1.8);
	// cout << stef.height << endl;
	cout << (stef<mike) << endl;

	cout << "Now Mike has height " << mike.getHeight();
}
