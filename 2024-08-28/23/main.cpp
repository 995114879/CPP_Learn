//#include <iostream>
//#include <fstream>
//#include <numeric>
//#include <vector>
//
//void checkPermission(int permissions, int requiredPermission) {
//    if (permissions & requiredPermission) {
//        std::cout << "Permission granted." << std::endl;
//    } else {
//        std::cout << "Permission denied." << std::endl;
//    }
//}
//
//void swap(int &a, int &b) {
//    a = a ^ b;
//    b = a ^ b;
//    a = a ^ b;
//}
//
//int singleNumber(std::vector<int>& nums) {
//    int result = 0;
//    for(int num : nums) {
//        result ^= num;
//    }
//    return result;
//}
//
//int main() {
//#if 0
//    unsigned int a = 3;  // 0b0000 0011 in binary
//    unsigned int b = 5;  // 0b0000 0101 in binary
//                         // 0b0000 0001
//    std::cout << "a & b: " << (a & b) << std::endl; // 输出 1 (001 in binary)
//
//    int a = 2;  // 0b0000 0010 in binary
//    int b = 6;  // 0b0000 0110 in binary
//                // 0b0000 0110
//    std::cout << "a | b: " << (a | b) << std::endl; // 输出 6 (110 in binary)
//
//    int x = 12; // 0b0000 1100 in binary
//    int y = 25; // 0b0001 1001 in binary
//                // 0b0001 0101
//    std::cout << "x ^ y: " << (x ^ y) << std::endl; // 结果为 21 (10101 in binary)
//    unsigned int n = 1; // 00000001 in binary
//    std::cout << "~n: " << (~n) << std::endl; // 注意：结果取决于系统位数
//    std::cout << "+n: " << std::numeric_limits<unsigned int>::max() << '\n';
//
//
//    int z = 1; // 00000001
//    std::cout << "z << 2: " << (z << 2) << std::endl; // 00000100 (4 in decimal)
//    std::cout << "z >> 1: " << (z >> 1) << std::endl; // 00000000 (0 in decimal)
//
//    int userPermission = 0b0101; // 读和写权限
//    checkPermission(userPermission, 0b0001); // 检查读权限
//    checkPermission(userPermission, 0b0010); // 检查写权限
//    checkPermission(userPermission, 0b0011); // 检查写权限
//
//    int a = 3;
//    int b = 4;
//    swap(a, b);
//    std::cout << "a = " << a << "b = " << b << '\n';
//    std::vector<int> numbers = {4,1,2,1,2};
//    std::cout << "The single number is: " << singleNumber(numbers) << std::endl;
//
//    // 创建一个包含4位的bitset，所有位初始为0
//    std::bitset<4> bset1;
//    // 通过字符串初始化bitset
//    std::bitset<4> bset2("1011");
//
//    std::cout << "bset1: " << bset1 << std::endl;
//    std::cout << "bset2: " << bset2 << std::endl;
//
//    // 设置某一位为1或0
//    bset1[1] = 1; // 设置第二位为1
//    std::cout << "After setting: " << bset1 << std::endl;
//
//    std::bitset<4> bset1(9); // 1001
//    std::bitset<4> bset2(5); // 0101
//
//    // 按位逻辑运算
//    std::cout << "bset1 & bset2: " << (bset1 & bset2) << std::endl;
//    std::cout << "bset1 | bset2: " << (bset1 | bset2) << std::endl;
//    std::cout << "bset1 ^ bset2: " << (bset1 ^ bset2) << std::endl;
//
//    // 翻转所有位
//    std::cout << "~bset1: " << (~bset1) << std::endl;
//
//    // 测试某一位
//    std::cout << "Is the second bit of bset1 set? " << bset1.test(1) << std::endl;
//#endif
//
//    std::bitset<4> bits("1010");
//    // 转换为字符串
//    std::string str = bits.to_string();
//    std::cout << "String representation: " << str << std::endl;
//
//    // 转换为无符号长整数
//    unsigned long num = bits.to_ulong();
//    std::cout << "As unsigned long: " << num << std::endl;
//
//    // Note: 当bitset的大小超过unsigned long的位数时，会抛出overflow_error
//    try {
//        std::bitset<65> tooLarge(-1l);
//        tooLarge.to_ulong(); // This will throw
//    } catch(const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//
//    return 0;
//}

#include <iostream>
#include <bitset>
#include <stdexcept>

template<size_t Size>
class BitSet {
public:
    BitSet() : bits() {}  // 模板构造函数，无需参数，直接使用模板参数Size


private:
    std::bitset<Size> bits; // 使用模板参数来定义bitset的大小
};

int main() {
    try {
        BitSet<10> bs;  // 现在可以用任意的大小来初始化BitSet了
//        bs.flip(2);
//        std::cout << "Bit at position 2 is: " << (bs.check(2) ? "set" : "not set") << std::endl;

        // 测试越界的情况
//        bs.check(10); // 这会抛出异常
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}