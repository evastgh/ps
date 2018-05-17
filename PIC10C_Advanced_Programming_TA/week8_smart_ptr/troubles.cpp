#include <iostream>
#include <memory>
#include <vector>

using namespace std;
struct IntData {
    int data;
    IntData(int data) : data(data) { cout << "IntData constructed. " << endl; }
    ~IntData() { cout << "IntData destructed. " << endl; }
};

struct IntRef {
    int& ref;
    IntRef(int& data) : ref(data) { cout << "IntRef constructed. " << endl; }
    ~IntRef() { cout << "IntRef destructed. " << endl; }
};

int main(int argc, char** argv) {
    cout << "main function starts. " << endl;

    IntData* p1 = new IntData(5);
    IntRef* p2 = new IntRef(p1->data);
    delete p1;
    cout << "print ref: " << p2->ref << endl;
    delete p2;

    return 0;
}
