## C++ 第 15 课：运算符重载与 String 类详解

**主要内容：**

1. **运算符重载**
2. **String 类详解**
    * 字符串操作函数
    * 访问字符串元素

3. **静态数组和动态数组**

---

### 1. 运算符重载

**引入：** C++ 允许我们为自定义的数据类型重新定义运算符的行为。这使得我们可以像操作内置类型一样，方便地操作自定义类型。

**例子：** 假设我们有一个 `Complex` 类表示复数。

**没有运算符重载**

```cpp
class Complex {
public:
  double real;
  double imag;

  Complex(double r = 0, double i = 0) : real(r), imag(i) {}
};

int main() {
  Complex c1(2, 3);
  Complex c2(4, 5);

  //  无法直接进行加法操作
  // Complex c3 = c1 + c2;  // 错误！

  return 0;
}
```

**使用运算符重载**

```cpp
class Complex {
public:
  double real;
  double imag;

  Complex(double r = 0, double i = 0) : real(r), imag(i) {}

  // 重载 + 运算符
  Complex operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
  }
};

int main() {
  Complex c1(2, 3);
  Complex c2(4, 5);

  // 现在可以使用 + 运算符进行加法操作
  Complex c3 = c1 + c2;

  cout << c3.real << " + " << c3.imag << "i" << endl;  // 输出：6 + 8i

  return 0;
}
```

**解释：** 通过重载 `+` 运算符，我们使得 `Complex` 对象可以直接进行加法运算。


---

### 2. String 类详解

**引入：** `string` 类提供了一种方便、安全、高效的方式来处理字符串。

**2.1 字符串操作函数**

| 函数        | 描述                       | 示例                              |
| ----------- | -------------------------- | --------------------------------- |
| `to_string` | 将数值转换为字符串         | `string s = to_string(123);`      |
| `isalpha`   | 判断字符是否为字母         | `bool is_alpha = isalpha('a');`   |
| `isalnum`   | 判断字符是否为字母或数字   | `bool is_alnum = isalnum('1');`   |
| `isupper`   | 判断字符是否为大写字母     | `bool is_upper = isupper('A');`   |
| `islower`   | 判断字符是否为小写字母     | `bool is_lower = islower('b');`   |
| `isprint`   | 判断字符是否为可打印字符   | `bool is_print = isprint('!');`   |
| `ispunct`   | 判断字符是否为标点符号     | `bool is_punct = ispunct('.');`   |
| `isspace`   | 判断字符是否为空白字符     | `bool is_space = isspace(' ');`   |
| `isxdigit`  | 判断字符是否为十六进制数字 | `bool is_xdigit = isxdigit('F');` |
| `isdigit`   | 判断字符是否为数字         | `bool is_digit = isdigit('5');`   |
| `iscntrl`   | 判断字符是否为控制字符     | `bool is_cntrl = iscntrl('\n');`  |


**示例：**

```cpp
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
  string str = "Hello, World! 123";

  for (char c : str) {
    if (isalpha(c)) cout << c << " is alphabetic\n";
    if (isdigit(c)) cout << c << " is a digit\n";
    if (ispunct(c)) cout << c << " is punctuation\n";
  }

  return 0;
}
```

**2.2 访问字符串元素**

| 方法    | 描述                                             | 示例                    |
| ------- | ------------------------------------------------ | ----------------------- |
| `[]`    | 通过下标访问字符串元素，越界访问会导致未定义行为 | `char c = str[0];`      |
| `at`    | 通过下标访问字符串元素，越界访问会抛出异常       | `char c = str.at(0);`   |
| `front` | 返回字符串的第一个字符                           | `char c = str.front();` |
| `back`  | 返回字符串的最后一个字符                         | `char c = str.back();`  |


**示例：**

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
  string str = "Hello, World!";

  cout << "First character: " << str[0] << endl;        // 输出：H
  cout << "First character: " << str.at(0) << endl;      // 输出：H
  cout << "Last character: " << str.back() << endl;       // 输出：!
  cout << "Second character: " << str[1] << endl;       // 输出：e
  cout << "Second character: " << str.at(1) << endl;      // 输出：e

  return 0;
}
```

---

### 3. 静态数组和动态数组

**3.1 静态数组**

* 内存位置固定，大小在编译时确定。
* 无法在运行时改变大小。

**示例：**

```cpp
int main() {
  int arr[5] = {1, 2, 3, 4, 5};

  // arr的大小固定为5，无法改变
  
  return 0;
}
```

**3.2 动态数组**

* 内存位置可以变动，大小可以在运行时改变。
* 使用 `new` 和 `delete` 运算符进行内存分配和释放。

**示例：**

```cpp
#include <iostream>

using namespace std;

int main() {
  int size;
  cout << "Enter the size of the array: ";
  cin >> size;

  // 使用 new 运算符动态分配内存
  int* arr = new int[size];

  // 使用数组
  for (int i = 0; i < size; i++) {
    arr[i] = i * 2;
  }

  // 打印数组元素
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  // 使用 delete 运算符释放内存
  delete[] arr;

  return 0;
}
```

---

### 补充：C风格字符串

* C 风格字符串是以 null 字符 `'\0'` 结尾的字符数组。
* `char* c` 本身是指向字符的指针，而不是字符串对象。
* 建议使用 `string` 类来处理字符串，因为它更安全、更方便。


**示例：**

```cpp
#include <iostream>
#include <cstring>

using namespace std;

int main() {
  char c_string[] = "Hello, World!";

  cout << c_string << endl;  // 输出：Hello, World!

  // 获取字符串长度
  int length = strlen(c_string);
  cout << "Length: " << length << endl;  // 输出：13

  return 0;
}
```

## 作业：

编写一个程序，实现以下功能：

1. 要求用户输入一个整数 `n`，表示数组的大小。
2. 动态分配一个大小为 `n` 的整型数组。
3. 要求用户输入 `n` 个整数，并将其存储到数组中。
4. 计算数组中所有元素的平均值，并输出。
5. 释放动态分配的内存。