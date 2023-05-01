#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

int getInteger(const string& prompt = "") {
    while(true) {
        cout << prompt << endl;
        string s;
        if (!getline(cin, s)) {
            throw std::domain_error("error");
        }
        istringstream iss(s);
        int num;
        char trash;

        if (iss >> num && !(iss >> trash)) {
            return num;
        } else  {
            cout << "invalid input, try again" << endl;
        }
    }
}

int main() { 
    int a = getInteger("Give an integer");
    return 0;
}
