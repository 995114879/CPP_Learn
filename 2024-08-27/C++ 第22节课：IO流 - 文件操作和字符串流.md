## C++ 第22节课：IO流 - cout 格式设置，文件操作和字符串流

**学习目标：**

* 掌握cout格式化输出方法
* 理解cin和cout缓冲区机制
* 熟练使用fstream进行文件读写操作
* 了解stringstream字符串流的应用

---

### 一、cout 格式设置

**1.1 cout 缓冲区机制**

* `cin`和`cout`都拥有缓冲区，用于临时存储输入和输出数据。
* `cout`要输出的内容会先暂存在缓冲区中，直到刷新缓冲区时才会输出到控制台。
* 刷新缓冲区的方式：
    * 遇到`endl`或`'\n'`
    * 遇到`flush`操作
    * 程序结束时自动刷新

**代码示例：**

```cpp
#include <iostream>

using namespace std;

int main() {
  cout << "Hello"; // 数据存入缓冲区，未输出
  cout << endl;    // 刷新缓冲区，输出 "Hello" 并换行

  cout << "World"; // 数据存入缓冲区，未输出
  cout.flush();     // 手动刷新缓冲区，输出 "World"

  return 0;
}
```

**1.2  iostream 类继承关系与单例模式**

* `iostream` 继承了 `istream` 和 `ostream`，实现了输入和输出功能。
* `cin` 是 `istream` 的对象，`cout` 是 `ostream` 的对象。
* **单例模式:** `iostream` 的设计遵循单例模式，无法创建第二个对象，保证了标准输入输出的唯一性。

**1.3 格式化输出**

* 使用`setw(n)`设置输出宽度，不足部分用空格填充。
* 使用`setfill(c)`设置填充字符。
* 使用`setprecision(n)`设置输出精度。
* 使用`fixed`和`scientific`设置浮点数输出格式。
* 使用`left`和`right`设置对齐方式。

**代码示例：**

```cpp
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  double pi = 3.1415926;

  cout << setw(10) << pi << endl;  // 输出宽度为 10
  cout << setfill('*') << setw(10) << pi << endl; // 用 * 填充
  cout << setprecision(3) << pi << endl;  // 保留 3 位有效数字

  cout << fixed << setprecision(2) << pi << endl; // 定点格式，保留 2 位小数
  cout << scientific << pi << endl; // 科学计数法

  cout << left << setw(10) << "Hello" << "World" << endl; // 左对齐
  cout << right << setw(10) << "Hello" << "World" << endl; // 右对齐

  return 0;
}
```
**综合示例 **

```
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    // 表格数据
    vector<vector<string>> table = {
            {"Name", "Age", "City"},
            {"Alice", "25", "New York"},
            {"Bob", "30", "London"},
            {"Charlie", "28", "Paris"}
    };

    // 计算每列最大宽度
    vector<int> columnWidths(table[0].size(), 0);
    for (const auto& row : table) {
        for (size_t i = 0; i < row.size(); ++i) {
            columnWidths[i] = max(columnWidths[i], static_cast<int>(row[i].size()));
        }
    }

    // 输出表格
    for (const auto& row : table) {
        for (size_t i = 0; i < row.size(); ++i) {
            cout << "|" << setw(columnWidths[i] + 2) << row[i];
        }
        cout << "|" << endl;

        // 输出分隔线
        if (&row == &table[0]) { // 只在表头后输出分隔线
            for (int width : columnWidths) {
                cout << "+" << setfill('-') << setw(width + 2) << "";
            }
            cout << "+" << endl;
            cout << setfill(' '); // 恢复默认填充字符
        }
    }

    return 0;
}
```

---

### 二、文件操作 - fstream

**2.1 fstream 类继承关系**

* `fstream` 继承自 `ifstream` 和 `ofstream`，实现文件读写功能。
* `ifstream` 继承了 `istream`，用于读取文件。
* `ofstream` 继承了 `ostream`，用于写入文件。
* **注意:** 文件的输入输出是相对于内存而言的，从文件读取数据到内存称为输入，将内存数据写入文件称为输出。

**2.2 文件打开模式**

* `fstream::open("PATH", openmod)` 用于打开文件。
* `in`: 读文件模式，`fstream` 和 `ifstream` 可以设置，`ofstream` 不能设置。
* `out`: 写文件模式，`fstream` 和 `ofstream` 可以设置，`ifstream` 不能设置。
* 默认模式：`ifstream` 默认 `in`，`ofstream` 默认 `out`。
* `trunc`: 截断模式，删除文件中原来的数据，必须先设置为 `out`。
* `app`: 文件末追加模式，在文件的最后写入数据。
* `ate`: 读写位置跳转到文件末尾。

**代码示例：**

