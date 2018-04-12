#include <iostream> 
#include <cassert>
#include <utility>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <class T>
void printList(const list<T>& l)
{
    for (auto it = l.cbegin(); it != l.cend(); ++it)
        cout << *it << ' ';
    cout << endl;
}

template <class T>
void mergeSortedLists(list<T>& l1, const list<T>& l2)
{
    // joining l2 at the end of l1
    // l1.insert(l1.end(), l2.cbegin(), l2.cend());
    
    // merge l2 into l1 with accending order
    // ASSUMPTION: l1 and l2 are both in accending order
    auto it1 = l1.begin();
    auto it2 = l2.cbegin();
    for (; it2 != l2.cend(); ++it2) {
        cout << "it1=" << *it1 << "\tit2=" << *it2 << endl;
        while (*it1 < *it2 && it1 != l1.end()) {
            ++it1;
            cout << "stepping. it1=" << *it1 << endl;
        }
        cout << "inserting. ";
        cout << "it1=" << *it1 << "\tit2=" << *it2 << endl;
        l1.insert(it1, *it2);
        printList(l1);
    }
}

void readList(list<int>& list)
{
    cout << "Please input number of integers: ";
    size_t size;
    cin >> size;

    cout << "Please input the integers, separated by space. " << endl;
    for (size_t i = 0; i < size; ++i) {
        int entry;
        cin >> entry;
        list.push_back(entry);
    }
    cout << "To verify, the input is ";
    for (auto it = list.cbegin(); it != list.cend(); ++it)
        cout << *it << ' ';
    cout << endl;
}

int main () {
    list<int> l1, l2;
    readList(l1);
    readList(l2);

    mergeSortedLists(l1, l2);
    cout << "The merged result is ";
    for (auto it = l1.cbegin(); it != l1.cend(); ++it)
        cout << *it << ' ';
    cout << endl;
}
