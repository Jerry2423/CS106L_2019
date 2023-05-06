#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>
using namespace std;

void foo(const int& a) {
    return;
}

int main() {
    const int a = 10;
    foo(a);

    vector<string> v {"hello", "world"};
    vector<string> v2 {"!"};
    std::copy(v2.begin(), v2.end(), back_inserter(v));
    cout << v[0] << endl;
    //equivalent line down:
    // cout.operator<<(v.operator[](0)).operator(endl);
    operator<<(cout, v.operator[](0)); // equivalent to cout << v[0];
    
}
