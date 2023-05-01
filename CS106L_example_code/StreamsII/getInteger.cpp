#include <iostream>
#include <sstream>
#include <stdexcept>
#include<string>
using namespace std;

int getInteger(const string& prompt);

int main() {
    string prompt = "input a number";
    int a = getInteger(prompt);
    cout << a << endl;
}

int getInteger(const string& prompt) {
    while (true) {
        cout << prompt << endl;
        string input;
        if (!getline(cin, input)) {
            throw std::domain_error("fail");
        }
        istringstream iss(input);
        int result;
        char trash;
        if (iss >> result && !(iss >> trash))
            return result;
    }
}

