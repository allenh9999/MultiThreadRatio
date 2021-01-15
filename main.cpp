#include <thread>
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

void count_to_num(long num) {
    for(long i = 0; i < num; ++i) {
        // simple program as benchmark
        if(i % 3 == 0) {
            vector<float> nums = {1.0f};
            for(int i = 0; i < 10; ++i) {
                auto back = nums.back();
                back *= 10;
                nums.push_back(back);
            }
        } else {
            pair<long,long> vals = {0,1};
            vals.first ^= 0x10f;
            vals.second *= vals.second;
            swap(vals.first,vals.second);
        }
    }
}

int main() {
    cout << "Note: this program can not test over 1000 threads" << endl;
    auto start_single = high_resolution_clock::now();
    count_to_num(100000000);
    auto end_single = high_resolution_clock::now();
    auto single_time = duration_cast<nanoseconds>(end_single - start_single);
    cout << "Single thread time: " << single_time.count() / 1000000 << "ms" << endl;
    thread threads[1000];
    auto start_multi = high_resolution_clock::now();
    for(int i = 0; i < 1000; ++i) {
        threads[i] = thread(count_to_num,100000);
    }
    for(int i = 0; i < 1000; ++i) {
        threads[i].join();
    }
    auto end_multi = high_resolution_clock::now();
    auto multi_time = duration_cast<nanoseconds>(end_multi - start_multi);
    cout << "Multi-thread time: " << multi_time.count() / 1000000 << "ms" << endl;
    cout << "Ratio: " << (float) single_time.count() /  (float) multi_time.count() << endl;
}