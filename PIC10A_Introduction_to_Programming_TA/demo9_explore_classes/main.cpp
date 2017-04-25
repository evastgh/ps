#include<iostream>
#include "Cat.h"
using namespace std;
int main() {
		Cat fluffy; // create a Cat called fluffy
		cout << "Fluffy says: "<< fluffy.talk(); // output cat's meow
		cin.get(); // pause
		return 0; // terminate program
}
