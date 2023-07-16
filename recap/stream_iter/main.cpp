#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
using std::cout; using std::endl; using std::cin;
using std::istringstream; using std::ostringstream;

void printVec(const std::vector<int>& v) {
    cout << "{";
    if (!v.empty()) {
        std::copy(v.begin(), v.end()-1, std::ostream_iterator<int>(cout, ","));
        cout << v.back();
    }
    cout << "}" << endl;
}

int main() {
    istringstream s("1 2 3 4 5 6 7 8");
    std::partial_sum(std::istream_iterator<int>(s), std::istream_iterator<int>(), std::ostream_iterator<int>(cout, " "));
    istringstream s1("1 2 3 4 5 6 7 8");
    auto it = std::find_if(std::istream_iterator<int>(s1), std::istream_iterator<int>(), [](int a){return a%2 == 0;});
    if (it != std::istream_iterator<int>()) {
        cout << "the first even number is " << *it << endl;
    } else {
        cout << "no even number" << endl;
    }

    printVec({2, 3, 1, 5, 6});
    printVec({6});
}
