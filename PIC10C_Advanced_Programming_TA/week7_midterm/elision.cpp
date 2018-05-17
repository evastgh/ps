#include <iostream>

using namespace std;
struct Algo {
    Algo () { std::cout << "Algo defultly constructed." << endl; }
    Algo (const Algo&) { std::cout << "Algo copied." << endl; }
};

struct AlgoExplicit {
    AlgoExplicit () { std::cout << "AlgoExplicit defultly constructed." << endl; }
    explicit AlgoExplicit (const AlgoExplicit&) { std::cout << "AlgoExplicit copied." << endl; }
    void say() { std::cout << "haha" << endl; }
};

int main () {
    // /* this is equivalent to Algo a(); */
    // Algo a = Algo();

    // /* this is still equivalent to Algo a(); */
    // Algo a = Algo(Algo(Algo()));
    
    /* explicit copy constructor won't be implicitly called */
    // AlgoExplicit a = AlgoExplicit(); // error
    AlgoExplicit a(AlgoExplicit());
    a.say();
}