```cpp
#include <iostream>
#include <fstream>

using namespace std;

int main() {
  // 写文件
  ofstream outfile("example.txt", ios::out | ios::trunc); 
  if (outfile.is_open()) {
    outfile << "Hello, world!" << endl;
    outfile.close();
  }

  // 读文件
  ifstream infile("example.txt", ios::in);
  if (infile.is_open()) {
    string line;
    while (getline(infile, line)) {
      cout << line << endl;
    }
    infile.close();
  }

  // 文件追加
  ofstream appendfile("example.txt", ios::out | ios::app);
  if (appendfile.is_open()) {
    appendfile << "This is appended text." << endl;
    appendfile.close();
  }

  return 0;
}
```

**2.3 文件指针操作**

* `seekg()`：控制输入流的文件指针位置。
* `seekp()`：控制输出流的文件指针位置。
* `ios::beg`: 文件开头。
* `ios::cur`: 文件当前位置。
* `ios::end`: 文件结尾。

**代码示例：**

```cpp
#include <iostream>
#include <fstream>

using namespace std;

int main() {
  fstream file("example.txt", ios::in | ios::out);
  if (file.is_open()) {
    // 移动到文件末尾
    file.seekg(0, ios::end);
    int length = file.tellg(); // 获取文件长度
    cout << "File length: " << length << endl;

    // 移动到文件开头
    file.seekg(0, ios::beg);
    string content;
    getline(file, content);
    cout << "First line: " << content << endl;

    file.close();
  }

  return 0;
}
```

---

### 三、字符串流 - stringstream

**3.1 stringstream 类继承关系**

* `stringstream` 用于操作字符串，可以像操作文件流一样操作字符串。
* `stringstream` 继承自 `istringstream` 和 `ostringstream`。
* `istringstream` 继承了 `istream`，用于从字符串读取数据。
* `ostringstream` 继承了 `ostream`，用于将数据写入字符串。

**3.2 stringstream 的应用**

* 数据类型转换
* 字符串拼接
* 字符串解析

**代码示例：**

```cpp
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
  // 将整数转换为字符串
  int num = 123;
  stringstream ss;
  ss << num;
  string str = ss.str();
  cout << "String: " << str << endl;

  // 将字符串转换为整数
  string str2 = "456";
  stringstream ss2(str2);
  int num2;
  ss2 >> num2;
  cout << "Integer: " << num2 << endl;

  // 字符串拼接
  stringstream ss3;
  ss3 << "Hello" << " " << "World!";
  string result = ss3.str();
  cout << "Concatenated string: " << result << endl;

  return 0;
}
```

---

### 四、作业

**题目：**

1. 读取文件中的数据（学生的成绩），根据姓名构造 `Student` 类。
2. 计算均分，并换算成 A-E 等级后，再写入另一个文件。
   * 等级划分：A[90,100] B[80,90) C[70,80) D[60,70) E[0,60)

**提示：**

* 可以使用 `fstream` 读取和写入文件。
* 可以使用 `stringstream` 辅助字符串解析和数据类型转换。

**下面是参考代码 :**

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Student {
public:
    string name;
    int chinese;
    int math;
    int english;
    char grade;

    Student(string name, int chinese, int math, int english) :
        name(name), chinese(chinese), math(math), english(english) {
        calculateGrade();
    }

    void calculateGrade() {
        double average = (chinese + math + english) / 3.
        if (average >= 90) {
            grade = 'A';
        } else if (average >= 80) {
            grade = 'B';
        } else if (average >= 70) {
            grade = 'C';
        } else if (average >= 60) {
            grade = 'D';
        } else {
            grade = 'E';
        }
    }
};

int main() {
    // 读取学生成绩数据
    ifstream inputFile("student_scores.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    vector<Student> students;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name;
        int chinese, math, english;
        ss >> name >> chinese >> math >> english;
        students.push_back(Student(name, chinese, math, english));
    }
    inputFile.close();

    // 写入学生成绩和等级
    ofstream outputFile("student_grades.txt");
    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

    for (const Student& student : students) {
        outputFile << student.name << " " << student.chinese << " " 
                   << student.math << " " << student.english << " " 
                   << student.grade << endl;
    }
    outputFile.close();

    cout << "Grades calculated and written to student_grades.txt" << endl;

    return 0;
}
```


**作业要求:**

* 创建两个文件 `student_scores.txt` 和 `student_grades.txt`。
* 在 `student_scores.txt` 中输入学生成绩数据，格式为：`姓名 语文 数学 英语`，每行一个学生。
* 运行程序后，`student_grades.txt` 中将包含学生的成绩和对应的等级。

---

**总结：**

本节课学习了 `cout` 格式化输出、`fstream` 文件操作和 `stringstream` 字符串流。这些知识点在实际开发中非常常用，请同学们认真练习，掌握这些技能。


大家加油！