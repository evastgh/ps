#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    // cout << "argc = " << argc << endl;
    // for (int i = 0; i < argc; ++i)
    //     cout << "argv[" << i << "] = \"" << argv[i] << "\" \n";

    assert(argc >= 2);
    string msg(argv[1]);
    if (msg == "hello") {
        cout << "Oh hello!" << endl;
        return 0;
    }
    else {
        cout << "Rude. " << endl;
        return -1;
    }
}
