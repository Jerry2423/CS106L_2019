#include "Employee.h"

class Snow {
    public:
        virtual void method2() {
            cout << "snow2" << endl;
        }
        virtual void method3() {
            cout << "snow3" << endl;
        }
        virtual void method4() {
            cout << "snow4" << endl;
            method2();
        }
};

class Rain : public Snow {
    public:
        virtual void method1() {
            cout << "rain1" << endl;
        }
        virtual void method2() {
            cout << "rain2" << endl;
        }
};

class Sleet : public Snow {
    public:
        virtual void method2() {
            cout << "sleet2" << endl;
            Snow::method2();
        }
        virtual void method3() {
            cout << "sleet3" << endl;
        }
};

class Fog : public Sleet {
    public:
        virtual void method1() {
            cout << "fog1" << endl;
        }
        virtual void method3() {
            cout << "fog3" << endl;
        }
};


int main() {
    Employee a("a", 10);
    // Snow* v1 = new Sleet();
    // v1->method2();
    // Snow* var2 = new Rain();
    // // var2->method1()
    // Snow* var4 = new Rain();
    // dynamic_cast<Sleet*>(var4) ->method2();

    // Snow* var4 = new Fog();
    // static_cast<Sleet*>(var4) -> method1()

    // Snow* var6 = new Sleet();
    // static_cast<Rain*>(var6)->method1();

    // Snow* var8 = new Sleet();
    // var8->method4();
    // Snow* b = new Sleet();
    // Rain* c = dynamic_cast<Rain*>(b);
    // c->method4();
    Snow b = Snow();
    Snow& refb = b;
    // dynamic_cast<Rain&>(refb) .method4();
    int foo = 100;
    int& fref = foo;
    int foo2 = 90;
    fref = foo2; //foo2 is not bound to fref, this is just an assignment
    fref ++;
    cout << fref << " " << foo <<" " << foo2 << endl;
    return 0;
}
