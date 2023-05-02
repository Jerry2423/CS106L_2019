#include <iostream>
#include <string>
using namespace std;

template<typename InputIter, typename DataType, typename UniPred>
int countOccurences(InputIter start, InputIter end, DataType val, UniPred pred) {
    int times = 0;
    for (auto i = start; i != end; ++i) {
        if ((pred(*i))) {
            times += 1;
        }
    }
    return times;
}
int main() {
    int limit = 5;
    auto isLessThan = [limit](auto val) -> bool {
        return val < limit;
    };
    
    auto isBiggerThan = [&limit](auto val) -> bool {
        return val > limit;
    };
}
