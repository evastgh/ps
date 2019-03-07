#include <iostream>
#include <vector>
using namespace std;
void print(const vector<int>& vec) {
    for (auto i : vec)
        cout << i << ' ';
}
vector<int> reverse(vector<int> vec) {
    // if vec = {1, 2, 3}, then return {3, 2, 1}
    // if vec = {1, 2, 3, 4}, then return {4, 3, 2, 1}
    vector<int> return_value(vec.size()); // initialize with expected length
    // two special cases:
    // return_value[0] = vec[vec.size()-1];
    // return_value[1] = vec[vec.size()-2];
    // return_value[return_value.size() - 2] = vec[1];
    // return_value[return_value.size() - 1] = vec[0];
    
    for (unsigned int i = 0; i < return_value.size(); ++i) {
        return_value[i] = vec[vec.size() - 1 - i];
    }
    return return_value;
}

void reverse_inplace(vector<int>& vec) {
    // slow, as it creates copies of vec:
    // vector<int> reversed = reverse(vec);
    // vec = reversed;
    
    // if vec = {1, 2, 3, 4}, 
    // swap vec[0] and vec[end], get {4, 2, 3, 1}
    // swap vec[1] and vec[end-1], get {4, 3, 2, 1}
    
    // recall: swapping the value of int a, b can be done by
    // int temp = a;
    // a = b;
    // b = temp;
    
    for (unsigned int i = 0; i < vec.size() / 2; ++i) {
        int temp = vec[i];
        vec[i] = vec[vec.size() - 1 - i];
        vec[vec.size() -1 - i] = temp;
    }
    
    // vec.size() / 2
    // There're two different cases:
    // Case 1: vec.size() is an even number: vec.size() / 2
    // Case 2: vec.sizer() is an odd number: (vec.size() - 1) / 2 == vec.size() / 2
    // Note that the following index range works as well:
    /*for (unsigned int i = vec.size() - 1; i >= vec.size() / 2; --i) {
        int temp = vec[i];
        vec[i] = vec[vec.size() - 1 - i];
        vec[vec.size() -1 - i] = temp;
    }*/
}


int main()
{
    vector<int> vec = {1, 2, 3, 4};
    //vector<int> reversed = reverse(vec);
    //print(reversed);
    reverse_inplace(vec);
    print(vec);
    return 0;
}

vector<int> operator+(vector<int> a, vector<int> b) {
    if (a.size() != b.size()) {
        cout << "ERR: operator+ called on vectors of different size: ";
        cout << "first.size() = " << a.size() << ", second.size() = " << b.size() << endl;
        return vector<int>();
    }
    unsigned int size = a.size(); // same as b.size() since we've checked
    vector<int> return_value(size);
    for (unsigned int i = 0; i < size; ++i) 
        return_value[i] = a[i] + b[i];
    return return_value;
}
int main()
{
    vector<int> a = {1, 2, 3}, b = {5566, 5567, 5568};
    print(a+b);
    return 0;
}
