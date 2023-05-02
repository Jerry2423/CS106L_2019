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

## std::remove
**erase-remove idiom**: `container.erase(std::remove(...));`

`ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );`
`ForwardIt remove_if( ForwardIt first, ForwardIt last, UnaryPredicate p );`

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
