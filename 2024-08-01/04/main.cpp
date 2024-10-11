#include <iostream>
#include <string>

struct Student {
    std::string name;
    int id;
    float score;
};

struct Test {
    char classic; // 1
    int  id;      // 4
};

struct Test2 {
    char c1;
    char c2;
};

struct Test3 {
    char c1;
    short s1;
};

struct Test4 {
private:
    char c1;
    char c2;
    short s2; //
};

enum week {
    w1 = 1,
    w2, // w1 + 1
    w3, // w1 + 2;
    w4,
    w5,
    w6,
    w7
};

union Data {
    char cx;
    int ix;
};

void greet();

int main() {
    Student s0;
    s0.name = "john";
    s0.id = 1;
    s0.score = 95.5;
    //
    Student* ps0 = &s0;
    std::cout << (*ps0).id << std::endl;
    std::cout << (*ps0).name << std::endl;
    std::cout << (*ps0).score << std::endl;

    std::cout << ps0->id << std::endl;
    std::cout << ps0->name << std::endl;
    std::cout << ps0->score << std::endl;

    Student& rs0 = s0;
    std::cout << rs0.name << std::endl;
    std::cout << rs0.id << std::endl;
    std::cout << rs0.score << std::endl;

    //
    Test t;
    std::cout << "t size = " << sizeof(t) << std::endl;

    Test2 t1;
    std::cout << "t size = " << sizeof(t1) << std::endl;

    Test3 t2;
    std::cout << "t size = " << sizeof(t2) << std::endl;

    Test4 t4;
    std::cout << "t4 size = " << sizeof(t4) << std::endl;
    // t4.c1;

    week today = w2;
    std::cout << today << std::endl;

    Data d1;
    d1.cx = 'a';
    std::cout << d1.cx << std::endl;
    d1.ix = 1;
    std::cout << d1.ix << std::endl;
    std::cout << sizeof(d1)  << std::endl;

    d1.ix = 97;
    std::cout << d1.cx << std::endl;

    d1.cx = 'a';
    std::cout << d1.ix << std::endl;

    greet();

    return 0;
}

void greet() {
    std::cout << "hello ....." << std::endl;
}

int test() {
    ////
    ///
    //if (true) {
    //    return x;
    //}
    // unlimited loop
    //for (;;) {
    //    //break;
    //    //return ...;
    //}
    //while(true) {
    //    //break;
    //}

    ///
}
