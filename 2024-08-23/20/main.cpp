#include <iostream>
#include "abc.hpp"


/*
struct MyException {
    std::string message = "my exception";
};
 */

/*
int divide(int a, int b) { // b != 2, b !=3
    if (b == 0) {
        throw std::string("divided by zero fatal");
    } else if (b == 2) {
        throw -1;
    } else if (b == 3) {
        throw 1.1;
    } else if (b == 4) {
        throw MyException();
    }

    return a / b;
}
 */

//int divide(int a, int b) {
//    if (b == 0) {
//        throw std::runtime_error("Error: Division by zero!");
//    }
//    return a / b;
//}

class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "My custom exception occurred!";
    }

};

// functionA -> ()-> -> ->

#ifndef ONE
#define ONE
int divide(int a, int b) {
    if (b == 0) {
        throw MyException();
    }
    return a / b;
}
#endif // ONE

void functionC() {
    throw 100;
}

void functionB() {
    functionC();
}

void functionA() {
    try {
        functionB();
    }
    catch(int& e) {
       std::cout << e << '\n' ;
    }
}

int main() {
    //int result = divide(10, 0);
    //int result = divide(-2, 2);
    /*
    try {
        int result = divide(2, 4);
        std::cout << "result = "  << result << '\n';

    } catch(int& error) {
        std::cout << "catch exception = " << error << '\n';
    } catch(std::string& error) {
        std::cout << error << '\n';
    } catch(double& error) {
        std::cout << error << '\n';
    }
    catch(MyException& error) { // final
        // TODO: fix exception
        std::cout << error.message << '\n';
    } catch(...) {

    }*/
    /*
    try {
        int result = divide(10, 0);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "catch first" << '\n';
    }
    catch (const MyException& e) {
        std::cout << e.what() << std::endl;
    }*/
    functionA();

    return 0;
}