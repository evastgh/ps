### Problem 1
(1) True, e.g. `vector<int> vec;`
(2) True, you can provide the implementation of the member functions later with syntax `MyClass::memberFunction() {}`
(3) Yes; however, it won't compile with `string s = "two" + "three" + t;`
(4) De Morgan's Law: !(!A || !B) = A && B. The expression is simplified to `x==0 && y==1`
(5) _Not sure what the question means. What's the input?_
(6) `const`. Accessors are read-only; only mutators can change the state of the class.
(7) `void`
(8) Passing by value, the original variable gets copied and the funciton won't be able to affect it. Passing by reference, the function will have access to the original varialbe through the reference and nothing is copied. (The function can't necessarily modify the original varialbe as the reference could be a const one.)
(9) `dq.pop_front();`
(10) Passing by pointer, the function needs to use the dereference operator to access the variable and it can modify this pointer to access the neighboring memory (e.g. when you pass an array by pointer). Passing by reference, the function doesn't need dereference operator and can directly access the variable. Neither causes copying of the variable.
(11) `a` is an array not a pointer as it's a staticly-sized array. It cannot be incremented.
(12) `lst.size()` Note that this may of may not involve traversing all elements depending on the implementation. See https://en.cppreference.com/w/cpp/container/list/size.
(13) True. See https://en.cppreference.com/w/cpp/container/vector/insert.
(14) a, b
(15) b

### Problem 2
1.  
```
int x;
cin >> x;
if (!(x%5)) cout << "x is divisible by 5";
```
2. 
```
int x;
cin >> x;
while (x >= 0)
{
    cout << (x % 10);
    x = x / 10;
}
```
3. An [ASCII table](http://www.asciitable.com/) might be helpful.
```
string s;
getline(cin, s);
for (unsigned int i = s.size() - 1; i >= 0; i--)
{
    if (s[i] >= 'a')
        s[i] = s[i] - 'a' + 'A';
}
```

### Problem 3
1. Be careful it's `modify(y, x)`!
```
5 2
2 5
8 7
7 2
```
2. g(y) = 3*h(y) = 3*(2*y+1) = 6*y+3, f(h(x), g(x)) = g(g(x)) + h(h(x)) = 6*(6*x+3)+3 + 2*(2*x+1)+1 = 40*x + 24
```
9 3 64
```
3. 
```
2 4 8
```






