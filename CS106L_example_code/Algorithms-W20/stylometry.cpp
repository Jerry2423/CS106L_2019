#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
using namespace std;

//using std::cout; using std::end;

string fileToString(ifstream& file) {
    string ret = "";
    string line;
    while (std::getline(file, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        ret += line + " ";
    }
    return ret;
}

// double getSimilarity(const string& text1, const string& text2) {
//     
// }
//
// std::vector<int> createFreqVec(const string& test) {
//     
// }

int dotProduct(const vector<int>& v1, const vector<int>& v2) {
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0); // knowing v2.begin() is enough since v1, v2 are the same length and by knowing the begin and end of v1, and begin of v2, we know end of v2 = v2.begin() + (v1.end() - v1.begin())
}
//regex

int main() {
    vector<int> v1 {1, 2};
    vector<int> v2 {3, 4};
    cout << dotProduct(v1, v2) << endl;
    return 0;
}
