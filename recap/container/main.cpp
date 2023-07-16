#include <algorithm>
#include <iostream>
#include <iterator>
#include <stack>
#include <utility>
#include <vector>
#include <deque>
#include <iterator>
#include <sstream>
#include <map>
using std::stack; using std::vector; using std::deque;
using std::ostream;

void eraseAllEvenKey(std::map<int, int>& dic) {
    auto it = dic.begin();
    while (it != dic.end()) {
        if(it->first % 2 == 0) {
            it = dic.erase(it);
        } else {
            std::advance(it, 1);
        }
    }
}

ostream& operator <<(ostream& os, const std::pair<int, int>& pair) {
    os << "{" << pair.first << "," << pair.second << "}";
    return os;
}

template<typename key, typename value>
void printMap(const std::map<key, value>& dic) {
    std::for_each(dic.begin(), dic.end(), [](const std::pair<key, value>& info) {std::cout << "{" << info.first << "," << info.second << "} ";});
    std::cout << std::endl;
}

int main() {
    // container adaptor
    stack<int, vector<int>> s;

    vector<int> v {1, 2, 3, 4, 5, 6, 7, 8};
    auto it = v.begin();
    while (it != v.end()) {
        if (*it % 2 != 0) {
            it = v.insert(it, *it);
            std::advance(it, 2);
        } else {
            it = v.erase(it);
        }
    }
    
    // remove and erase idiom: don't forget to erase the range between remove and v.end()!
    // can use auto in lambda function parameter since it can deduct it's the type of each element in the collection
    v.erase(std::remove_if(v.begin(), v.end(), [](auto i) {return i % 3 == 1;}), v.end());
    v.erase(std::remove(v.begin(), v.end(), 3), v.end());

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::map<int, int> dic {{1, 3}, {2, 4}, {6, 9}, {7, 5}, {3, 2}};
    eraseAllEvenKey(dic);
    // remove_if does not work for associative container. see note for more info
    // dic.erase(std::remove_if(dic.begin(), dic.end() , [](std::pair<int, int>& info) {return info.first%2 == 0;}), dic.end()); 
    // invalid output map, see more in stackoverflow
    // std::copy(dic.begin(), dic.end(), std::ostream_iterator<std::pair<int, int>>(std::cout, " "));

    printMap<int, int>(dic); 
}
