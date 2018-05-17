#include <iostream>
#include <memory>
#include <vector>

using namespace std;
struct TaDah {
    TaDah () { cout << "Ta-Dah constructed. " << endl; }
    virtual ~TaDah () { cout << "Ta-Dah destructed. " << endl; }
    virtual void print() { cout << "Ta-Dah" << endl; }
};

struct TaDahPeriod : public TaDah {
    TaDahPeriod () { cout << "Ta-Dah-Period constructed. " << endl; }
    ~TaDahPeriod () { cout << "Ta-Dah-Period destructed. " << endl; }
    void print() { cout << "Ta-Dah-Period" << endl; }
};

int main(int argc, char** argv) {
    cout << "main function starts. " << endl;
    // TaDah* p = new TaDah();
    // TaDah* q = p;
    // unique_ptr<TaDah> q; // Error: why?
    // q = p;
    
    vector<unique_ptr<TaDah>> vec;
    {
        unique_ptr<TaDah> p = make_unique<TaDah>(); // Note: std::make_unique wasn't introduced until c++14
        vec.emplace_back(std::move(p)); // move?
    }
    
    // unique_ptr<TaDah> period = make_unique<TaDahPeriod>();
    // vector<unique_ptr<TaDah>> vec;
    // vec.emplace_back(std::move(period)); // move?
    // for (auto& p : vec)
    //     p->print();

    cout << "main function ends. " << endl;
    return 0;
}
