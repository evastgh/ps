// First, install tbb by 
//  > brew install tbb
// Compile this file with flags
//  > g++ tbb.cpp -I tbb/include -ltbb -ldl -std=c++14
#include "tbb/tbb.h"
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int main() {
    using Accessor = tbb::enumerable_thread_specific<vector<size_t>>;
    Accessor vec;
    mutex m;

    // vector<size_t> dummy; // slow!
    auto printing = [&m, vec/*, &dummy*/](tbb::blocked_range<size_t>& subrange) -> void {
            // {
            //     lock_guard<mutex> guard(m);
            //     cout << "This thread size is " << subrange.size() << endl;
            //     // for (auto it = subrange.begin(); it != subrange.end(); ++it)
            //     //     dummy.emplace_back(it);
            // }

            Accessor::reference sub_vec = vec.local();
            for (auto it = subrange.begin(); it != subrange.end(); ++it)
                sub_vec.emplace_back(it);
            };
    tbb::parallel_for(tbb::blocked_range<size_t>(0, 9000000, 25), printing);
    // copy(dummy.begin(), dummy.end(), ostream_iterator<int>(cout, " "));
    
    vector<size_t> final_vec;
    for (Accessor::const_iterator it = vec.begin(); it != vec.end(); ++it) 
        final_vec.insert(final_vec.end(), it->begin(), it->end());

    copy(final_vec.begin(), final_vec.end(), ostream_iterator<int>(cout, " "));
    return 0;
}



