#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main() {
    auto pair = make_pair("jr", 20);
    auto& [a, b] = pair;
    cout << a << " " << b << endl;
    return 0;
}
