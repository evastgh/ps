#include <iostream>
#include <memory>

using namespace std;
struct TaDah {
    TaDah () { cout << "Ta-Dah constructed. " << endl; }
    ~TaDah () { cout << "Ta-Dah destructed. " << endl; }
};

int main(int argc, char** argv) {
    cout << "main function starts. " << endl;
    unique_ptr<TaDah> p = make_unique<TaDah>(); // Note: std::make_unique wasn't introduced until c++14

    cout << "main function ends. " << endl;
    return 0;
}
