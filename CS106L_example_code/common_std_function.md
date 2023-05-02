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
