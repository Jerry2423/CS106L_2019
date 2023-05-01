#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <set>
using namespace std;

int main() {
    std::vector<int> v = {1, 2, 3};
    v.push_back(10);
    std::sort(v.begin(), v.end());
    cout << v.front() << " " << v.back() << endl;
    // v.at(10); use at function will check the boundary

    std::deque<int> dec = {1,2,3};
    dec.push_front(10);
    cout << dec.front() << endl;

    std::stack<int> s;
    s.push(5); //container adaptor: push = push_back
    s.push(4);
    s.push(3);
    while (!s.empty()) {
        cout << s.top() << endl; //top = back()
        s.pop(); //pop = pop_back()
    }

    std::queue<int> q;
    q.push(5); //push = push_back
    q.push(4);
    q.push(3);
    
    while (!q.empty()) {
        cout << q.front() << endl; //front = front
        q.pop(); //pop = pop_front
    }
    
    std::map<string, int>  map {{"jr", 10}, {"zj", 20}};
    string line;
    getline(cin, line);
    
    //use count to check whether a key exists.
    if (map.count(line)) {
        cout << "key: " << line << " value: " << map[line] << endl;
    } else  {
        cout << "DNE" << endl;
    }

    for (auto iter = map.begin(); iter != map.end(); ++iter) {
        cout << "key: " << iter->first << "value: " << iter->second << endl;
    }

    std::set<int> set {1, 2, 3};
    auto iter = set.begin();
    //if we don't use auto
    std::set<int>::iterator iter2 = set.end();
    set.insert(5);
    std::pair<int, int> p {1, 2};
    auto p2 = std::make_pair("make_pair", "auto compile");

    auto find = std::find(set.begin(), set.end(), 5); //another way to find a element, find function returns a iterator, if not found, return the end iterrator; slightly faster than .count method
    //find += 1; input(read only iterator)
    std::set<int>::iterator find2 = std::find(set.begin(), set.end(), 100);
    if (find == set.end()) {
        cout << "not found" << endl;
    } else  {
        cout << "yep" << endl;
    }
    //找没找到：出现了没有，count记录出现次数
    if (set.count(100)) {
        cout << "find 100" << endl;
    } else  {
        cout << "no" << endl;
    }

    
    auto someIter = v.begin();
    someIter = someIter + v.size()/2;
    
    std::list<int> l {3, 5, 6, 3, 2};
    //auto lIter = l.begin()+5; error
    

    return 0;
}

