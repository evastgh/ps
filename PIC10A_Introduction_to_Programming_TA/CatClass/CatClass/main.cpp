#include<iostream>
#include "Cat.hpp"
using namespace std;
int main() {
    Cat fluffy; // create a Cat called fluffy
    cout << "Fluffy is a " << fluffy.breed << endl;
    cout << "Fluffy says: "<< fluffy.talk() << endl; // output cat's meow
    return 0; // terminate program
}
