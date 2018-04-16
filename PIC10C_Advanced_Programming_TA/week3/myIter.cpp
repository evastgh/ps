#include <iostream> 
#include <cassert>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class DisjointRangesWrapper {
    private:
        vector<pair<int, int>> ranges;

    public:
        DisjointRangesWrapper(vector<pair<int, int>>&& ranges) : ranges(ranges) {}
        size_t size() const { return ranges.size(); }
        bool isEmpty() const { return ranges.empty(); }

        struct Iterator {
            private: 
                const vector<pair<int, int>>& ranges;
                int pos;
                int range_id;
            public:
                Iterator(const vector<pair<int, int>>& ranges, int pos, int range_id) : ranges(ranges) , pos(pos), range_id(range_id) {}
                Iterator& operator++() {
                    if (pos == ranges[range_id].second - 1) { // last number valid in this range, need to go to the next range!
                        ++range_id;
                        if (range_id == (int)ranges.size()) // reached the end of ranges... return the end value of the range
                            ++pos;
                        else
                            pos = ranges[range_id].first;
                    }
                    else {
                        ++pos;
                    }
                    return *this;
                }
                int operator*() { return pos; }
                bool operator==(const Iterator& other) { return pos==other.pos/* && range_id==other.range_id*/; }
                bool operator!=(const Iterator& other) { return pos!=other.pos/* || range_id!=other.range_id*/; }
        };

        // when ranges is empty, the set is asssumed to be {-1}
        Iterator begin() const {
            if (isEmpty())
                return Iterator(ranges, -1, -1);
            else 
                return Iterator(ranges, ranges[0].first, 0);
        }
        
        Iterator end() const {
            if (isEmpty())
                return Iterator(ranges, -1, -1); 
            else
                return Iterator(ranges, ranges.back().second, (int)ranges.size());
        }
};

template <class TContainer>
vector<pair<int, int> > convertSorted(const TContainer& set)
{
    vector<pair<int, int> > return_value;
    auto iter = set.cbegin();
    pair<int, int> current_range(*iter, *iter + 1);
    cout << "[" << *iter << ", ";

    for (++iter; iter != set.cend(); ++iter) {
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

int main () {
    cout << "Please input number of integers: ";
    size_t size;
    cin >> size;

    vector<int> some_set;
    cout << "Please input the integers, separated by space. " << endl;
    for (size_t i = 0; i < size; ++i) {
        int entry;
        cin >> entry;
        some_set.push_back(entry);
    }
    sort(some_set.begin(), some_set.end());

    cout << "To verify, the input is ";
    for (auto it = some_set.cbegin(); it != some_set.cend(); ++it)
        cout << *it << ' ';
    cout << endl;

    vector<pair<int, int> > ranges = convertSorted(some_set);

    DisjointRangesWrapper dr(std::move(ranges));
    for (auto it = dr.begin(); it != dr.end(); ++it)
        cout << *it << ' ';
    // cout << "The converted ranges is: ";
    // for (auto it = ranges.cbegin(); it != ranges.cend(); ++it)
    //     cout << "[" << it->first << ", " << it->second << ") " << endl;

    return 0;
}
