#include <iostream>
//#include <stdio.h>
#include <cstdio> // 内置的头文件

#include "test.h"
// Python module

int main()
{
    std::cout << "Hello, World!" << std::endl;
    printf("hello world\n");
    greet();

    int a = 2, b = 3;
    // int a = 2;
    // int b = 3;

    int i = 10;
    int c = ++i;
    std::cout << "c = " << c << std::endl;
    std::cout << "i = " << i << std::endl;

    int d = 2;
    int e = 3;
    int f = (d > e) ? d : e;
    std::cout << "f = " << f << std::endl;

    for (auto i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            continue;
        }
        std::cout << "i = " << i << std::endl;
    }

    double res = area(2);
    std::cout << "res = " << res << std::endl;

    /*
    int xx = 1;
    int* p2xx = &xx;
    std::cout << "p2xx = " << p2xx << std::endl;
    int* p2xx1 = p2xx+1;
    std::cout << "p2xx1 = " << p2xx1 << std::endl;
    */
    /*
    int arr[3]{1,2,3};
    int* ptr = &arr[0];
    std::cout << *(ptr+1) << std::endl;
    */
    int arr[2][3]{{1,2,3}, {4, 5, 6}};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << "arr = " << arr << std::endl;
    std::cout << "arr + 1 = " << arr+1 << std::endl;
    std::cout << "a[1] = " << arr[1] << std::endl;
    std::cout << "arr[1][0] = " << arr[1][0] << std::endl;
    std::cout << "*arr[1] = " << *(arr+1) << std::endl;
    std::cout << **(arr + 1) << std::endl;
    return 0;
}
