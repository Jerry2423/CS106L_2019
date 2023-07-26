### C++ Learning Notes
- template class operator

在写template class的非member function的时候会出现这样的问题：

```c++
template<typename T>
class MyVector {
  ....
    private:
    ....
    friend ostream& operator<<(ostream& os, const MyVector<T>& v);
    friend MyVector<T> operator+(const MyVector<T>& lhs, const MyVector<T>& rhs);
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
```

这样写：现在类里面声明函数，再在类外面声明函数看似没什么问题，但编译的时候就有错误了

`Linker Command Failed With Exit Code 1`

问助教这个问题得到了解决：

错因：

> 当你在类内对operator<<有一个friend声明时，相当于这个函数在这个类的作用域内被声明了一次
>
> 如果仅仅是这样，当你再在类外定义它的时候，编译器是无法知道类外定义的那个函数和类内声明的这个函数之间的联系的
>
> 这和非模板的情形不同，如果MyVector不是模板，这两个函数也不是模板函数，那么编译器就会知道类外的那个定义和这个friend声明是同一个函数
>
> 造成这种区别的原因是，编译器在编译一个模板的时候，它首先只会做普通的词法和语法检查，不会检查更深层的东西，比如语义、类型、上下文的关联等等。只有在这个模板被用到的时候，给出了模板参数，编译器才会去实例化这个模板，这时它才会做更多的检查
>
> 然后，当编译器看到你main函数里调用了operator<<的时候，重点来了：它如何查找这个operator<<？
>
> 这里有一个重要的名字查找规则，叫做Argument-dependeng lookup (ADL)：如果这个函数调用的时候某个参数是类类型的，编译器会首先在这个参数的类型的类作用域内查找这个函数名。比方说这里的operator<<和operator+都有MyVector类型的参数，编译器就会首先在class MyVector这个类作用域内查找operator<<和operator+
>
> 那么它自然就找到了这两个friend声明。但是很遗憾，编译器仍然不会意识到后面类外给出的那两个函数定义正是这两个friend的定义
>
> 所以它只能找到声明，没有找到定义，也就是说它能编译但无法链接，这就是为什么你看到的报错是linker报的错

关键问题：template function在被编译的时候只是进行简单的句法分析，不会做关联，就没有把class的声明和后面的implementation联系起来。编译器在main file编译<< 和+ 的时候，就会去**类的作用域**（仅限于`class{}`所包住的部分）中找<< 和+， 注意，因为类里面`class{}`的声明没有后面的implementation联系起来，所以就相当于调用了一个没有实现的函数，就会报错



解决办法：

> 那么第一种解决方法也就非常自然了：直接将这两个friend函数在声明friend的时候定义

直接在类里面就实现了；

> 第三种解决方法，就是干脆没有friend，也不访问私有成员。这时ADL就会失败，它在MyVector类作用域内没有找到匹配的函数时，自然就会到全局去找，这时也就能找到全局的operator<<和operator+了

干脆就不在类里面声明，编译器在类的作用域里面找不到，就回去.h file外面找，就找到了



- template class的特殊语法

1. member function的implementation：以template function的方式定义

```c++
template<typename T>
bool MyVector<T>::empty() const {
    return _logicalSize == 0;
}

```

注意：在**class specifier(classname::)**部分也要加上`<T>`

2. member type

> Sometimes, we need a name for a type that is **dependent** on our template types
>
> - Recall: iterators `vector<int>::iterator`
>
> - Used to make sure your clients have a standardized way to access important types.
>
> - Lives in your namespace: vector<T>::iterator.
>
> - After class speciﬁer, you can use the alias directly (e.g. inside function arguments, inside function body).
>
> - Before class speciﬁer, use typename.

关于最后两地点，用一个代码实例说明

```c++
template<typename T>
class MyVector {
public:
		
    //type alias: these types dependent on real type T
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using iterator = value_type*;

}
...
template<typename T>
typename MyVector<T>::reference MyVector<T>::operator[](size_type n) {

    if (n >= _logicalSize) {
        throw "invalid index";
    } else {
        return _elems[n];
    }
}

```

前面`typename MyVector<T>::reference`其实是为了说明函数的返回类型， 但为了统一用member type，而此时还没有出现class specifier，就只能用`typename`关键词把member type从`MyVector<T>`里面调用出来；但后面函数的参数`size_type n`就可以直接调用，因为前面有了class specifier `MyVector<T>::operator[]`



- Iterator support

如何让`MyVector`支持iterator，这样它就可以和别的stl container一样被stl库里面的算法调用？

提供`begin()`和`end()`函数！注意const correctness：常数型iterator也要提供！

