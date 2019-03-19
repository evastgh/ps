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

### Problem 4
1. 
```
srand(time(nullptr));
double sum = 0.0;
for (int i = 0; i < 1000; ++i) {
    double r = static_cast<double>(rand());
    r /= static_cast<double>(RAND_MAX);
    sum += r;
}
double average = sum / static_cast<double>(1000);
cout << average;
```
2.
```
double polynom(double x, const vector<double>& a) {
    double power = 1, return_value = 0.0;
    for (unsigned int i = 0; i < a.size(); ++i) {
        return_value += a[i] * power;
        power *= x;
    }
    return return_value;
}
```

Here's another version that might be easier to understand:
```
double polynom(double x, const vector<double>& a) {
    unsigned int n = a.size();
    double return_value = 0;
    for (unsigned int i = 0; i <= n; ++i) {
        double power = 1.0;
        for (unsigned int k = 1; k <= i; ++k)
            power *= x;
        return_value += power * a[i];
    }
    return return_value;
}
```

### Problem 5
1. 
```
vector<int> concat(const vector<int>& a, const vector<int>& b) {
    vector<int> return_value = a;
    for (vector<int>::iterator it  = b.begin(); it != b.end(); ++it)
        return_value.push_back(*it);
    return return_value;
}
```

Here's anther version that doesn't involed iterator:
```
vector<int> concat(const vector<int>& a, const vector<int>& b) {
    vector<int> return_value = a;
    for (unsigned int i = 0; i < b.size(); ++i)
        return_value.push_back(b[i]);
    return return_value;
}
```

2. You might find the [description of string::find](http://www.cplusplus.com/reference/string/string/find/) helpful.
```
vector<string> parse(const string& s) {
    vector<string> return_value;
    size_t start_pos = 0;
    while (true) {
        size_t pos = s.find(' ', start_pos);
        if (pos == -1) {
        return_value.push_back(s.substr(start_pos, s.size() - start_pos));
            break;
        }
        return_value.push_back(s.substr(start_pos, pos - start_pos));
        start_pos = pos + 1;
    }
    return return_value;
}
```

### Problem 6
1. 
```
class Item {
    string description;
    int price;
  public:
    Item(const string& d, int p) : description(d), price(p) {}
    Item(const string& d) : description(d), price(0) {}
    void print() const { cout << "Description: " << description << ".\n Price: " << price << endl; }
    void set_price(int p) { price = p; }
    int get_price() const { return price; }
    string get_description() const { return description; }
};
```
2. 
```
class date {
    int month, date, year;
  public:
    date(int m, int d, int y) : month(m), date(d), year(y) {}
    date(const string& s) {
        month = stoi(s.substr(0, 2));
        date = stoi(s.substr(3, 2));
        year = stoi(s.substr(6, 4));
    }
    void print() const { cout << month << ' ' << date << ' ' << year; }
    int operator-(const date& another) {
        return (year - another.year)*365 + (month - another.month)*30 + (date - another.date);
    }
    bool operator< (const date& another) {
        if (year < another.year)
            return true;
        else if (year == another.year) {
            if (month < another.month)
                return true;
            else if (month == anther.month) {
                if (date < another.date)
                    return true;
            }
        }
        return false;
    }
};
```

### Problem 7
1. You might find the [description of list::erase](http://www.cplusplus.com/reference/list/list/erase/) helpful.
```
void remove_even(list<int>& lst) {
    list<int>::iterator it = lst.begin();
    while (it != lst.end()) {
        if ((*it)%2) { // odd
            ++it;
        }
        else { // even
            it = lst.erase(it);
        }
    }
}
```
