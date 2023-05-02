#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <sstream>
#include <vector>
using namespace std;

template<typename T>
std::pair<T, T> my_max(T a, T b) {
    if (a < b) {
        return {b, a};
    } else  {
        return {a, b};
    }
}

template<typename T>
T getType(const string& prompt = "") {
    while (true) {
        cout << prompt << endl;
        string line;
        if (!getline(cin, line)) {
            throw std::domain_error("error");
        }
        istringstream iss(line);
        T result;
        char trash;
        if (iss >> result && !(iss >> trash))
            return result;
    }
}

/*
   assumption 1: vector
   assumption 2: int type
   assumption 3: the whole vector
   good template: the less implicit assumptions, the better the template function is
   */
// template<typename InputIter, typename DataType>
// int countOccurences(InputIter start, InputIter end, DataType val) {
//     int times = 0;
//     for (auto i = start; i != end; ++i) {
//         if (*i == val) {
//             times += 1;
//         }
//     }
//     return times;
// }

template<typename InputIter,  typename UniPred>
int countOccurences (InputIter start, InputIter end,  UniPred pred) {
    int count = 0;
    for (auto i = start; i != end; ++i) {
        if (pred(*i))
            count ++;
    }
    return count;
}

int main() {
    auto [a, b] = my_max<double>(10, 8.9);
    cout << a <<  " " << b << endl;

    double num = getType<double>();
    cout << num << endl;

    std::set<double> set {9.9, 8,9, 7.6};
    auto iter = set.begin(); // set iterator is bidirectional iterator, not random iterator; += is invalid
    ++iter;
    // cout << countOccurences<std::set<double>::iterator, double>(iter,set.end(), 9.9) << endl;
    
    int limit = 5, numCalled = 0;
    auto lessThanLimit = [limit, &numCalled](auto val) {
        numCalled ++;
        return val < limit;
    };

    std::vector<int> v {1, 2, 4, 3, 30, 89, 10};
    cout << "# of elements satisfying the predicate condition:";
    cout << countOccurences(v.begin(), v.end(),  lessThanLimit) << endl;
    cout << "times the lambda function called: ";
    cout << numCalled << endl;

    cout << "using the std::count_if, which is the same:";
    cout << std::count_if(v.begin(), v.end(), lessThanLimit) << endl;

    return 0;
}
