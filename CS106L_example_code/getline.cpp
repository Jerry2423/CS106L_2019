#include <iostream>
#include <string>
using namespace std;

int main() {
    string s, s1;
    cin >> s;
    cin.ignore();// Don't mix cin with getline, without this line forcing the ptr move past the whitspace, getline will read an empty line

    getline(cin, s1);
    cout << s1; //getline consumes/pasts the delimiter but the return value does not include the ending whitespace
    cout << s << endl;
    return 0;
}
