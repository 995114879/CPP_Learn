## C++ 课程第九课：指针、内存管理和类的基础

**学习目标：**

* 掌握数组传参的特性。
* 理解 `new` 和 `delete` 的用法，并能正确地进行动态内存分配和释放。
* 认识内存越界和内存泄漏的危害，并学会避免这些问题。
* 掌握指针安全使用的原则。
* 了解 C++ 的输入输出流 `cin` 和 `cout`。
* 初步了解类的概念、构造函数、析构函数、公有成员和私有成员。

---

### 1. 数组传参

数组传参时，会退化为指针，指向数组的第一个元素。这意味着在函数内部修改数组元素，会影响到原始数组。


**代码示例：**

```c++
#include <iostream>

void modifyArray(int arr[], int size) {
  for (int i = 0; i < size; ++i) {
    arr[i] *= 2; 
  }
}

int main() {
  int arr[5] = {1, 2, 3, 4, 5};
  modifyArray(arr, 5);

  for (int i = 0; i < 5; ++i) {
    std::cout << arr[i] << " "; // 输出：2 4 6 8 10
  }
  std::cout << std::endl;
  return 0;
}
```

**解释：**

`modifyArray` 函数接受一个 `int` 数组和它的尺寸作为参数。函数内部修改了数组元素，由于数组传参退化为指针，所以修改会影响到 `main` 函数中的 `arr` 数组。

---


### 2. 数组的 `new` 和 `delete`

`new` 用于动态分配内存，`delete` 用于释放 `new` 分配的内存。

**代码示例：**

```c++
#include <iostream>

int main() {
  // 使用 new 分配一个包含 5 个整数的数组
  int *b = new int[5];

  // 初始化数组元素
  for (int i = 0; i < 5; ++i) {
    b[i] = i * 2;
  }

  // 打印数组元素
  for (int i = 0; i < 5; ++i) {
    std::cout << b[i] << " "; // 输出：0 2 4 6 8
  }
  std::cout << std::endl;

  // 使用 delete[] 释放数组内存
  delete[] b;

  return 0;
}
```

**解释：**

* `int *b = new int[5];` 分配了一个包含 5 个整数的内存块，并将起始地址赋给指针 `b`。
* `delete[] b;` 释放了 `b` 指向的内存块。

**C 语言中的对应操作：**

* `malloc`: 用于动态分配内存。
* `free`: 用于释放 `malloc` 分配的内存。

---


### 3. 内存越界

访问不属于自己管理范围的内存地址，会导致程序崩溃或产生不可预期的结果。

**代码示例：**

```c++
#include <iostream>

int main() {
  int arr[5] = {1, 2, 3, 4, 5};

  // 尝试访问 arr[5]，越界访问
  std::cout << arr[5] << std::endl; // 可能导致程序崩溃或输出垃圾值

  return 0;
}
```

**解释：**

数组 `arr` 只有 5 个元素，索引范围是 0 到 4。访问 `arr[5]` 就超出了数组的边界，导致内存越界。

---

### 4. 内存泄漏

手动申请的内存地址，没有手动释放，会导致内存泄漏。

**代码示例：**

```c++
#include <iostream>

void leakMemory() {
  int *p = new int;
  *p = 10;
  // 缺少 delete p;
}

int main() {
  leakMemory(); // 每次调用都会泄漏 4 字节的内存
  return 0;
}
```

**解释：**

`leakMemory` 函数分配了内存，但没有释放。每次调用该函数，都会泄漏一部分内存。

---

### 5. 指针的安全使用

为了避免内存错误，需要遵循指针安全使用的原则：

**(1) 指针未指向需要的地址前，先置空 `p = nullptr`**

**(2) 使用前判断，是否为空指针 `nullptr`**

**(3) 谁申请的谁释放。自动申请的，请不要手动 `delete` 释放，手动申请的一定要手动 `delete` 释放**

**(4) 建议：哪里申请的，哪里释放。**

**(5) 不要释放已经释放的指针**

**(6) 释放后，立即置空。`p = nullptr`**

**(7) 释放前判断，是否为空指针 `nullptr`**

**代码示例：**

```c++
#include <iostream>

int main() {
  int *p = nullptr; // 初始化为空指针

  if (p != nullptr) { // 检查是否为空指针
    *p = 10;
  }

  p = new int; // 分配内存

  if (p != nullptr) { 
    *p = 10;
    delete p; // 释放内存
    p = nullptr; // 置空指针
  }

  return 0;
}
```

