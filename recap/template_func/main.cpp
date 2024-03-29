#include <algorithm>
#include <iostream>
#include <tuple>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <iterator>
using std::cin; using std::cout; using std::endl;
using std::string; using std::istringstream; using std::ostringstream;
using std::ostream_iterator; using std::istream_iterator; using std::ostream;
using std::vector;

// Ask user for input of type T and return the input value
template<typename T>
T getType(const string& prompt = "", const string& reprompt = "invalid input, please enter again") {
    while (true) {
        cout << prompt;
        string s;
        if (!std::getline(cin, s)) {
            throw "error";
        }
        T num;
        char trash;
        istringstream stream(s);
        if (stream >> num && !(stream >> trash)) {
            return num;
        }
        cout << reprompt << endl;
    }
}

/* print container to stream os in the range[first,last), separated by delimiter.

DataType must support << operator; The function does not support std::map. 
*/
template<typename InputIt, typename DataType>
void printContainer(ostream& os, InputIt first, InputIt last, const string& delimiter = ",") {
    cout << "{";
    if (first != last) {
        --last;
        // print second last element
        std::copy(first, last, ostream_iterator<DataType>(os, delimiter.c_str())); // the delitimer type of os_it is c_string
        // print the last element
        cout << *last;
    }
    cout << "}" << endl;
}

/* count the occurrences of val in the container range[first,last).

DataType must support == operator.
*/
template<typename InputIt, typename DataType>
size_t myCount(InputIt first, InputIt last, DataType val) {
    size_t count = 0;
    for (auto it = first; it != last; ++it) {
        if (*it == val) {
            ++count;
        }
    } 
    return count;
}

template<typename InputIt, typename UniPred>
size_t myCountIf(InputIt first, InputIt last, UniPred predicate) {
    size_t count = 0;
    for (auto it = first; it != last; ++it) {
        if (predicate(*it)) {
            ++count;
        }
    } 
    return count;
}



template<typename T>
auto printSize(const T& a) -> decltype(a.size()) {
    cout << "print the size with member function: ";
    cout << a.size() << endl;
    return a.size();
}

template<typename T>
auto printSize(const T& a) -> decltype(-a) {
    cout << "print the size with member function: ";
    cout << -a << endl;
    return -a;
}

template<typename T>
auto printSize(const T& a) -> decltype(a->size()) {
    cout << "print the size with member function: ";
    cout << a->size() << endl;
    return a->size();
}

// DataType, container vec, index
template<typename InputIt1, typename InputIt2>
std::pair<InputIt1, InputIt2> myMismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    while (first1 != last1 && *first1 == *first2) {
        ++first1;
        ++first2;
    }
    return {first1, first2};
}

// in-place algorithm: double pointers, start from where? + find correct postion (similar program: split stirng)
// std::find can also help us find correct postion
template<typename ForwardIt, typename T>
ForwardIt myRemove(ForwardIt first, ForwardIt last, const T& val) {
    auto curr = std::find(first, last, val);
    if (curr != last) {
        auto next = std::next(curr);
        while (next != last) {
            if (!(*next == val)) {
                *curr = std::move(*next);
                ++curr;
                ++next;
            } else {
                ++next;
            }
        }
    }
    return curr;
}

template<typename ForwardIt, typename UniPred>
ForwardIt myRemoveIf(ForwardIt first, ForwardIt last, UniPred pred) {
    auto curr = std::find_if(first, last, pred);
    if (curr != last) {
        auto next = std::next(curr);
        while (next != last) {
            if (!pred(*next)) {
                *curr = std::move(*next);
                ++curr;
                ++next;
            } else {
                ++next;
            }
        }
    }
    return curr;
}

vector<string> splitString(const string& s, const string& delimiter = " ") {
    auto start = s.find_first_not_of(delimiter, 0);
    auto end = s.find(delimiter, start);
    vector<string> result;
    while (start != string::npos) {
        result.push_back(s.substr(start, end - start));
        start = s.find_first_not_of(delimiter, end);
        end = s.find(delimiter, start);
    }
    return result;
}

int main() {
    double foo = getType<double>("give me a double: ");
    cout << foo << endl;
    std::vector<int> v {1, 2, 3};
    auto it = v.begin();
    printContainer<std::vector<int>::iterator, int>(cout, v.begin(), v.begin()+1);
    std::set<int> s {3, 2, 5, 2, 0};
    printContainer<std::set<int>::iterator, int>(cout, s.begin(), s.end());
    cout << myCount(v.begin(), v.end(), 2) << endl;

    std::vector<int> vec {1, 3, 5, 7};
    printSize(vec); // const auto& a = vec; T = const vec<int>&
    printSize(vec[1]); // const auto& a = 3; T = const int&
    printSize(&vec);  // const auto& a = &vec; T = vec<int>* const

    std::vector<int> re_vec {1, 2, 3, 4, 3, 3, 5, 7, 8, 10};
    cout << myCountIf(re_vec.begin(), re_vec.end(), [](auto i) {return i % 2;}) << endl;
    printContainer<std::vector<int>::iterator, int>(cout, re_vec.begin(), myRemove(re_vec.begin(), re_vec.end(), 3));

    auto result = splitString("hello world! Have Fun!");
    printContainer<vector<string>::iterator, string>(cout, result.begin(), result.end());

}
