#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>
// using namespace std;
using std::cin; using std::cout; using std::endl;
using std::vector;

template<typename T, typename U>
std::unique_ptr<T> make_unique(U&& arg) {
    return {new T(std::forward<U>(arg))};
}

template<typename T, typename ... Types>
void print(const T& v1, Types... rest) {
    cout << v1 << endl;
    if constexpr(sizeof...(rest) > 0) {
        print(rest...);
    }
}

// template<typename Iterator>
// // auto my_distance_impl(Iterator begin, Iterator end, std::random_access_iterator_tag) {
// //     return end - begin;
// // }    
// //
// // template<typename Iterator>
// // auto my_distance_impl(Iterator begin, Iterator end, std::input_iterator_tag) {
// //     typename Iterator::difference_type result = 0;
// //     while (begin != end) {
// //         ++begin;
// //         ++result;
// //     }
// //     return result;
// // }

// template<typename Iterator>
// auto my_distance(Iterator begin, Iterator end) {
//     using category = typename Iterator::iterator_category;
//     return my_distance_impl(begin, end, category{});
// }

// template<typename Itetator>
// auto my_distance(Itetator begin, Itetator end) {
//     using category = typename std::iterator_traits<Itetator>::iterator_catogry;
//     if constexpr(std::is_same_v<category, std::random_access_iterator_tag>) {
//         return end - begin;
//     } else {
//         typename Itetator::difference_type result = 0;
//         while (begin != end) {
//             ++begin;
//             result ++;
//         }
//         return result;
//     }
// }

// template<int U, int W>
// struct is_same {
//     static const bool value = U==W;
// };

template<typename T, typename U>
struct is_same {
    static const bool value = false;
};

//static member var as return Value
template<typename T>
struct is_same<T, T> {
    static const bool value = true;
};

//member type as return Type value
template<typename T>
struct remove_const {
    using type = T;
};

template<typename T>
struct remove_const<const T> {
    using type = T;
};


template<typename Iterator>
auto my_distance(Iterator begin, Iterator end) {
    using it_type = typename std::iterator_traits<Iterator>::iterator_category;
    if constexpr (std::is_same_v<it_type, std::random_access_iterator_tag>) {
        return end - begin;
    } else {
        typename std::iterator_traits<Iterator>::difference_type result = 0;
        while (begin != end) {
            ++begin;
            ++result;
        }
        return result;
    }
}

int main() {
    const int a = 10;
    auto& ref = a;
    auto&& ref2 = a;
    auto&& ref3 = 9+1;
    print(1, 2, 3.14,
          "Pass me any "
          "number of arguments",

          "I will print\n");
    cout << is_same<int, double>::value << endl;
    vector<int> v = {1, 2, 3};
    cout << my_distance(v.begin(), v.end()) << endl;
}
