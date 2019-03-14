#include <iostream>
#include <vector>
#include <list>
using namespace std;

void print(const vector<int>& c) {
    for (vector<int>::const_iterator it = c.cbegin(); it != c.cend(); ++it) {
        cout << *it << ' ';
        // *it += 1; // cannot modify it because it's a const_iterator
    }
}
void print(list<int> c) {
    for (list<int>::iterator it = c.begin(); it != c.end(); ++it) {
        cout << *it << ' ';
        *it += 1;
    }
}
int main()
{
    vector<int> vec = {1, 2, 3, 4};
    list<int> lst = {5, 6, 7, 8};
    cout << "vec = ";
    print(vec);
    cout << endl;
    cout << "lst = ";
    print(lst);
    cout << endl;
    // concatenate lst to vec
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        lst.push_back(*it);
    }
    cout << "vec = ";
    print(vec);
    cout << endl;
    cout << "lst = ";
    print(lst);
    
    return 0;
}
//----
#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;
void print(const set<int>& s) {
    for (set<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
        cout << *it << ' ';
    }
}
void print(const unordered_set<int>& s) {
    for (unordered_set<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
        cout << *it << ' ';
    }
}

int main()
{
    unordered_set<int> s = {7, 4, 1, 0};
    print(s);
    
    s.insert(6);
    cout << "\nAfter insert, ";
    print(s);
    return 0;
}
//----
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void print(const vector<int>& c) {
    for (vector<int>::const_iterator it = c.cbegin(); it != c.cend(); ++it) {
        cout << *it << ' ';
        // *it += 1; // cannot modify it because it's a const_iterator
    }
}
void print(list<int> c) {
    for (list<int>::iterator it = c.begin(); it != c.end(); ++it) {
        cout << *it << ' ';
        *it += 1;
    }
}

int main()
{
    list<int> lst = {1, 2, 3, 4, 5, 6, 7};
    print(lst);
    
    list<int>::iterator it = lst.begin();
    while (it != lst.end()) {
        if (*it == 5)
            break;
        ++it;
    }
    
    if (it == lst.end()) {
        cout << "Error, list doesn't contain 5.";
        return -1;
    }
    list<int>::iterator result = lst.erase(it);
    cout << endl << *result << endl;
    print(lst);
    
    return 0;
}
//----
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    string name("Stephanie");
    cout << name.find('t');
    
    vector<char> vec = {'S', 't', 'e', 'f'};
    vector<char>::iterator it = vec.begin();
    while (it != vec.end()) {
        if (*it == 't')
            break;
        ++it;
    }
    
    if (it == vec.end()) {
        cout << "Error, vec doesn't contain 't'.";
        return -1;
    }
    
    cout << *(it+1);
    
    return 0;
}
