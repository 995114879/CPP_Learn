#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <forward_list>


template <typename T>
struct MyStack {
    MyStack() {
    }
    void push(const T& t) {
        stack_inside_.push_back(t);
    }

    T top() {
        return stack_inside_.back();
    }

    void pop() {
        return stack_inside_.pop_back();
    }

    bool empty() {
        return stack_inside_.empty();
    }

    std::vector<T> stack_inside_;
};

int main() {
    /*
    std::vector<int> vints{1,2,3};
    auto iter = vints.begin();
    std::cout <<"iter -> " <<  *iter << '\n';
    std::cout <<"iter -> " <<  *(iter+1) << '\n';
    auto iter2 = vints.end();
    std::cout << "iter2 -> " << *iter2 <<  '\n';
    std::cout << "iter2 -> " << *(iter2-1) << '\n';

    for (auto iter = vints.begin(); iter != vints.end(); ++iter) {
        std::cout << "iter-> " << *iter << '\n';
    }

    std::array<int, 5> arr{1,2,3,4};
    //int arrx[5]{1,2,3,4};
    for (const auto& e: arr) {
        std::cout << e << ' ';
    }

    for (auto iter = arr.begin(); iter != arr.end(); ++iter) {
        std::cout << *iter << ' ';
    }


    std::cout << '\n';


    /*
    std::vector<int> numbers = {1, 3, 4};
    //std::vector<int>::iterator it = numbers.begin() + 1; // 指向第二个元素 (3)
    auto it = numbers.begin() + 1; // 指向第二个元素 (3)
    numbers.insert(it, 2);

    for (int i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
     */
    /*
    std::vector<int> numbers = {1, 2, 3, 4};
    std::vector<int>::iterator it = numbers.begin() + 1; // 指向第二个元素 (2)
    auto after = numbers.erase(it);
    std::cout << "*after = " << *after << '\n';

    for (int i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    */

    /*
    std::vector<int> numbers{1,2,2,2,3,2,4};
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
        if (*iter == 2) {
            iter = numbers.erase(iter);
        }
    }
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << '\n';
     */
    /*
    std::vector<int> input{1, 2, 3, 2, 4};
    std::remove(input.begin(), input.end(),2);
    for (const auto& e: input) {
        std::cout << e << " " ;
    }

    std::forward_list<int> fl{1,2,3};
    fl.erase_after(fl.begin());
    std::cout << "--------" << std::endl;
    auto iter = fl.begin();
    iter++;
    std::cout << *iter << std::endl;

    std::cout << '\n';
     */
    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    while(!stack.empty()) {
        std::cout << stack.top() << ' ';
        stack.pop();
    }
    std::cout << '\n';



    return 0;
}
