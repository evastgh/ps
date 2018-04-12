# Week 2 - STL Containers

## Iterators
* [Why iterators?](https://stackoverflow.com/questions/131241/why-use-iterators-instead-of-array-indices) e.g. functions templated on container types, STL algorithms, avoid **SIGSEG** 😉 
* [Categories of iterators](http://www.cplusplus.com/reference/iterator/)
* Gotta have to talk about this http://en.cppreference.com/w/cpp/container/vector/back

## Demo: a templated function that turns sorted integers to disjoint ranges (pair of integers)
```cpp
template <class TContainer>
vector<pair<int, int> > convertSorted(const TContainer& set)
{
    vector<pair<int, int>> return_value;
    auto iter = set.cbegin();
    pair<int, int> current_range(*iter, *iter + 1);
    cout << "[" << *iter << ", ";

    for (++iter; iter != set.end(); ++iter) {
        assert(*iter >= current_range.second); //, "convertSorted only works with sorted data. ");
        if (*iter == current_range.second) {
            current_range.second = *iter + 1;
        }
        else {
            return_value.push_back(current_range);
            cout << current_range.second << ") \n[" << *iter << ", ";
            current_range.first = *iter;
            current_range.second = *iter + 1;
        }
    }
    cout << current_range.second << ")\n";
    return_value.push_back(current_range);

    return return_value;
}
```

## Demo: Stack?
[Leet Code 20 - Valid Parentheses](https://leetcode.com/problems/valid-parentheses/description/)
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

## Demo: List?
[Leet Code 21 - Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/description/)
```cpp
template <class T>
void mergeSortedLists(list<T>& l1, const list<T>& l2)
{
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
```

## Side Notes
* Like my vim - MarkDown settings? [Here](https://github.com/suan/vim-instant-markdown) you go!
