#include <iostream>
#include <stdio.h>

int main() {
    char str[] = {'h', 'e', 'l', 'l' ,'o'};
    char str1[] = "abcdef";
    //std::cout << str << std::endl;
    printf("%s\n", str);

    int i = 4;
    int* p1 = &i;
    int *p2 = &i;

    void* px = &i;
    std::cout << *(int*)px << std::endl;

    char* pstr = new char[4];
    int* pint = (int*)(pstr); // C的写法，选择完全相信程序员
    //int* pint2 = static_cast<int*>(static_cast<void*>(pstr));

    return 0;
}
