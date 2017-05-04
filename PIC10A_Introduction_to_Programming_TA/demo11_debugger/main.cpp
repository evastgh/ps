//
//  main.cpp
//  test
//
//  Created by KoraJr on 5/2/17.
//  Copyright © 2017 Ucla-Mathematics. All rights reserved.
//

#include <iostream>
// #include <string>

using namespace std;
int main(int argc, const char * argv[]) {
//    // 5 ways to print number 0 to 6 on the screen
//    int m1 = 0;
//    while (m1 < 7) {
//        cout << m1;
//        ++m1;
//    }
//    
//    cout << endl;
//    int m2 = -1;
//    while (m2 < 6)
//        cout << ++m2;   // ++m2 will return the incremented value
//    //          ^^^^ this is evaluated before cout is executed
//    
//    cout << endl;
//    int m3 = 0;
//    while (m3 < 7)
//        cout << m3++;   // m3++ will return the un-incremented value
//    //          ^^^^ this is evaluated before cout is executed
//    cout << endl << m3 << endl;
//    
    int m4 = 100;
    for (m4 = 0; m4 < 7; ++m4)
        cout << m4;
    cout << endl << m4 << endl;     // should throw compiler error

//    int m5 = 0;
//    do {
//        cout << m5++;
//    } while (m5 < 7);   // is this equivalent to the m3 loop? No!!
//                        // the first DO is always executed regardless of the condition!

    int n = 15;
    string s = "hello";
    size_t m = s.size();
    cout << s[m] << endl;
    cout << string('a',n) << endl;
    
    
    // demo of an possibly infinite while loop...!
    size_t n1 = 1, n2 = 2, n3 = 3, n4 = 4;
    while (n3 < n4)
    {
        ++n1;
        n2 += n1;
        n3 = n1 % n2;
        n4 = n2 * n3;
    }
    
    return 0;

}
