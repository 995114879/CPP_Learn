#include <iostream>
#include <stdlib.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    const char* s1 = "abc";
    int len = strlen(s1);
    std::cout << "len = " << len << std::endl;

    char arr1[] = "abc";
    std::cout << "arr1[] size = " << sizeof(arr1) << std::endl;

    std::cout << "*s1 = " << *s1 << std::endl;
    std::cout << "*(s1+1) = " << *(s1+1) << std::endl;
    std::cout << "*(s1+2) = " << *(s1+2) << std::endl;
    std::cout << "*(s1+3) = " << *(s1+3) << std::endl; // std::string

    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*p_row)[3] = matrix;  // 数组指针，指向包含3个整数的一维数组
    int (*p_row1)[3] = matrix + 1;  //

    /*
    using row_pointer = int (*)[3];
    row_pointer p_row = matrix;
    */

    std::cout << "二维数组matrix的地址：" << matrix << std::endl;
    std::cout << "行指针p_row的地址：" << p_row << std::endl; // 两者地址相同

    // 使用行指针访问二维数组元素
    std::cout << "matrix[1][2] = " << *(*(p_row + 1) + 2) << std::endl;
    std::cout << "matrix[1][2] = " << matrix[1][2] << std::endl;

    int (*funcptr)(int, int) = add;
    std::cout << funcptr(1,2) << std::endl;

    const char* ss1 = "abc";
    const char* ss2 = "abc";
    std::cout << (void*)&ss1[0] << std::endl;
    std::cout << (void*)&ss2[0] << std::endl;


    return 0;
}
