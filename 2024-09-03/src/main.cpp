#include <iostream>

#if 0
int add(int a, int b) {
	return a + b;
}

int sub(int a, int b) {
	return a - b;
}
#endif

#if 0
int add(int, int);
int sub(int, int);
#endif

#include "add.hpp"
#include "sub.hpp"

int main() {
	std::cout << "add(1, 2) =" << add(1, 2) << '\n';
	std::cout << "sub(1, 2) =" << sub(1, 2) << '\n';

	return 0;
}