#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<int> ptr1 = std::make_unique<int>(10);

    // std::unique_ptr<int> ptr2 = ptr1; // 错误: unique_ptr 不允许复制

    std::unique_ptr<int> ptr2 = std::move(ptr1); // 所有权转移到 ptr2

    // ptr1 不再拥有该对象
    if (ptr1) {
        std::cout << *ptr1 << std::endl;
    } else {
        std::cout << "ptr1 is empty." << std::endl; // 输出: ptr1 is empty.
    }

    std::cout << *ptr2 << std::endl; // 输出: 10

    // ptr2 出作用域时，自动释放内存
    return 0;
}