#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int stringToInt(const string& s) {
   istringstream iss(s);
   stringstream fun(s);

   int a;
   fun >> a; //use istringstream to convert a string to an integer 
   return a;
}

int main() {
    string s;
    cin >> s;
    cout << "the string is " << s << endl;
    cout << "integer is ";
    cout << stringToInt(s) << endl;
    return 0;
}
