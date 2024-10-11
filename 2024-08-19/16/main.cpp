#include <iostream>
#include <numeric>
#include <vector>
#include <list>
#include <map>
#include <set>

int main() {
    /*
    int n;
    std::cout << "input the number of ints: " << '\n';
    std::cin >> n;

    int* p = new int[n];
    if (p != nullptr) { // 这一步是必须要有的，因为真实的场景中申请内存存在不成功的情况
        for (auto i = 0; i < n; ++i) {
            std::cin >> p[i];
        }
    } else {

    }

    auto result = std::accumulate(p, p+n, 0.0);
    auto final_result = result / n;
    std::cout << "final_result = " << final_result << '\n';
     */

    /*
    std::string a{"abc"}; // 二进制安全
    std::string b{"def"};
    auto result = a + b;
     */
    std::vector<int> vint{1,2,3};
    std::cout << "size = " <<  vint.size() << '\n';
    std::cout << "cap = " << vint.capacity() << '\n';
    vint.push_back(4);
    std::cout << "size = " <<  vint.size() << '\n';
    std::cout << "cap = " << vint.capacity() << '\n';

    std::cout << vint[0] << '\n';
    std::cout << vint[1] << '\n';
    std::cout << vint[2] << '\n';
    std::cout << vint[3] << '\n';
    std::cout << vint[4] << '\n';

    std::vector<std::vector<int>> vint2{{1,2,3}, {4,5,6}};

    std::cout << vint2[1][1] << std::endl;

    for (const auto& e: vint2[0])  { // for (auto i = 0; i < n; ++i) {}
        std::cout << e << " ";
    }
    std::cout << '\n';

    for (auto& e: vint2[1])  {
        std::cout << e << " ";
    }
    std::cout << '\n';

    std::list<int> numbers = {1, 2, 3, 4, 5};

    numbers.push_back(6);
    numbers.push_front(0);
    numbers.insert(numbers.begin(), 9);
    numbers.insert(numbers.begin(), 9);

    std::cout << "Elements in list: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
//////////////////////////////
    std::map<int, std::string> student_map;

    // 插入元素
    student_map[101] = "Alice";
    student_map[102] = "Bob";
    student_map[103] = "Charlie";
    student_map[999] = "abc";
   // student_map.insert({999, "def"});
    student_map[999] = "def";



    // 遍历 map
    std::cout << "Student IDs and names:" << std::endl;
    for (const auto& pair : student_map) {
        std::cout << "ID: " << pair.first << ", Name: " << pair.second << std::endl;
    }

    // 查找元素
    int id_to_find = 102;
    auto it = student_map.find(id_to_find);
    if (it != student_map.end()) {
        std::cout << "Student with ID " << id_to_find << " is " << it->second << std::endl;
    } else {
        std::cout << "Student with ID " << id_to_find << " not found." << std::endl;
    }

    std::set<int> unique_numbers = {10, 20, 30, 20, 40, 10};

    std::cout << "Elements in set: ";
    for (int num : unique_numbers) {
        std::cout << num << " ";  // 输出 10 20 30 40，自动去重和排序
    }
    std::cout << std::endl;

    // 查找元素
    if (unique_numbers.find(20) != unique_numbers.end()) {
        std::cout << "20 is found in the set." << std::endl;
    } else {
        std::cout << "20 is not found in the set." << std::endl;
    }


    return 0;
}
