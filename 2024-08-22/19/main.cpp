#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

bool is_even(int x) {
    return x % 2 == 0;
}

void add_one(int& x) {
    ++x;
}

int square(int x) {
    return x*x;
}

int main() {
    /*
    std::vector<int> vints{1,2,3,2,4};
    auto new_postion = std::remove(vints.begin(), vints.end(), 2);
    for (const auto& e : vints) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
    vints.erase(new_postion, vints.end());

    for (const auto& e : vints) {
        std::cout << e << ' ';
    }
     */

    /*
    std::vector<int> vec = {2, 4, 6, 8, 10, 11};

    //bool all_even = std::all_of(vec.begin(), vec.end(), [](int i){ return i % 2 == 0; });
    bool all_even = std::all_of(vec.begin(), vec.end(), is_even);

    std::cout << (all_even ? "All elements are even" : "Not all elements are even") << std::endl;
     */
    /*
    std::vector<int> vec = {1, 3, 5, 7, 9};

    bool has_even = std::any_of(vec.begin(), vec.end(), is_even);

    std::cout << (has_even ? "There is at least one even element" : "All elements are odd") << std::endl;
     */

    /*
    std::vector<int> vec = {1, 3, 5, 7};

    bool none_even = std::none_of(vec.begin(), vec.end(), is_even);

    std::cout << (none_even ? "None of the elements are even" : "There is at least one even element") << std::endl;
     */

    /*
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::for_each(vec.begin(), vec.end(), add_one);

    for (const auto& n : vec) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
     */

    /*
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> result(vec.size());

    std::transform(vec.begin(), vec.end(), result.begin(), square);

    for (const auto& v : result) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
     */

    /*
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination(source.size()-1);

    std::copy(source.begin(), source.end()-1, destination.begin());

    for (const auto& v : destination) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
     */

    /*
    std::vector<int> vec = {1, 2, 3, 2, 4, 2, 5};

    std::replace(vec.begin(), vec.end(), 2, 10);

    for (const auto& v : vec) {
        std::cout << v << " ";
    }

    std::cout << std::endl;
     */

    /*
    std::vector<int> vec(5);

    std::fill(vec.begin(), vec.end(), 7);

    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
     */
    /*
    std::vector<int> vec = {1, 2, 3, 4, 5};

    int sum = std::accumulate(vec.begin(), vec.end(), 0);

    std::cout << "Sum: " << sum << std::endl;
     */

    /*
    std::vector<int> vec(100);

    std::iota(vec.begin(), vec.end(), 1);

    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
     */

    /*
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2};

    std::sort(vec.begin(), vec.end(), std::greater<int>());

    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
     */

    /*
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};

    auto it = std::find(vec.begin(), vec.end(), 4);

    if (it != vec.end()) {
        std::cout << "Element found at position: " << std::distance(vec.begin(), it) << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }
     */

    /*
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};

    bool found = std::binary_search(vec.begin(), vec.end(), 4);

    std::cout << (found ? "Element found" : "Element not found") << std::endl;
     */
    std::vector<int> vec = {1, 2, 3, 3, 3, 4, 5};

    auto range = std::equal_range(vec.begin(), vec.end(), 3);

    std::cout << "First occurrence of 3 at position: " << std::distance(vec.begin(), range.first) << std::endl;
    std::cout << "Last occurrence of 3 at position: " << std::distance(vec.begin(), range.second) - 1 << std::endl;










    return 0;
}
