#include <iostream>
#include <string>


int add(int a, int b) {
    std::cout << "call nontemplate function" << '\n';
    return a + b;
}
/*
double add(double a, double b) {
    return a + b;
}

std::string add(std::string a, std::string b) {
    return a + b;
}*/

struct Test{
    Test(int t): t_(t) {}
    int t_;

    void show() {
        std::cout << "t inside = " << t_ << '\n';
    }
};

Test operator+(Test t1, Test t2) {
    return Test(t1.t_+t2.t_);
}


template <typename T>
T add(T a, T b) {
    return a + b;
}

template<typename T, typename RT>
RT add(T a, T b) {
    return RT(a+b);
}

template <typename T>
class MyArray {
private:
    T* data;
    int size;

public:
    MyArray(int size) : size(size) {
        data = new T[size];
    }

    ~MyArray() {
        delete[] data;
    }

    void set(int index, T value) {
        data[index] = value;
    }

    T get(int index) {
        return data[index];
    }
};

class MyContainer {
private:
    int value;

public:
    MyContainer(int value) : value(value) {}

    template <typename U>
    void printWith(U prefix) {
        std::cout << prefix << ": " << value << std::endl;
    }
};

template <typename T>
T sum(T arr[], int n) {
    T res{};
    for (auto i = 0; i < n; i++) {
        res += arr[i];
    }

    return res;
}

int main() {
    /*
    std::cout << add<int>(1, 2) << std::endl;
    std::cout << add<double>(1.1, 2.2) << std::endl;
    std::cout << add<std::string>(std::string("abc"), std::string("def")) << std::endl;
    Test t1(3);
    Test t2(6);
    Test t3 = add<Test>(t1, t2);
    t3.show();
    Test t4 = add<int, Test>(1, 2);
    t4.show();
     */
    int x = add(1, 2);
    double y = add(1.1, 2.1);
    std::cout << y << std::endl;
//    auto res = add<std::string, Test>(std::string("abc"), std::string("def"));

    MyContainer intContainer(10);
    intContainer.printWith<const char[]>("Integer");

    /*
    MyContainer<double> doubleContainer(3.14);
    doubleContainer.printWith<const char[]>("Double");
    doubleContainer.printWith<int>(123); // 可以传入不同类型的参数
    return 0;
     */

    int arr[]{1,2,3};
    double arr1[]{1.1, 2.1, 3.1};
    std::string arr2[]{std::string("abc"), std::string("def"), std::string("xyz")};
    std::cout << sum(arr, 3) << '\n';
    std::cout << sum(arr1, 3) << '\n';
    std::cout << sum(arr2, 3) << '\n';

    int yy{};
    std::string zz{};
    std::cout << "yy =" << yy << '\n';
    std::cout << "zz =" << std::boolalpha << zz.empty() << '\n';

    return 0;
}
