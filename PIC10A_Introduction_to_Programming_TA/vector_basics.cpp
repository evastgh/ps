#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*int main()
{
    string name;
    cout << "What is your name? ";
    getline (cin, name);
    cout << "Hello, " << name << "!\n";
    for (int i = 0; i < name.size(); ++i)
        cout << "The " << i << "-th character in your name is " << name[i] << endl;
    int array[3];
    array[0] = 5;
    array[1] = 7;
    array[2] = 9;
    for (int i = 0; i < 3; ++i)
        cout << array[i];
    cout << array[15]; // this sometimes is okay, sometimes it causes segmental fualt and your program crashes
}*/

/*int main() {
    vector<int> areacodes;
    areacodes[0] = 310;
    areacodes[1] = 323;
    areacodes[2] = 424;
    for (int i = 0; i < areacodes.size(); ++i)
        cout << "The " << i << "-th entry is " << areacodes[i] << endl;
    
}*/

/*int main()
{
    // string name;
    // cout << name[0]; // this is a bad idea
    // name[0] = 'S'; // also a bad idea
    vector<int> areacodes(/*length*/3, /*default entry*/5566);
    for (int i = 0; i < areacodes.size(); ++i)
        cout << "The " << i << "-th entry is " << areacodes[i] << endl;
    areacodes[0] = 310;
    areacodes[1] = 323;
    areacodes[2] = 424;
    for (int i = 0; i < areacodes.size(); ++i)
        cout << "The " << i << "-th entry is " << areacodes[i] << endl;
    return 0;
}*/

/*int main()
{
    cout << "Please input an desired length:";
    int length_from_input;
    cin >> length_from_input;
    cout << "Constructing a vector of length " << length_from_input << "...\n";
    // int array[length_from_input];
    int default_value = 0;
    vector<int> vec(length_from_input, defaul_value);
    cout << "Now please input the entries.\n";
    for (int i = 0; i < length_from_input; ++i)
        cin >> vec[i];
    cout << "Please enter the desired length to resize:";
    int resize_length;
    cin >> resize_length;
    vec.resize(resize_length, default_value);
    if (resize_length > length_from_input) {
        cout << "Please input the additional entries.\n";
        for (int i = length_from_input; i < resize_length; ++i)
            cin >> vec[i];
    }
    return 0;
}*/

/*int main() {
    vector<int> vec(/*length*/1, /*default entry*/0);
    // cout << "vec[0] = " << vec[0] << endl; // this causes segfault
    cout << "vec[1] = " << vec[1] << endl; // this causes segfault
    cout << "vec.at(0) = " << vec.at(0) << endl;
    cout << "vec.at(1) = " << vec.at(1) << endl;
}*/
