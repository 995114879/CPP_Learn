#include <iostream>

class MyClass { // 业务逻辑
public:
    MyClass(int value) : value_(value) {}

    void set_value(int value) {
        value_ = value;
    }

    int get_value() const {
        return value_;
    }

    void display() const {
        std::cout << "Value: " << value_ << std::endl;
    }

private:
    int value_;
};

// C 兼容接口
extern "C" {
    // 创建MyClass的实例
    MyClass* MyClass_new(int value) {
        return new MyClass(value);
    }

    // 销毁MyClass的实例
    void MyClass_delete(MyClass* instance) {
        delete instance;
    }

    // 调用MyClass的set_value方法
    void MyClass_set_value(MyClass* instance, int value) {
        instance->set_value(value);
    }

    // 调用MyClass的get_value方法
    int MyClass_get_value(MyClass* instance) {
        return instance->get_value();
    }

    // 调用MyClass的display方法
    void MyClass_display(MyClass* instance) {
        instance->display();
    }
}