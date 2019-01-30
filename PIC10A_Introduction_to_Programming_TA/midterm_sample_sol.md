## Problem 1
**(a)** cmath

**(b)** size, length, ... see [string](https://en.cppreference.com/w/cpp/header/string)

**(d)** ii (exclamation mark), iv (starts with number), vi (bool is a reserved key-word

**(c)** False, string comparison compares each position lexicographically, and capital letters are smaller than lower case letters.

**(d)** (ii) both arguments are integers. (write a short program and test it!)

**(e)** (ii) the division results in 32.

## Problem 2
The correst program should be
```cpp
#include <iostream>
using namespace std;
int main()
{
    string text = "Hello, World!";
    cout << text;
    return 0;
}
```

## Problem 3
**(a)** 
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    cout << "Please input a positive floating point number x: ";
    double x;
    cin >> x;
    double result;
    if (x < 0.0) {
        result = 0.0; // result should be zero
    }
    else {
        result = ( pow(x, 1.75) - sqrt(cos(x) + 0.25 * x) ) / ( x * x + 1);
    }
    cout << "The result is " << result << endl;
    return 0;
}
```

**(b)**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
    cout << "How are you feeling today?" << endl;
    string response;
    getline(cin, response);
    cout << "Sorry, but Computer does not understand emotions.";
    return 0;
}
```

## Problem 4
**(a)**
`q && !p` evaluates to `true`, then `p || true` evaluates to `true`, hence the final result is `false`.

**(b)**
n = 4, k = 0, s = 25

**(c)**
x = 3, y = 2.0;

## Problem 4
In the first iteration of the while loop, `quantity1` becomes 1, `quantity2` becomes 2, `cost` becomes 16, `cost > 10 && quantity2 < 4` evaluates to `true`, hence `cost` becomes 17.6.

Enters second iteration since `cost` is smaller than `BUDGET`.

In the first iteration of the while loop, `quantity1` becomes 2, `quantity2` becomes 4, `cost` becomes 32, `cost > 10 && quantity2 < 4` evaluates to `false`. 

Exists the while loop since `cost` is greater than `BUDGET`.

The console output should be 
```
The final cost is = 32
```

## Problem 5
The lines needed filling are
```cpp
#include <>
#include <>
char YN = cin.get();
if (YN == 'Y') {
    d1 = rand() % 6 + 1;
    d2 = rand() % 6 + 1;
    cout << d1 << ' ' << d2 << endl;
    if (d1 == d2) {
        d1 = rand() % 6 + 1;
        d2 = rand() % 6 + 1;
        cout << d1 << ' ' << d2 << endl;
    }
}
else {
    more = false;
}
```

## Problem 6
**Notice that the Taylor expansion of the function exp(x) should be sum of x^k / factorial(k) instead of x^k / k.**
```cpp
double x, output = 1.0;
unsigned int n, fac = 1;
cin >> x >> n;
if (n >= 1) {
    for (int k = 1; k < n; ++k) {
        fac *= k;
        output += pow(x, k) / fac;
    }
}
cout << "The output is " << output << endl;
```

If you like it more sophisticated, try declaring `double xpower = x;` and increment it by `xpower *= x` in each iteration of the for loop.
