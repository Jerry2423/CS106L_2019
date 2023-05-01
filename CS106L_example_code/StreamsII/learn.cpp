#include<iostream>
#include<string>
#include <sstream> //for ostringstream
using namespace std;

int main() {
    ostringstream oss("iii", ostringstream::ate); // specified the position pointer at the end after writing in to the stream
    // cout << oss.str() << endl;
    // //if not specified, stream position pointer starts at the start, ovveriding the leading original characters.
    // oss << "10199";
    // cout << oss.str() << endl;
    // //ostringstream buffer are seperate
    oss << "123" << "210938"; // concatenate successively, NOT Like the one above written in seperate lines;
    cout << oss.tellp() << endl;
    cout << oss.str() << endl;

    istringstream iss("18.7 fun");
    int num;
    double num2;
    string s;

    // iss >> s; // after reading to the first ending position(e.g white space or some chars that do not satisfy the consersion stop, position pointer won't go back)
    // iss >> num;
    iss >> num2 >> s;
    cout << num2 << " str:" << s << endl;

    return 0;
}
