#include <iostream>
#include <string>
using namespace std;

int main() {
    int&& rref = 7*8;
    int a = 10;
    int* ptr = &a;
    int*& ptref = ptr;
    int& b = a;
    const int* cptr;
    int* const cp2 = &a;
    cp2++
    // ptr = &b;
    cout << *ptr << endl;
}


