---

### 6. `cin` 输入流，`cout` 输出流

`cin` 和 `cout` 是 C++ 标准库提供的输入输出流对象，用于从键盘读取数据和向屏幕输出数据。

**代码示例：**

```c++
#include <iostream>

int main() {
  int a;

  std::cout << "请输入一个整数：";
  std::cin >> a; // 从键盘读取一个整数

  std::cout << "您输入的整数是：" << a << std::endl; // 输出结果

  return 0;
}
```

**解释：**

* `cin >> a;`  从键盘读取一个整数，并将其存储到变量 `a` 中。
* `cout << a;` 将变量 `a` 的值输出到屏幕。

**`#include <iostream>`**: 包含输入输出流相关的头文件。

---

### 7. 简单的类

类是面向对象编程的基本概念，用于封装数据和操作。

**代码示例：**

```c++
#include <iostream>

class Rectangle {
public:
  int width;
  int height;

  int getArea() {
    return width * height;
  }
};

int main() {
  Rectangle rect;
  rect.width = 5;
  rect.height = 10;

  std::cout << "矩形面积：" << rect.getArea() << std::endl; // 输出：50

  return 0;
}
```

**解释：**

`Rectangle` 类包含两个成员变量 `width` 和 `height`，以及一个成员函数 `getArea()`，用于计算矩形面积。

---

### 8. 构造和析构

构造函数在创建对象时调用，用于初始化对象；析构函数在销毁对象时调用，用于释放资源。

**代码示例：**

```c++
#include <iostream>

class Person {
public:
  Person(const std::string& name, int age) : name(name), age(age) {
    std::cout << "构造函数被调用，姓名：" << name << "，年龄：" << age << std::endl;
  }

  ~Person() {
    std::cout << "析构函数被调用，姓名：" << name << "，年龄：" << age << std::endl;
  }

private:
  std::string name;
  int age;
};

int main() {
  Person p("张三", 20);

  return 0;
}
```

**解释：**

* `Person(const std::string& name, int age)` 是构造函数，在创建 `Person` 对象时调用。
* `~Person()` 是析构函数，在 `Person` 对象销毁时调用。

---

### 9. 公有和私有

公有成员可以在类外部访问，私有成员只能在类内部访问。

**代码示例：**

```c++
#include <iostream>

class Person {
public:
  std::string getName() const { return name; }
  void setName(const std::string& name) { this->name = name; }

private:
  std::string name;
};

int main() {
  Person p;
  p.setName("张三");
  std::cout << p.getName() << std::endl; // 输出：张三

  // 无法访问私有成员 name
  // std::cout << p.name << std::endl; // 编译错误

  return 0;
}
```

**解释：**

* `getName()` 和 `setName()` 是公有成员函数，可以在类外部访问。
* `name` 是私有成员变量，只能在类内部访问。

---

### `sizeof(cout)`

`sizeof(cout)` 的结果取决于编译器和操作系统，通常是一个较大的值，因为它是一个复杂的对象，包含了大量的内部数据和函数。

---

## 作业


### 1. 封装一个 Student 类

```c++
#include <iostream>
#include <string>

class Student {
public:
    Student(const std::string& name, int score) : name(name), score(score) {
        std::cout << "Student 构造函数: " << name << ", " << score << std::endl;
    }

    ~Student() {
        std::cout << "Student 析构函数: " << name << ", " << score << std::endl;
    }

    std::string getName() const { return name; }
    int getScore() const { return score; }

private:
    std::string name;
    int score;
};

int main() {
    Student s1("张三", 80);
    Student s2("李四", 90);
    Student* s3 = new Student("王五", 75);

    std::cout << "sizeof(s1): " << sizeof(s1) << std::endl;
    std::cout << "sizeof(s2): " << sizeof(s2) << std::endl;
    std::cout << "sizeof(s3): " << sizeof(s3) << std::endl; // 指针大小，通常是4或8字节

    double average = (s1.getScore() + s2.getScore() + s3->getScore()) / 3.0;
    std::cout << "平均成绩: " << average << std::endl;

    delete s3;

    return 0;
}
```

> [!TIP]
>
> 在构造函数和析构函数中添加输出语句，观察对象在复制、赋值、传参等过程中的构造和析构行为。