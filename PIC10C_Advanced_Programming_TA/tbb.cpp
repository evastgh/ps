#include "tbb/tbb.h"
#include "tbb/blocked_range.h"
#include <vector>
#include <iostream>

using namespace std;
// using Accessor = tbb::enumerable_thread_specific<vector<int>>;

int main() {
    // Accessor vec;
    tbb::parallel_for(tbb::blocked_range<size_t>(0, 100), 
        [](tbb::blocked_range<size_t>& subrange) {
            // Accessor::reference sub_vec = vec.local();
            cout << "This thread size is " << subrange.size() << endl;
            // for (auto it = subrange.begin(); it != subrange.end(); ++it)
            //     cout << it << endl;
                // sub_vec.emplace_back(*it)
            });


    // vector<int> final_vec;
    // for (Accessor::const_iterator it = vec.begin(); it != vec.end(); ++it) 
    //     final_vec.insert(final_vec.end(), it->begin(), it->end());

    // copy(final_vec.begin(), final_vec.end(), ostream_iterator<int>(cout, " "));
    return 0;
}



