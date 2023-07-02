## Array Cheatsheet



### Array Decay and Implicit Conversion 

数组名在大多是情况下会隐式转化成一个指向数组首个元素（明晰数组首个元素的类型）的指针（non-lvalue）

**The pointer that points to the 0th element of array**

但在一下情况中不会转化：

> Any lvalue expression of array type, when used in any context **other than**
>
> - as the operand of the address-of operator (`&`)
> - as the operand of `sizeof`
> - as the string literal used for array initialization
>
> undergoes a conversion to the non-lvalue **pointer to its first element**.

以至于某些人会告诉你“数组名就是指针”，**但这是不对的！**

```c++
int a[10] {1, 2, 3, 4};
int (*ptr)[10] = &a // no implicit conversion
sizeof(a) // no impliocit conversion
```



### Pass Array as Parameter

函数parameter声明的类型要和数组decay之后的类型一致

**Trick**: 从首个`[]`往后`->`所指的类型，后面没东西了就绕回定义的开头，比如`int`...



### Pointer to an Array and Array of Pointers

**Pointer to an Array**

Def:

```c++
type (*var_name)[size] = &array_name;
```

`()` 的理解：`[]`的运算优先级大于`*`解引用的优先级，所以要打括号让`*`优先，表示dereference`*var_name`之后的对象是个数组



**Array of Pointers**

Def:

```c++
type* var_name[size]
```

从`[]`开始，这个内存块里面的element的类型是`type*`



**Incompatibility**

上述两个东西不兼容：也不能强制转化

本质原因：pointer arithmetic is performed **relative to the base size**两者decay后的base size不同，混用会导致访问非法内存

One aspect of multidimensional arrays that often confuses novice C programmers is that these two ways to represent multidimensional data are not compatible with each other—they are different types, and cannot be implicitly converted from one to the other. In fact, if you try to explicitly convert from one to the other (via a cast), you will get results ranging from nonsensical answers to your program crashing. This common problem underscores the importance of knowing the *exact* meaning of the types that you declare, and *fully* understanding the semantics of every line of code that you write.

Problems arise when a programmer naïvely inserts a cast to “fix” a compiler error without understanding the implications of what he is doing—the program crashes; far worse consequences are possible. Recall that a program which gives the wrong answer (with no indication that something went wrong) is often far worse than a program that crashes. It is possible that we could instead read or write values that we did not intend to, and produce bogus results.



### Multidimensional Array

**多位数组在内存中的表示形式**

注意`[]`运算符从左往右的先后顺序

```c++
int arr[3][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
```

![img](https://media.geeksforgeeks.org/wp-content/uploads/Diagram2.png)

首先`[3]`分配3大块内存，`[4]`表示在每个3大块里面再分成4小块



**多位数组数组名退化后的类型与`[]`访问**

方法：画出多位数组在内存中的储存方式，根据下标的先后顺序画横线切块

```c++
int arr[2][3][2] = {
                       {
                         {5, 10},
                         {6, 11},
                         {7, 12},
                       },
                       {
                         {20, 30},
                         {21, 31},
                         {22, 32},
                       }
                     };
```

1. 画出总共有`2*3*2=12`个内存小块

![IMG_F14F91087529-1](/Users/bryant/Programming/CS106L-master/CS106L_2019/Slides/array_image/IMG_F14F91087529-1.png)

2. 根据下标依次划线分块

![IMG_72E2E5296E5F-1](/Users/bryant/Programming/CS106L-master/CS106L_2019/Slides/array_image/IMG_72E2E5296E5F-1.png)

理解：多维数组的本质还是1维数组

```
int arr[2]([3][2]) //当前所指下标后面的东西就是数组里面的element
	    |
	    先把整个内存分成两大块，两大块里面的东西是[3][2]的二维数组
int arr[2][3]([2])
		   |
		   再把上面两大块里面的东西分成3小块，里面的东西是[2]的一维数组
(int) arr[2][3][2]
				|
				再把上面各3小块里面的东西分成2小块，里面的东西是int
```

顺序图解：

![IMG_E84A4A81DA3C-1](/Users/bryant/Programming/CS106L-master/CS106L_2019/Slides/array_image/IMG_E84A4A81DA3C-1.png)



3. 各级指针退化图解

![IMG_367C2AEB776A-1](/Users/bryant/Programming/CS106L-master/CS106L_2019/Slides/array_image/IMG_367C2AEB776A-1.png)

每一条横线可以理解为一个地址，每一次dereference就相当于穿过1条横线

从图中可以看到，指针的base type不同，pointer arithmetic每次移动的bits也不同



**Pass a 2-D Array to a C++ Function**

```c++
void func(int (&arr)[m][n]);// strictly fixed size m*n by reference,remember the ()before []
void func(int (*arr)[m][n]); // note: pass the address of the 2-d arrat: func(&a); accessing element:dereference first (*a)[m][n]
void func(int (*arr)[size], int row); // constrain the size of col
void func(int arr[][size], int row); // same as above
void func(int** arr); // pointers to pointers: for array of pointers only
```

Generally, the fixed size can be determined by template

```c++
template<size_t m, size_t n>
void func(int (&arr)[m][n]);
```

Wrong method

```c++
void func(int (*arr)[], int row, int col); //(*arr)[], inside the [] cannot be empty
```



### Array Initialization

和普通变量类似，如果没有显式初始化：全局或局部静态会进行空初始化，别的就是undefined

- 局部非静态的数组：未初始化，数组里的所有元素都具有未定义的值。
- **全局或局部静态的数组**：**空初始化**，就是对数组里的所有元素进行**空初始化**。

问题：



**Caveat**: the size of an array must be determined **at compile time**! Once determined, the size is **fixed**.



### Referance

[Passing a 2D array to a C++ function](https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function)

[What is array to pointer decay?](https://stackoverflow.com/questions/1461432/what-is-array-to-pointer-decay)

[Pointer Decay](http://web.archive.org/web/20081208122434/http://www.transcendentaxis.com/dthompson/blog/archives/9)

[Pointer to an Array | Array Pointer](https://www.geeksforgeeks.org/pointer-array-array-pointer/)