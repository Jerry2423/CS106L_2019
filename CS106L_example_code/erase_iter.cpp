#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

void eras_all(std::vector<int>& v, int val) {
    //this code is buggy, when container is changed, the iterator i is invalidated
    // for (auto i = v.begin(); i != v.end(); ++i) {
    //     v.erase(i);
    // }

    for (auto i = v.begin(); i != v.end();) {
        if (*i == val) {
            //update iterator
            i = v.erase(i); //by cpp reference: An iterator pointing to the new location of the element that followed the last element erased by the function call. 
        } else {
            ++i;
        }
    }
}



int main() {
    std::vector<int> l {3, 1, 4, 1, 5, 2, 6};
    auto iter = l.begin();
    std::advance(iter, 2);
    cout << *iter << endl;
    l.erase(iter);
    cout << *iter << endl;
    std::vector<int> v { 1, 5, 10, 15, 20 };
    std::vector<int> v_copy = v;
    //similarly to python, to avoid invalidated iterator, make a copy of the vector when changing the size of a vector in the loop
    for (auto i =v_copy.begin(); i != v_copy.end(); ++i) {
        if (*i == 5)
            v.push_back(-1);
    }



    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    /*
    if (std::find(l.begin(), l.end(), *iter) != l.end()) {
        cout << "find" << endl;
    } else {
        cout << "fail" << endl;
    }
    */
    return 0;
}
