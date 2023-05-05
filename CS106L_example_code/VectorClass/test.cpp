#include "feaction.h"
#include "doublevector.h"
#include "intvector.h"

int main() {
    // Feaction a(3, 4);
    // Feaction b(2, 5);
    // cout << a << endl;
    // a += b;
    // cout << a << endl;
    // cout << a + 10 << endl;
    // cout << 10 + a << endl;
    
    DoubleVector v {1.12, 2.9};
    v.push_back(6.6);
    v.insert(2, 2.4);
    v.push_back(9.9);
    DoubleVector v2(3, 8.8);
    v2 += 4.4;
    // cout << v2 << endl;
    // cout << v + v2 << endl;
    DoubleVector v3 = v + 100;
    // cout << v3 << endl;
    // cout << v << endl;
    v3 = v2;
    v3.push_back(90);
    cout << v3 << endl;
    cout << v2 << endl;

    return 0;
}
