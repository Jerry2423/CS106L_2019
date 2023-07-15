#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using std::vector;
using std::string;
using std::cout; using std::endl;
using std::cin;
using std::istringstream; using std::ostringstream;

vector<string> split(const string& s, const string& delimiter = " ") {
    vector<string> vec;
    // two pointer slicing a word
    size_t pos_start = s.find_first_not_of(delimiter, 0);
    size_t pos_end = s.find(delimiter, pos_start);
    while (pos_start != string::npos || pos_end != string::npos) {
        vec.push_back(s.substr(pos_start, pos_end - pos_start));
        // move forward position
        pos_start = s.find_first_not_of(delimiter, pos_end);
        pos_end = s.find(delimiter, pos_start);
    }
    return vec;
}

int getInteger(const string& prompt = "", const string& reprompt = "") {
    while (true) {
        cout << prompt;
        string s;
        if (!std::getline(cin, s)) {
            throw "error";
        }
        int num;
        char trash;
        istringstream stream(s);
        if (stream >> num && !(stream >> trash)) {
            return num;
        }
        cout << reprompt << endl;
    }
}



int& badIntRef(int& a) {
    int b = a;
    return b;
}

int& goodIntRef(int& a) {
    return a;
}

int main() {
    string s = " I love Code ! ";
    auto vec = split(s);
    for (const auto& i : vec) {
        cout << i << endl;
    }
    istringstream flow("42 is a magic number");
    int a;
    flow >> a;
    cout << "the stream position is " << flow.tellg() << endl;
    flow.seekg(0); // rewind
    cout << "the stream position is " << flow.tellg() << endl;


    // a = getInteger();
    std::map<int, string> dic {{10, "hi"}};
    for (auto [key, value] : dic) {
        cout << "{" << key << ":" << value << "}" << endl;
    }

    ++goodIntRef(a);
    cout << a << endl;

}
