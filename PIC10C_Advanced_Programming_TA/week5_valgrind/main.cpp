#include <vector>
#include <iostream>

using namespace std;

struct Base {
    // ~Base() { cout << "Destructor Base called. " << endl; }
};

struct Derived : public Base {
    int data;
    Derived(int) : data() {}
    // ~Derived() { cout << "Destructor Derived called. " << endl; }
};

// /* Example 1: uninitialized values */ 
// double compute_average(const vector<int>& scores ){
//     char accumulated_average;

//     for ( size_t i = 0 ; i < scores.size() ; ++i )
//         accumulated_average += scores[i];

//     return static_cast<double>(accumulated_average)/scores.size();
// }

// void comparison_fun() {
//     char array[100000000];

//     for (size_t i = 0; i < 100000000; ++i) {
//         array[i] = 10;
//         // blah~
//     }
// }

// /* Example 2: uninitialized pointers */
// double compute_average2( vector<int> scores ){
//     char *accumulated_average;

//     for ( size_t i = 0 ; i < scores.size() ; ++i )
//         *accumulated_average += scores[i];

//     return static_cast<double>(*accumulated_average)/scores.size();
// }

// /* Example 3: inproper descruction */
// void some_fun( ){
//     int *p = new int[2017];
//     return;
// }

// /* Example 4: inproper descruction */
// void some_fun2( ){
//     int *p = new int[2017];
//     delete p;
//     return;
// }

// /* Example 5: inproper descruction. ALERT: valgrind didn't capture this!! */
// void my_fun3() {
//     Base* ptr = new Derived(1);
//     delete ptr;
// }

/* Example 6: inproper new */
void some_fun4( ){
    int *p; 
    p = new int[2017];
    // if (/* some_condition*/ )
    //     int *pp = p;
    p = new int[7012];   // Ooops

    delete[] p;
    return;
}

int main(int argc, char** argv) {
    // vector<int> scores(10, 99);
    // cout << "Average is " << compute_average(scores) << endl;
    // cout << "Average is " << compute_average2(scores) << endl;
    // some_fun();
    // some_fun2();
    // my_fun3();
	some_fun4();
}
