#include "feaction.h"

//Feaction::Feaction(const int num, const int denom)
//{
//    this->num = num;
//    this->denom = num;
//}

//int Feaction::getDenom() const {
//    return this->denom;
//}
//int Feaction::getNum() const {
//    return this->num;
//}

//Feaction& Feaction::operator+=(const Feaction &rhs) {
//    int newDenom = rhs.getDenom() * this->denom;
//    int newNum = rhs.getNum() * this->denom + this->num * rhs.getDenom();
//    this->num = newNum / gcd(newNum, newDenom);
//    this->denom = newDenom / gcd(newNum, newDenom);
//    return *this;
//}


//Feaction& Feaction::operator+=(const int rhs) {
//    this->num += rhs * this->denom;
//    this->num /= gcd(num, denom);
//    this->denom /= gcd(num, denom);
//    return *this;
//}

//int Feaction::gcd(int a, int b) const {
//    if (a < b) {
//        int temp = a;
//        a = b;
//        b = temp;
//    }
//    if (b == 0) {
//        return a;
//    } else  {
//        return gcd(b, a%b);
//    }
//}

//// Feaction::operator double() const {
////     return double(this->num) / double(this->denom);
//// }

//ostream& operator<<(ostream& os, const Feaction& fraction) {
//    os << fraction.num << "/" << fraction.denom;
//    return os;
//}

//Feaction operator+(const Feaction& lhs, const Feaction& rhs) {
//    int newNum = lhs.num * rhs.denom + rhs.num * lhs.denom;
//    int newDenom = lhs.denom * rhs.denom;
//    return Feaction(newNum / lhs.gcd(newDenom, newNum), newDenom / lhs.gcd(newDenom, newNum));
//}

//Feaction operator+(const Feaction& lhs, const int rhs) {
//    int newNum = lhs.num + lhs.denom * rhs;
//    newNum /= lhs.gcd(newNum, lhs.denom);
//    return Feaction(newNum, lhs.denom / lhs.gcd(newNum, lhs.denom));
//}
//Feaction operator+(const int lhs, const Feaction& rhs) {
//    int newNum = rhs.num + rhs.denom * lhs;
//    newNum /= rhs.gcd(newNum, rhs.denom);
//    return Feaction(newNum, rhs.denom / rhs.gcd(newNum, rhs.denom));
//}


//#endif // IntVector_H

