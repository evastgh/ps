#include <iostream>
#include <vector>
using namespace std;
ostream& operator<<(ostream& os, const vector<int>& v) {
    for (int i = 0; i < v.size(); ++i)
        os << v[i] << ' ';
    return os;
}
int main() {
    vector<int> vec = { 2, 4, 6 };
    cout << vec << endl;
    // cout << "vec[-1] = " << vec[-1] << endl;
    // cout << "&(vec[-1]) = " << &(vec[-1]) << endl;
    // cout << "&(vec[0]) = " << &(vec[0]) << endl;
    // vec.resize(1);
    // cout << "Called vec.resize(1);" << endl;
    // cout << vec << endl;
    // cout << "vec[0] = " << vec[0] << endl;
    // cout << "vec[1] = " << vec[1] << endl;
    // cout << "vec[2] = " << vec[2] << endl;
    
}

#include <iostream>
using namespace std;
void print_array(int a[3]) {
    for (int i = 0; i < 3; ++i)
        cout << a[i] << ' ';
}
void modify_maybe(int a[3]) { a[0] = 5566;}
// passing &(a[0])
void modify(int* p) { *p = 5566; }
int main() {
    int a[3];
    a[0] = 2;
    a[1] = 4;
    a[2] = 6;
    print_array(a);
    modify_maybe(a);
    print_array(a);
    int n = 11;
    modify(&n);
    cout << n;
}

#include <iostream>
using namespace std;
void print_array(int* a, int size) {
    for (int i = 0; i < size; ++i)
        cout << a[i] << ' ';
}
int main() {
    int a[4] = { 2, 4, 6, 8 }, b[2] = {3, 9};
    print_array(a, 4);
    print_array(b, 2);
}

#include <iostream>
using namespace std;
struct MyMatrix3by3 {
    /* bad implementation
    int col1[3], col2[3], col3[3];
    MyMatrix3by3(int c1[], int c2[], int c3[]) {
        for (int i = 0; i < 3; ++i) {
        col1[i] = c1[i];
        col2[i] = c2[i];
        col3[i] = c3[i];
        }
    }
    void print() {
        cout << col1[0] << ' ' << col2[0] << ' ' << col3[0] << '\n';
        cout << col1[1] << ' ' << col2[1] << ' ' << col3[1] << '\n';
        cout << col1[2] << ' ' << col2[2] << ' ' << col3[2] << '\n';
    }*/
    
    int data[3][3];
    MyMatrix3by3(int c0[], int c1[], int c2[]) {
        for (int i = 0; i < 3; ++i) {
            data[i][0] = c0[i];
            data[i][1] = c1[i];
            data[i][2] = c2[i];
        }
    }
};
int main() {
    int c1[3] = {2, 1, 0}, c2[3] = {1, 2, 1}, c3[3] = {0, 1, 2};
    MyMatrix3by3 A(c1, c2, c3);
    A.print();
}
