#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

int stringToInt1(const string& s) {
    istringstream iss(s);
    int num;
    iss >> num;
    if (iss.fail()) {
        throw std::domain_error("invalid string at the beginning");
    }
    char trash;
    iss >> trash;
    if (!iss.fail()) { //equal to iss.eof()
        throw std::domain_error("redundant string at the tail");
    }
    return num;
}

int stringToInt2(const string& s) {
    istringstream iss(s);
    int num;
    char trash;
    if (!(iss >> num) || (iss >> trash)) { //simplify the code; iss >> num returns a stream that can be converted into a boolean value
        throw std::domain_error("invalid input");
    }
    return num;
}

int main() {
    string s;
    getline(cin, s);
    cout << stringToInt1(s) << endl;
    cout << stringToInt2(s) << endl;
    return 0;
}
