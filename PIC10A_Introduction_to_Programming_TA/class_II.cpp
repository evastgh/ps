#include <iostream>
using namespace std;
void cry() { cout << "Standalone function cry() called. \n"; }

struct Dummy {
    Dummy() {}
    void print() {
        cout << "Dummy printing its status. \n";
        cry(); // the same as this->cry();
    }
    void cry() { cout << "Dummy::cry() called. \n"; }
};

int main()
{
    Dummy foo;
    foo.print();
    
    int i = 0;
    while (ture) {
        int i = 5;
        cout << i;
    }
    return 0;
}
