#ifndef MYVECTOR_H //order matters: isndef first then define
#define MYVECTOR_H

// #include "feaction.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <initializer_list>
using namespace std;

/*
assumptions:
datatype: value_type
referece(const): value_type&
sizetype: size_type
iterator/pointer: value_type*
   */


template<typename T>
class MyVector {
public:

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using iterator = value_type*;


    MyVector();
    MyVector(size_type n, const_reference val);
    // MyVector(size_type n);
    MyVector(std::initializer_list<value_type> l);

    //addition: rule of three: copy constructor, copy assignment, destructor
    ~MyVector();
    MyVector(const MyVector<T>& other);
    MyVector<T>& operator=(const MyVector<T>& rhs); //assignment
    MyVector(MyVector<T>&& other);
    MyVector<T>& operator=(MyVector<T>&& rhs);

    size_type size() const;
    bool empty() const;
    void reserve(size_type new_cap);

    //add l-value version for insert, push_back and +=
    
    void insert(size_type index, const_reference val); //!
    void insert(size_type index, value_type&& val);
    
    void push_back(value_type&& value);
    void push_back(const_reference value); //!
    
    MyVector& operator+=(const_reference val);
    MyVector& operator+=(value_type&& val); //!
    
    const_reference at(size_type n) const;
    reference at(size_type n);

    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    

private:
    size_type _logicalSize;
    size_type _allocateSize;
    iterator _elems;

    friend ostream& operator<<(ostream& os, const MyVector<T>& v);
    friend MyVector<T> operator+(const MyVector<T>& lhs, const MyVector<T>& rhs);
};

template<typename T>
MyVector<T>::MyVector():_logicalSize(0), _allocateSize(10), _elems(new value_type[_allocateSize]) {
    // cout << "defalut constructor" << endl;
}

template<typename T>
MyVector<T>::MyVector(size_type n, const_reference val): _logicalSize(n), _allocateSize(2*n) {
    // cout << "fill constructor" << endl;
    _elems = new value_type[_allocateSize];
    std::fill(_elems, _elems+_logicalSize, val);
} //syntax: new type[size]{filled in value}; add one more {}

// DoubleVector::DoubleVector(size_t n) :_logicalSize(n), _allocateSize(2*n), _elems(new double[_allocateSize]{0}) {}
template<typename T>
MyVector<T>::~MyVector() {
    // cout << "destructor" << endl;
    delete [] _elems;
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<value_type> l): _logicalSize(l.size()), _allocateSize(2*l.size()), _elems(new value_type[_allocateSize]) {
    // cout << "initializer_list constructor" << endl;
    std::copy(l.begin(), l.end(), _elems);
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& other):_logicalSize(other._logicalSize), _allocateSize(other._allocateSize), _elems(new value_type[_allocateSize]) {
    // cout << "copy constructor" << endl;
    std::copy(other._elems, other._elems+other.size(), _elems);
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& rhs) {
    cout << "coppy assignment" << endl;
    if (this != &rhs){
        _logicalSize = rhs._logicalSize;
        _allocateSize = rhs._allocateSize;
        delete [] _elems;
        _elems = new value_type[_allocateSize];
        std::copy(rhs._elems, rhs._elems + rhs._allocateSize, _elems);
    }
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& other): _logicalSize(other.size()), _allocateSize(other._allocateSize), _elems(other._elems) {
    // cout << "move constructor" << endl;
    other._elems = nullptr;
    other._allocateSize = 0;
    other._logicalSize = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& rhs) {
    cout << "move assignment" << endl;
    if (this != &rhs) {
        delete [] _elems;
        _logicalSize = std::move(rhs._logicalSize);
        _allocateSize = std::move(rhs._allocateSize);
        _elems = rhs._elems;
        rhs._elems = nullptr;
    }
    return *this;
}

//size_type is dependent name, in order to use dependent name, we need tp gp to the typename(declare using dependent name) MyVector<T>::size_type
template<typename T>
 typename MyVector<T>::size_type MyVector<T>:: size() const {
    return _logicalSize;
}

template<typename T>
bool MyVector<T>::empty() const {
    return _logicalSize == 0;
}

template<typename T>
void MyVector<T>::reserve(size_type new_cap) {
    if (new_cap > _allocateSize) {
        iterator temp = new value_type[new_cap];
        std::move(_elems, _elems+_allocateSize, temp);
        delete [] _elems; //??
        _elems = temp;
        _allocateSize = new_cap;
    }
}

template<typename T>
void MyVector<T>::insert(size_type index, const_reference val) {
    if (_allocateSize == _logicalSize) {
        reserve(_allocateSize * 2);
    }
    std::move_backward(_elems+index, _elems+_logicalSize, _elems+_logicalSize+1);
    _elems[index] = val;
    _logicalSize += 1;
}

template<typename T>
void MyVector<T>::insert(size_type index, value_type&& val) {
    if (_allocateSize == _logicalSize) {
        reserve(2*_allocateSize);
    }
    std::move_backward(_elems+index, _elems+_logicalSize, _elems+_logicalSize+1); //?
    _elems[index] = std::move(val);
    _logicalSize += 1;
}

template<typename T>
void MyVector<T>::push_back(value_type&& value) {
    insert(_logicalSize, std::move(value));
}

template<typename T>
void MyVector<T>::push_back(const_reference val) {
    insert(_logicalSize, val);
}

template<typename T>
typename MyVector<T>::reference MyVector<T>::at(size_type n) {
    if (n >= _logicalSize) {
        throw "invalid index";
    } else {
        return _elems[n];
    }
}

template<typename T>
typename MyVector<T>::const_reference MyVector<T>::at(size_type n) const {
    if (n >= _logicalSize) {
        throw "invalid index";
    } else  {
        return _elems[n];
    }
}

template<typename T>
typename MyVector<T>::reference MyVector<T>::operator[](size_type n) {

    if (n >= _logicalSize) {
        throw "invalid index";
    } else {
        return _elems[n];
    }
}

template<typename T>
typename MyVector<T>::const_reference MyVector<T>::operator[](size_type n) const {
    
    if (n >= _logicalSize) {
        throw "invalid index";
    } else {
        return _elems[n];
    }
}

template<typename T>
ostream& operator<<(ostream& os, const MyVector<T>& v) {
    os << "{" << v._elems[0];
    for (auto i = 1; i < v._logicalSize; i++) {
        os << ", " << v._elems[i];
    }
    os << "}";
    return os;
}

template<typename T>
MyVector<T> operator+(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    MyVector<T> v = lhs;
    // std::move(lhs._elems, lhs._elems + lhs.size(), v._elems);
    std::move(rhs._elems, rhs._elems + rhs.size(), v._elems+lhs.size());
    return v;
}

template<typename T>
MyVector<T> operator+(const MyVector<T> &lhs, typename MyVector<T>:: value_type rhs) {
    MyVector<T> v = lhs;
    v.push_back(std::move(rhs));
    return v;
}


template<typename T>
MyVector<T>& MyVector<T>::operator+=(value_type&& val) {
    push_back(std::move(val));
    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator+=(const_reference val) {
    push_back(val);
    return *this;
}

#endif // DEBUG





