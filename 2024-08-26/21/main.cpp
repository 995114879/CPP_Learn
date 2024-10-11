#include <iostream>

class Complex {
public:
    Complex(int real, int imag): real(real), imag(imag) {}
    int getReal() {
        return real;
    }

    int getImag() {
        return imag;
    }

    friend void print_complex(Complex& com);
    friend std::ostream& operator<<(std::ostream& os, const Complex& com);

private:
    int real;
    int imag;

};

void print_complex(Complex& com) {
    std::cout << '(' << com.real << ',' << com.imag << 'i' << ')';
}

std::ostream& operator<<(std::ostream& os, const Complex& com) {
    std::cout << "this is complex value: " << '(' << com.real << ',' << com.imag << 'i' << ')' << '\n';

    return os;
}

//void print_complex(Complex& com) {
//    std::cout << '(' << com.getReal() << ',' << com.getImag() << 'i' << ')';
//}

class Box {
private:
    double width;
public:
    Box(double w) : width(w) {}
    friend void printWidth(Box& b);  // friend 声明友元函数
};

void printWidth(Box& b) {
    std::cout << "Width of box: " << b.width << std::endl;  // 访问私有成员
}

class ClassA {
private:
    int privateMember;

public:
    ClassA() : privateMember(42) {}
    friend class ClassB;  // ClassB 将是 ClassA 的友元类
};

class ClassB {
public:
    void displayPrivateMember(const ClassA& a) {
        std::cout << "Private member of ClassA: " << a.privateMember << std::endl;
    }
};

class Parent {
private:
    int parentPrivate;

protected:
    int parentProtected;

public:
    Parent() : parentPrivate(10), parentProtected(20) {}
    friend void friendFunction(Parent& p);
};

void friendFunction(Parent& p) {
    std::cout << "Parent Private: " << p.parentPrivate << std::endl;
    std::cout << "Parent Protected: " << p.parentProtected << std::endl;
}

class Child : public Parent {
private:
    int childPrivate;

public:
    Child() : Parent(), childPrivate(30) {}

    // Note: friendFunction() inherits permission to access Parent's members
    friend void childFriendFunction(Child& c);
};

void childFriendFunction(Child& c) {
    // 可以访问父类的私有和受保护部分
    //friendFunction(c);

    // 仅可以访问子类的受保护成员
    std::cout << "Child Private: " << c.childPrivate << std::endl;
    std::cout << "Parent Protected Access via Child: " << c.parentProtected << std::endl;
}

int main() {
//    // (3, 4i)
    Complex com(3, 4);
//    print_complex(com);
    std::cout << com << '\n';

    /*
    Box box(10.0);
    printWidth(box);
     */

    /*
    ClassA a;
    ClassB b;
    b.displayPrivateMember(a);
     */

    /*
    Child c;
    childFriendFunction(c);
     */

    return 0;
}