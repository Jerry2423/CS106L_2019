#include <ios>
#include <iostream>
#include <queue>
#include <algorithm>
#include <iterator>
#include <set>
#include <unordered_set>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include "my_util.h"

using std::cout;            using std::endl;
using std::cerr;            using std::string;
using std::unordered_map;   using std::unordered_set;

class Fraction {
    public:
        explicit operator double() const {return static_cast<double>(num) / denom;}
        operator bool() const {return num < denom;}
        Fraction(int num, int denom) : num(num), denom(denom) {}
        Fraction(Fraction&& other) : num(std::move(other.num)), denom(std::move(other.denom)) {}
        Fraction& operator++() {num += denom; return *this;}
        Fraction operator++(int) {Fraction copy(num, denom); num += denom; return copy;}
    private:
        int num;
        int denom;
        friend ostream& operator<<(ostream& os, const Fraction &fra);
};

ostream& operator<<(ostream& os, const Fraction &fra) {
    os << fra.num << "/" << fra.denom;
    return os;
}

/*
 * You should delete the code in this function and
 * fill it in with your code from part A of the assignment.
 *
 * If you used any helper functions, just put them above this function.
 */

// TODO: ASSIGNMENT 2 TASK 4:
// Please implement a function that can determine if a wiki link is valid or not.
// As a reminder, it needs to take in a string and return whether or not 
// # or : is contained in the string.
// Estimated length: ~5-10 lines

///////////////////////////////////////////////////////////////////////////////////////////////////
// BEGIN STUDENT CODE HERE
bool valid_wikilink(const string& link) {
    // replace these lines!
    (void) link;
    return std::all_of(link.begin(), link.end(), [](auto ch) {return ch != ':' && ch != '#';});
}
// END STUDENT CODE HERE
///////////////////////////////////////////////////////////////////////////////////////////////////

unordered_set<string> findWikiLinks(const string& inp) {
    /* Delimiter for start of a link  */
    static const string delim = "href=\"/wiki/";

    unordered_set<string> ret;

    auto url_start = inp.begin();
    auto end = inp.end();

    while(true) {

        // TODO: ASSIGNMENT 2 TASK 1:
        // Set url_start to the next location of "delim" (starting your search at url_start), using std::search.
        // After doing so, break out of the while loop if there are no occurrences of delim left
        // (use your work from the line above).
        // Estimated length: 2-3 lines

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // BEGIN STUDENT CODE HERE
        auto find_delim = std::search(url_start, end, delim.begin(), delim.end());
        if (find_delim == end) {
            break;
        }
        url_start = std::next(find_delim, delim.size());
        // Please delete this line when you start working!
        // END STUDENT CODE HERE
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        // TODO: ASSIGNMENT 2 TASK 2:
        // Set url_end to the end of the wikilink. Start searching after the delimeter you found above.
        // Make sure to use std::find! (std::find looks for a single element in a container, e.g. character in 
        // a string—std::search looks for a series of elements in a container, like a substring in a string. 
        // remember that a string is represented as an array of characters, and is also a container!)
        // Estimated length: 1 lines

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // BEGIN STUDENT CODE HERE (delete/edit this line)
        auto url_end = std::find(url_start, end, '"');
        // END STUDENT CODE HERE
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        // TODO: ASSIGNMENT 2 TASK 3:
        // Last exercise of this function! Create a string from the two iterators (url_start and url_end) above
        // using a string constructor. Make sure you start the string AFTER the delimiter you found in task 5!
        // Estimated length: 1 lines
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // BEGIN STUDENT CODE HERE (delete/edit this line)
        
        string link = string(url_start, url_end);

        // END STUDENT CODE HERE
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        /*
         * Only add link to the set if it is valid i.e. doesn't
         * contain a ':' or a '#'.
         */
        if(valid_wikilink(link)){
            ret.insert(link);
        }

        url_start = url_end;

    }
    return ret;

}

bool tryDecltype() {
    return false;
}

int main() {
    string s = "<p>\n"
"  In <a href=\"/wiki/Topology\">topology</a>, the <b>long line</b> (or <b>Alexandroff line</b>) is a\n"
"  <a href=\"/wiki/Topological_space\">topological space</a> somewhat similar to the <a href=\"/wiki/Real_line\">real line</a>, but in a certain way \"longer\". It behaves locally just like the real line, but has different large-scale properties (e.g., it is neither\n"
"  <a href=\"/wiki/Lindel%C3%B6f_space\">Lindelöf</a> nor\n"
"  <a href=\"/wiki/Separable_space\">separable</a>). Therefore, it serves as one of the basic counterexamples of topology\n"
"  <a href=\"http://www.ams.org/mathscinet-getitem?mr=507446\">[1]</a>. Intuitively, the usual real-number line consists of a countable number of line segments [0,1) laid end-to-end, whereas the long line is constructed from an uncountable number of such segments. You can consult\n"
"  <a href=\"/wiki/Special:BookSources/978-1-55608-010-4\">this</a> book for more information.\n"
"  </p>\n"
"               ";
    auto result = findWikiLinks(s);
    my_util::printContainer<std::unordered_set<string>::iterator, string>(cout, result.begin(), result.end());
    
    cout << my_util::containVal(result.begin(), result.end(), "Topological_space") << endl;

    string foo = "abcdefgabc";
    string target = "abc";
    vector<int>  vec {1, 2, 3, 4, 5, 6};
    vector<int> goal {3, 4, 5};
    cout << std::boolalpha << (vec.end() != std::search(vec.begin(), vec.end(), goal.begin(), goal.end())) << endl;
    // decltype(tryDecltype()) fun;
    // int limit = 10;
    // auto cmp = [&limit](int a) {return a < limit;};
    // decltype(cmp) fun(cmp);
    auto cmp = [](const auto& v1, const auto& v2) {return v1.size() > v2.size();};
    vector<int> v {1, 2}, v1{3, 4, 5}, v2 {6, 7, 8, 9};
    std::priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
    q.push(v);
    q.push(v1);
    q.push(v2);
    my_util::printContainer<decltype(v.begin()), decltype(v.front())>(cout, v.begin(), v.end());
    while (!q.empty()) {

        
        std::copy(q.top().begin(), q.top().end(), std::ostream_iterator<int>(cout, " "));
        cout << endl;
        q.pop();
    }

    int kdj = 10;
    const int d = 10;
    const int &f = d;
    int k;
    decltype(k = 100) i = kdj;
    decltype(f) h = 10;
    decltype(d) e = 5;

    extern const double PI;
    cout << PI << endl;
    
    int *const cptr = &kdj;
    *cptr = 10;

    vector<string> s_v {"1234", "234", "122343223", "fun"};
    for (auto i = s_v.cbegin(); i != s_v.cend(); ++i) {
        if (i->size() > 3) {
            cout << *i << endl;
        }
    }
    vector<string>::const_iterator ii = s_v.begin();
    ++ii;

    Fraction fra(3, 4);
    if (fra) {
        cout << "true fraction " << fra << "'s value is " << static_cast<double>(fra) << endl;
    }

    
    int a1 = 1, b1 = 2, c1 = 3;
    // a1 = (b1 = a1) = b1;
    a1 = b1 = c1;
    cout << a1 << endl;
    cout << b1 << endl;
    return 0;
}
