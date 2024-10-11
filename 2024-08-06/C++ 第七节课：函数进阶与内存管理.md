## C++ 第七节课：函数进阶与内存管理

---

### 一、回调函数 6

**概念：** 将一个函数的指针作为参数传递给另一个函数，使得另一个函数能够在需要的时候调用该函数。

**作用：** 提升代码的灵活性和可扩展性。

**示例代码：**

```cpp
#include <iostream>

// 回调函数
void printMessage(int num) {
  std::cout << "回调函数被调用，数字为: " << num << std::endl;
}

// 接收回调函数指针作为参数的函数
void callFunction(void (*callback)(int), int num) {
  callback(num);
}

int main() {
  // 将 printMessage 函数的指针传递给 callFunction
  callFunction(printMessage, 10);
  return 0;
}
```

**讲解要点：**

* 函数指针的声明方式。
* 如何将函数指针作为参数传递。
* 回调函数的实际应用场景，例如事件处理、排序算法定制等。

---

### 二、函数的递归调用 6

**概念：** 函数直接或间接地调用自身。

**关键：**

* 递归的终止条件 (Base Case)。
* 递归的递推关系。

**示例代码：**

```cpp
#include <iostream>

// 计算阶乘
int factorial(int n) {
  // 递归终止条件
  if (n == 0) {
    return 1;
  }
  // 递归调用
  return n * factorial(n - 1);
}

int main() {
  int num = 5;
  std::cout << num << " 的阶乘是: " << factorial(num) << std::endl;
  return 0;
}
```

**讲解要点：**

* 递归的优缺点。
* 递归与迭代的比较。
* 避免无限递归。
* 栈溢出的风险。

---

### 三、new 和 delete 4

**概念：**

* `new` 运算符用于动态分配内存。
* `delete` 运算符用于释放 `new` 分配的内存。

**示例代码：**

```cpp
#include <iostream>

int main() {
  // 使用 new 分配一个 int 类型的内存空间
  int* ptr = new int;
  *ptr = 10;
  std::cout << "ptr 指向的值: " << *ptr << std::endl;

  // 使用 delete 释放内存
  delete ptr;

  return 0;
}
```

**讲解要点：**

* 动态内存分配的必要性。
* `new` 和 `delete` 的使用方法。
* 内存泄漏的概念和危害。

---

### 四、内存中的栈区和堆区 4

**概念：**

* **栈区 (Stack):** 由编译器自动分配和释放，用于存储局部变量、函数参数等。
* **堆区 (Heap):** 由程序员手动分配和释放，用于存储动态分配的内存。

**示例代码：**

```cpp
#include <iostream>

int main() {
  // 栈区变量
  int a = 10;

  // 堆区变量
  int* b = new int;
  *b = 20;

  std::cout << "栈区变量 a: " << a << std::endl;
  std::cout << "堆区变量 b: " << *b << std::endl;

  delete b;

  return 0;
}
```

**讲解要点：**

* 栈区和堆区的区别。
* 栈区和堆区的内存分配方式。
* 栈溢出和堆溢出。

---

### 五、全局变量、局部变量、static 静态变量 4

**概念：**

* **全局变量 (Global Variable):** 在所有函数外部定义，具有全局作用域。
* **局部变量 (Local Variable):** 在函数内部定义，具有局部作用域。
* **static 静态变量 (Static Variable):** 在函数内部定义，但只初始化一次，生命周期与程序相同。

**示例代码：**

```cpp
#include <iostream>

// 全局变量
int globalVar = 10;

void func() {
  // 局部变量
  int localVar = 20;
  // static 静态变量
  static int staticVar = 30;

  std::cout << "全局变量: " << globalVar << std::endl;
  std::cout << "局部变量: " << localVar << std::endl;
  std::cout << "静态变量: " << staticVar << std::endl;

  localVar++;
  staticVar++;
}

int main() {
  func();
  func();
  return 0;
}
```

**讲解要点：**

* 三种变量的作用域和生命周期。
* static 关键字的作用。
* 全局变量的使用注意事项。

---

### 六、函数的指针传参和引用传参 2

**概念：**

* **值传递 (Pass by Value):** 将参数的值复制一份传递给函数。
* **指针传递 (Pass by Pointer):** 将参数的地址传递给函数。
* **引用传递 (Pass by Reference):** 将参数的别名传递给函数。

**示例代码：**

```cpp
#include <iostream>

// 值传递
void swapByValue(int a, int b) {
  int temp = a;
  a = b;
  b = temp;
}

// 指针传递
void swapByPointer(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// 引用传递
void swapByReference(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  int x = 10, y = 20;

  // 值传递
  swapByValue(x, y);
  std::cout << "值传递后: x = " << x << ", y = " << y << std::endl; // x = 10, y = 20

  // 指针传递
  swapByPointer(&x, &y);
  std::cout << "指针传递后: x = " << x << ", y = " << y << std::endl; // x = 20, y = 10

  // 引用传递
  swapByReference(x, y);
  std::cout << "引用传递后: x = " << x << ", y = " << y << std::endl; // x = 10, y = 20

  return 0;
}
```

**讲解要点：**

* 三种传参方式的区别。
* 指针和引用的概念。
* 二级指针的应用场景。

---

## 作业

编写一个 C++ 函数，使用递归方法计算斐波那契数列的第 n 项。

**斐波那契数列定义：**

- F(0) = 0
- F(1) = 1
- F(n) = F(n-1) + F(n-2) (n >= 2)