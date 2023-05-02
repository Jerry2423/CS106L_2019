/*
 * Lecture code for Lecture 8, Functions and Algorithms.
 *
 * Avery Wang - last updated 1/29/2020
 */

#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
using namespace std;

// We will represent a course on Carta/explorecourses with this struct.
struct Course {
    std::string name;
    double rating;
};

// This function allows you to print a Course struct to any ostream.
// Usage: std::cout << c << std::endl;
// We'll cover how to overload operators in about a week.
std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << std::setw(15) << std::setfill(' ') << c.name << "   " << c.rating;
    return os;
}

// This is the function template we wrote last lecture.
// Solves the problem "how many times does [type] [val] appear in [range of elements]"
// template <typename InputIt, typename DataType>
// int countOccurences(InputIt begin, InputIt end, const DataType& val) {
//     int count = 0;
//     for (auto iter = begin; iter != end; ++iter) {
//         if (*iter == val) ++count;
//     }
//     return count;
// }

template<typename InputIter,  typename UniPred>
int countOccurences (InputIter start, InputIter end,  UniPred pred) {
    int count = 0;
    for (auto i = start; i != end; ++i) {
        if (pred(*i))
            count ++;
    }
    return count;
}
// A predicate function that is specialized to limit = 5.
bool isLessThan5(int val) {
    return val < 5;
}

// A predicate function, returns true if val < limit, false otherwise.
bool isLessThanLimit(int val, int limit) {
    return val < limit;
}

// A function which returns a fixed vector.
// This is just a quick survey of common courses.
// Sorry for the bias towards the CS core.
std::vector<Course> readCourses() {
    std::vector<Course> v = {{"CS 106A", 4.4337}, {"CS 106B", 4.4025},
        {"CS 107", 4.6912}, {"CS 103", 4.0532},
        {"CS 109", 4.6062}, {"CS 110", 4.343},
        {"Math 51", 3.6119}, {"Math 52", 4.325},
        {"Math 53", 4.3111}, {"Econ 1", 4.2552},
           {"Anthro 3", 3.71}, {"Educ 342", 4.55},
           {"Chem 33", 3.50}, {"German 132", 4.83},
           {"Econ 137", 4.84}, {"CS 251", 4.24},
           {"TAPS 103", 4.79}, {"Music 21", 4.37},
           {"English 10A", 4.41}};
    // std::random_shuffle(v.begin(), v.end());
    return v;
}

// A function which returns a vector of a bunch of numbers.
std::vector<double> readNumbers() {
    std::vector<double> numbers;
    std::generate_n(std::back_inserter(numbers), 500, std::rand);
    return numbers;
}

int main() {
    // Count how many times 5 appears in the second half of a vector<int>.
    std::vector<int> phoneNumber{5, 5, 5, 8, 2, 6, 5, 5, 3, 5};
    int val = 5;
    auto isEqualToVal = [val] (int n) {
        return n == val;
    };
    int times1 = countOccurences(phoneNumber.begin() + phoneNumber.size()/2,
                                 phoneNumber.end(), isEqualToVal);
    std::cout << "the second half of phoneNumber contains " << times1
              << " elements of 5" << std::endl;

    // Count how many elements in the second half of a vector<int> are less than 5.
    int times2 = 0; // TODO: Edit this
    times2 = countOccurences(phoneNumber.begin(), phoneNumber.end() - phoneNumber.size() / 2, isLessThan5);
    std::cout << "the first half of phoneNumber contains " << times2
              << " elements that are at less than 5" << std::endl;

    // Fun with algorithms.
    auto courses = readCourses();
    auto numbers = readNumbers();
    std::copy(courses.begin(), courses.end(),
              std::ostream_iterator<Course>(std::cout, "\n"));

    // FILL IN YOUR CODE HERE

    //sort courses by ratings
    auto courseRank = [](Course& a, Course& b) {
        return a.rating < b.rating;
    };
    std::sort(courses.begin(), courses.end(), courseRank);
    cout << "rankings:" << endl;
    std::copy(courses.begin(), courses.end(),
              std::ostream_iterator<Course>(std::cout, "\n"));

    //partition the course by math: relative order preserved; thus by sorting first then partition, we can see math courses' 1)ranking 2)first
    string courseName = "Math";
    auto mathFirst = [courseName](Course& a) {
        return a.name.size() >= courseName.size() && a.name.substr(0, courseName.size()) == courseName;
    };
    std::stable_partition(courses.begin(), courses.end() , mathFirst);
    cout << "Math First Partition:" << endl;
    std::copy(courses.begin(), courses.end(),
              std::ostream_iterator<Course>(std::cout, "\n"));

    //Note: copy_if/copy function, for distination, we need a back_inserter(container) to give a iterator(back_insert_iterator) that an enlarge the size of the vector;
    // copy function is not a member function of vector, so it cannot enlarge vector automatically
    //every time when back_insert_iterator is assigned to, .push_back() is called, so the size if enlarge.
    //back_inserter,ostream_iterator are called iterator adaptor. Adapt the iterator to the real use case.
    cout << "All Math Courses:" << endl;
    std::vector<Course> allMathCourses;
    std::copy_if(courses.begin(), courses.end(), std::back_inserter(allMathCourses), mathFirst);
    std::copy(allMathCourses.begin(), allMathCourses.end(), std::ostream_iterator<Course>(std::cout, "\n")); // how is each course object is copied? overload << operator gives a ostream for os << aCourse; copy each os into the cout ostream, the trait/delimiter is '\n'


    cout << "Featured Math Courses:" << endl;
    double leastCourseRating = 4;
    auto isBadCourse = [leastCourseRating] (const Course& a) {
        return a.rating < leastCourseRating;
    };
    //erase-remove idiom: erase is a member function which can change size of vector; while remove function is a std functino can only remove elements but cannot reshape the vector
    allMathCourses.erase(std::remove_if(allMathCourses.begin(), allMathCourses.end(), isBadCourse));
    std::copy(allMathCourses.begin(), allMathCourses.end(), std::ostream_iterator<Course>(std::cout, "\n"));
}



