#include <iostream>
#include <string>

// struct,

struct Complex { //
    Complex(int real, int img): real(real), img(img) {}
    int real;
    int img;
    void show() {
        std::cout << "real = " << real << " img = " << img << '\n';
    }
    Complex operator+(const Complex& other) {
        std::cout << "member" << '\n';
        return Complex(this->real+other.real, this->img + other.img);
    }
};

Complex operator+(const Complex& c1, const Complex& c2) {
    std::cout << "global" << '\n';
    return Complex(c1.real+c2.real, c1.img + c2.img);
}

Complex complex_add(const Complex& c1, const Complex& c2) {
    return Complex(c1.real+c2.real, c1.img + c2.img);
}

int main() {
    Complex c1(1, 2);
    c1.show();
    Complex c2(2, 3);
    c2.show();
    Complex c3 = c1 + c2;
    c3.show();

    Complex c4 = complex_add(c1, c2);
    c4.show();

    Complex c5 = c1 + c2;
    c5.show();

    std::string abc;
    std::cout << std::boolalpha << abc.empty() << std::endl;

    std::string str = "H";

    for (char c : str) {
        if (isalpha(c)) std::cout << c << " is alphabetic\n";
        if (isdigit(c)) std::cout << c << " is a digit\n";
        if (ispunct(c)) std::cout << c << " is punctuation\n";
    }

    std::cout << "str[0]: " << str[0] << '\n';
    std::cout << "str[1]: " << str[1] << '\n';
    std::cout << "str[2]: " << str[2] << '\n';

    return 0;
}
