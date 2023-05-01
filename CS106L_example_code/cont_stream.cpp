#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

string getLine() {
    string line;
    getline(cin, line);
    return line;
}

int main() {
    ostringstream oss("Words Counter\nTo Continue, enter y;quit enter q");
    
//mode function: ask for continuous input; only enter 'enter' to terminate the process
    while (true) {
        cout << oss.str() << endl;
        cout << ">";
        string response = getLine();
        if (response == "y") {
            break;
        } else if (response == "q") {
            return 0;
        } else  {
            cout << "Please give valid string" << endl;
        }
    } 

    std::map<string, int> dic;
    cout << "Enter Words: " << endl;    
    while (true) {
        cout << "> ";
        string response = getLine();
        if (response.empty()) {
            break;
        }
        istringstream iss(response);
        string word;
        while (iss >> word) { //use >> operator to extract words. While loop to extreact words continuously
            ++dic[word];
        }
    }
    cout << "Enter Words to Search For: " << endl;
    while (true) {
        cout << "> ";
        string findElem = getLine();
        if (findElem.empty()) {
            break;
        }
        if (dic.count(findElem)) { // containsKey?
            cout << dic[findElem] << " entries found" << endl;
        } else  {
            cout << "none" << endl;
        }
    }
    return 0;
}
