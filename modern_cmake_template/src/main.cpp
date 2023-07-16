#include <iostream>
#include <vector>
#include "my_util.h"

int main() {
    std::vector<int> v {1, 2, 3};
    my_util::printContainer<vector<int>::iterator, int>(cout, v.begin(), v.end());

    return 0;
}
