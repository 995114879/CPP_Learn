#include <iostream>
#include <string>

struct Animal {
     virtual void speak() {
        std::cout << "Animal must be speeking" << '\n';
    }
};

struct Cat : public Animal {
    virtual void speak() override {
        std::cout << "speeking with Meow...." << '\n';
    }
};

struct Dog : public Animal {
    virtual void speak() override {
        std::cout << "speeking with wang..." << '\n';
    }
};

void make_animal_speak(Animal* arr[], int num) {
    for (auto i = 0; i < num; i++) {
        arr[i]->speak();
    }
}



int main() {
//    Animal* pa1 = new Animal;
//    Animal* pa2 = new Animal;

//    Animal* arr[2] = {new Cat , new Dog};
//    make_animal_speak(arr, 2);
    Animal* pcat = new Cat;
    pcat->speak();
    Animal& rcat = *pcat;
    rcat.speak();

    return 0;
}