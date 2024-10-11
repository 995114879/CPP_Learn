#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
//    int pi{314159267};
//    double pi2 = 314159267;
//    std::cout << pi << '\n';
//    std::cout << std::setfill('*') << std::setw(12) << pi << '\n';
//    std::cout << std::setprecision(3) << pi2 << '\n';
    double pi = 3.1415926;

//    cout << setw(11) << pi << endl;  // 输出宽度为 10
//    cout << setfill('*') << setw(11) << pi << endl; // 用 * 填充
//    cout << setw(11) << setprecision(10) << pi << endl;  // 保留 3 位有效数字
//    cout << fixed << setprecision(2) << pi << endl; // 定点格式，保留 2 位小数
//    cout << scientific << pi << endl; // 科学计数法
//    cout << setfill('*') << left << setw(10) << "Hello" << "World" << endl; // 左对齐
//    cout << setfill('*') << right << setw(10) << "Hello" << "World" << endl; // 右对齐

// 表格数据
#if 0
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
#endif

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