```c++
class MyVecotr {
...
    iterator begin();
    iterator end();
    const_iterator begin() const; //const correctness!
    const_iterator end() const;

}
template<typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
    return _elems;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
    return _elems + _logicalSize;
}

template<typename T>
typename MyVector<T>::const_iterator MyVector<T>::begin() const {
    return _elems;
}

template<typename T>
typename MyVector<T>::const_iterator MyVector<T>::end() const {
    return _elems + _logicalSize;
}

```

可以看到返回值其实就是一个指针：`random iterator`

- std::move and std::copy: iterator adaptor

在写`+`运算符的时候出现了这样的问题：

```c++
template<typename T>
MyVector<T> operator+(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    MyVector<T> v = lhs;
    // std::move(lhs._elems, lhs._elems + lhs.size(), v._elems);
    std::move(rhs._elems, rhs._elems + rhs.size(), v._elems+lhs.size());
    return v;
}

```

> 先说个题外话，我看你到处在用std::move，注意一点，标准库<algorithm>里的算法永远都不会往容器里插入元素或者删除容器里的元素，除非你传给它的迭代器是某些特殊的iterator adapter，例如inserter
>
> 比方说std::copy(begin1, end1, begin2)，它就是将[begin1, end1)里的元素拷贝到从begin2开始的一段范围里，你必须保证begin2开始的那一段范围的长度大于等于[begin1, end1)的长度
>
> std::copy是不会帮你一个一个push_back的
>
> std::move也是同理
>
> 标准库<algorithm>里没有任何算法会改变容器的长度，除非你传给它的是某些inserter

用`std::copy `和`std::move`的时候一定要小心容器的长度！如果要扩容的话要用iterator adaptor，back_inserter之类的；在实现iterator的基础上，将move行改成

`std::move(rhs.begin(), rhs.end(), back_inserter(v));`

注意back_inserter的用法：

> `back_inserter` is a convenient function template that constructs a [std::back_insert_iterator](https://en.cppreference.com/w/cpp/iterator/back_insert_iterator) for the container `c` with the type deduced from the type of the argument.
>
> Parameters
>
> | c    | -    | container that supports a push_back operation |
> | ---- | ---- | --------------------------------------------- |
> |      |      |                                               |

Container `c`要支持push_back操作





- ~~OOP Inheritance~~
- ~~Polymorphisim and mytery~~
- type conversion
- ~~selected line search and replace vim command~~

- 命名规范

- ~~stl：stream~~



### Class Summary

**Class Design**

- Public and Private Members
- Const correctness: const object; const functions; const ptr/iterator

- Rule of five and zero: constructor and destructor



**Member Function Design**

- Const correctness: **return** **value;** **parameter,function,does** **it** **work** **for** **const** **object?**
- Pass by value / reference
- POLA(**operator**): member/non-member(friend)?



**Special Member Functions: Move and Copy operator**

- Copy 

1. constructor
2. Assignment 

- Move

1. constructor
2. assignment
3. R and l value(reference)
4. steal
5. Force a move`std::move`



**Inheritance and Polymorphism**



**Template Class**



**Iterator Design for Custom Data Structure**: check out the file`/CS106L_2019/CS106L_example_code/VectorClass-move/MyVector.h` and `/cs106b/recap/linklist/linklist/linklist.h`

Build a class called `iterator` inside the vector class, set vector class as `friend` in `iterator` and set iterator as`friend` in vector class. The constructor of `iterator` should be private so that the iterator can only be constructed by the vector class.

Operator overloading for iterator class: for linked list, the `++`operator means go to the next node, different from the addition for a ptr.



- 奇葩的赋值等式：`a1` 和`b1`的值是什么？

```c++
int a1 = 1, b1 = 2, c1 = 3;
a1 = (b1 = a1) = b1;
cout << a1 << endl;
cout << b1 << endl;
```

> 1. 首先赋值运算符是右结合的，a=b=c需要理解为a=(b=c)，所以你这个表达式要理解为a1=((b1=a1)=b1)
>
> 2. 然后，我们知道对于表达式E1=E2来说，一定会先将E1和E2这两个表达式求值完毕再发生对E1的赋值，所以这里对最左边的a1的赋值是没有任何疑问的，就是把右边((b1=a1)=b1)求值完毕再赋给a1
>
>    求值的顺序：先右后左
>
> 3. 问题在于(b1=a1)=b1这个表达式。自C++17起，E1=E2这样的赋值，一定会**先对E2求值再对E1求值（不论E1有没有括号）**，所以C++17起这里不存在疑问，就是(b1=a1)=2，也就是(b1=1)=2，也就是先执行b1=1然后执行b1=2，最终执行a1=b1，所以a1也是2
>
> 4. **C++17以前**，以及在C中，这个规则是没有的。即，究竟是E1先求值还是E2先求值是unspecified，如果在这个过程中发生了对同一个对象的两个修改或者一读一写，那就是undefined behavior。在(b1=a1)=b1中，左侧(b1=a1)是对b1修改，右侧又是在读b1的值，所以是**undefined behavior**
