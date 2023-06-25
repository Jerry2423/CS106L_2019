### std::count, std::count_if

`count( InputIt first, InputIt last, const T& value );`
`count_if( InputIt first, InputIt last, UnaryPredicate p );`

Note:
- The type of the `value` in `std::count` must be the **same** the type the iterator pointing to.
- Predicate `p` can be defined by lambda function.


### std::stable_partition

`BidirIt stable_partition( BidirIt first, BidirIt last, UnaryPredicate p );`
Reorders the elements in the range [first, last) in such a way that all elements for which the predicate `p` returns true precede the elements for which predicate `p` returns false. Relative order of the elements is preserved.

### std::sort

`void sort( RandomIt first, RandomIt last, Compare comp );`

### std::remove and std::erase

**erase-remove idiom**: `container.erase(std::remove(...));`

`ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );`
`ForwardIt remove_if( ForwardIt first, ForwardIt last, UnaryPredicate p );`

Note the difference between `erase` and `remove`

`remove` do not change the physical size:

> Removing is done by **shifting** (by means of [copy assignment](https://en.cppreference.com/w/cpp/language/copy_assignment) (until C++11)[move assignment](https://en.cppreference.com/w/cpp/language/move_assignment) (since C++11)) the elements in the range in such a way that the <u>elements that are not to be removed appear in the beginning of the range.</u> Relative order of the elements that remain is preserved and the <u>*physical* size of the container is unchanged.</u> Iterators pointing to an element between the <u>new *logical* end and the *physical* end of the range are still [dereferenceable](https://en.cppreference.com/w/cpp/iterator#Dereferenceability_and_validity), but the elements themselves have unspecified values</u> (as per [*MoveAssignable*](https://en.cppreference.com/w/cpp/named_req/MoveAssignable) post-condition) (since C++11).

For container, it's better to use `erase`: [link](https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index)

```c++
std::vector<int> vec;

vec.push_back(6);
vec.push_back(-17);
vec.push_back(12);

// Deletes the second element (vec[1])
vec.erase(std::next(vec.begin()));

// Deletes the second through third elements (vec[1], vec[2])
vec.erase(std::next(vec.begin(), 1), std::next(vec.begin(), 3));
```



### std::next and std::advance

`next` return the `n`th successor (or `-n`th predecessor if `n` is negative) of iterator `it`. `advance` increments given iterator it by n elements.

### std::copy, std::copy_if

`OutputIt copy( InputIt first, InputIt last, OutputIt d_first );`
`OutputIt copy_if( InputIt first, InputIt last,
                  OutputIt d_first,
                  UnaryPredicate pred );`

**iterator-adaptor**:
Look at the following example:
```
//Note: copy_if/copy function, for distination, we need a back_inserter(container) to give a iterator(back_insert_iterator) that an enlarge the size of the vector;
// copy function is not a member function of vector, so it cannot enlarge vector automatically
//every time when back_insert_iterator is assigned to, .push_back() is called, so the size if enlarge.
//back_inserter,ostream_iterator are called iterator adaptor. Adapt the iterator to the real use case.

std::vector<Course> allMathCourses;
std::copy_if(courses.begin(), courses.end(), std::back_inserter(allMathCourses), mathFirst);
std::copy(allMathCourses.begin(), allMathCourses.end(), std::ostream_iterator<Course>(std::cout, "\n")); // how is each course object is copied? overload << operator gives a ostream for os << aCourse; copy each os into the cout ostream, the trait/delimiter is '\n'

```


### std::transform
`OutputIt transform( InputIt first1, InputIt last1,
                    OutputIt d_first, UnaryOperation unary_op );`

> `std::transform` applies the given function `unary_op` to a range and **stores the result in another range**`d_first`, keeping the original elements order and beginning at d_first.

Examples: 
- Transform a string to lower case by apply `::tolower` to each `char` where `InputIt` points to.

### std::search
`ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                   ForwardIt2 s_first, ForwardIt2 s_last );`

> Searches for the first occurrence of the sequence of elements [`s_first`, `s_last`) in the range [`first`, `last`).

Examples:
- Search a word in a string.

### std::inner_product
`T inner_product( InputIt1 first1, InputIt1 last1, InputIt2 first2, T init );`

> Computes inner product (i.e. sum of products) or performs ordered map/reduce operation on the range [`first1`, `last1`) and the range beginning at `first2`. Then add the product to `init`.

Note:
Knowing v2.begin() is enough since v1, v2 are the same length and by knowing the begin and end of v1, and begin of v2, we know end of v2 = v2.begin() + (v1.end() - v1.begin())
