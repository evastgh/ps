# Week 2 - STL Containers

## Iterators

* why iterators?
```cpp
vector<int> s(10);
for (size_t i = 0; i < s.size(); ++i)
    cout << s[i] << endl;

// Now write a loop 
```

[Categories of iterators](http://www.cplusplus.com/reference/iterator/)


Gotta have to talk about this http://en.cppreference.com/w/cpp/container/vector/back

## 

## Demo: Stack
```cpp
bool checkParenthesis(const string& input)
{
    stack<char> record;
    for (auto iter = input.cbegin(); iter != input.cend(); ++iter) {
        if (*iter == '(') {
            record.push(*iter);
        }
        else if (*iter == ')') {
            if (record.top() == '(')
                record.pop();
            else
                return false;
        }
    }
}
```
