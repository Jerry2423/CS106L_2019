#ifndef DOUBLEVECTOR_H
#define DOUBLEVECTOR_H

// #include "feaction.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <initializer_list>
using namespace std;

class DoubleVector {
public:
    DoubleVector();
    DoubleVector(size_t n, double val = 0);
    // DoubleVector(size_t n);
    DoubleVector(std::initializer_list<double> l);

    //addition: rule of three: copy constructor, copy assignment, destructor
    ~DoubleVector();
    DoubleVector(const DoubleVector& other);
    DoubleVector& operator=(const DoubleVector& rhs); //assignment

    size_t size() const;
    bool empty() const;
    void reserve(size_t new_cap);

    void insert(size_t index, double val);
    void push_back(double value);
    double& at(size_t n);
    const double& at(size_t n) const;

    double& operator[](size_t n);
    const double& operator[](size_t n) const;
    
    DoubleVector& operator+=(double val);

private:
    size_t _logicalSize;
    size_t _allocateSize;
    double* _elems;

    friend ostream& operator<<(ostream& os, const DoubleVector& v);
    friend DoubleVector operator+(const DoubleVector& lhs, const DoubleVector& rhs);
};

DoubleVector::DoubleVector():_logicalSize(0), _allocateSize(10), _elems(new double[_allocateSize]) {}
DoubleVector::DoubleVector(size_t n, double val): _logicalSize(n), _allocateSize(2*n) {
    _elems = new double[_allocateSize];
    std::fill(_elems, _elems+_logicalSize, val);
} //syntax: new type[size]{filled in value}; add one more {}
// DoubleVector::DoubleVector(size_t n) :_logicalSize(n), _allocateSize(2*n), _elems(new double[_allocateSize]{0}) {}
DoubleVector::~DoubleVector() {
    delete [] _elems;
}
DoubleVector::DoubleVector(std::initializer_list<double> l): _logicalSize(l.size()), _allocateSize(2*l.size()), _elems(new double[_allocateSize]) {
    std::copy(l.begin(), l.end(), _elems);
}


DoubleVector::DoubleVector(const DoubleVector& other):_logicalSize(other._logicalSize), _allocateSize(other._allocateSize), _elems(new double[_allocateSize]) {
    std::copy(other._elems, other._elems+other.size(), _elems);
}

DoubleVector& DoubleVector::operator=(const DoubleVector& rhs) {
    if (this != &rhs){
        _logicalSize = rhs._logicalSize;
        _allocateSize = rhs._allocateSize;
        delete [] _elems;
        _elems = new double[_allocateSize];
        std::copy(rhs._elems, rhs._elems + rhs._allocateSize, _elems);
    }
    return *this;
}

size_t DoubleVector::size() const {
    return _logicalSize;
}

bool DoubleVector::empty() const {
    return _logicalSize == 0;
}

void DoubleVector::reserve(size_t new_cap) {
    if (new_cap > _allocateSize) {
        double* temp = new double[new_cap];
        std::move(_elems, _elems+_allocateSize, temp);
        delete [] _elems; //??
        _elems = temp;
        _allocateSize = new_cap;
    }
}

void DoubleVector::insert(size_t index, double val) {
    if (_allocateSize == _logicalSize) {
        reserve(2*_allocateSize);
    }
    std::move_backward(_elems+index, _elems+_logicalSize, _elems+_logicalSize+1); //?
    _elems[index] = val;
    _logicalSize += 1;
}


void DoubleVector::push_back(double value) {
    insert(_logicalSize, value);
}

double& DoubleVector::at(size_t n) {
    if (n >= _logicalSize) {
        throw "invalid index";
    } else {
        return _elems[n];
    }
}

const double& DoubleVector::at(size_t n) const {
    if (n >= _logicalSize) {
        throw "invalid index";
    } else  {
        return _elems[n];
    }
}


double& DoubleVector::operator[](size_t n) {

    if (n >= _logicalSize) {
        throw "invalid index";
    } else {
        return _elems[n];
    }
}
const double& DoubleVector::operator[](size_t n) const {
    
    if (n >= _logicalSize) {
        throw "invalid index";
    } else {
        return _elems[n];
    }
}


ostream& operator<<(ostream& os, const DoubleVector& v) {
    os << "{" << v._elems[0];
    for (auto i = 1; i < v._logicalSize; i++) {
        os << ", " << v._elems[i];
    }
    os << "}";
    return os;
}

DoubleVector operator+(const DoubleVector& lhs, const DoubleVector& rhs) {
    DoubleVector v(lhs.size() + rhs.size());
    std::move(lhs._elems, lhs._elems + lhs.size(), v._elems);
    std::move(rhs._elems, rhs._elems + rhs.size(), v._elems+lhs.size());
    return v;
}

DoubleVector operator+(const DoubleVector &lhs, double rhs) {
    DoubleVector v = lhs;
    v.push_back(rhs);
    return v;
}


DoubleVector& DoubleVector::operator+=(double val) {
    push_back(val);
    return *this;
}

#endif // DEBUG
