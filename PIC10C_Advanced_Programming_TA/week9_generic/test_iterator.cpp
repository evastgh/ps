#include <iostream>
#include <unordered_set>

using namespace std;
void setIterTest() {
    // see discussion here: https://stackoverflow.com/questions/38468844/erasing-elements-from-unordered-map-in-a-loop
    unordered_set<int> some_set = {0, 1, 5, 4, 2};
    some_set.insert(6);
    some_set.insert(7);
    some_set.insert(8);
    
    cout << "Starting state, the set is: ";
    for (int j : some_set)
        cout << j << ' ';
    cout << endl;
    
   /* erase element in colon-loop */
   for (int i : some_set) {
       if (i==2) {
           some_set.erase(i);
           cout << "Erased 2. \n";
       }
       cout << "In for loop, i = " << i << ", the set is: ";
       for (int j : some_set)
           cout << j << ' ';
       cout << endl;
   }
    
//    /* insert element in colon-loop */
//    for (int i : some_set) {
//        if (i==2) {
//            some_set.insert(3);
//            cout << "Inserted 3. \n";
//        }
//        cout << "In for loop, i = " << i << ", the set is: ";
//        for (int j : some_set)
//            cout << j << ' ';
//        cout << endl;
//    }
    
    // /* dereferencing iterator after erasure */
    // for (auto it = some_set.begin(); it != some_set.end(); ++it) {
    //     int i = *it;
    //     if (i==2) {
    //         some_set.erase(2);
    //         cout << "Erased 2. \n";
    //     }
    //     cout << "In for loop, i = " << i << ", dereference the iterator: " << *it << endl;
    // }
}

int main() {
    setIterTest();
    return 0;
}
