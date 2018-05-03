#include <iostream>

struct MyClass {
    double data;
    MyClass() : data(0.0) {}
    MyClass(const MyClass& other) : data(1.0) {}
    MyClass(MyClass&& other) : data(2.0) {}
};

int main() {
    MyClass first;
    MyClass second = first;
    MyClass third(std::move(first));
    std::cout << "first. data = " << first.data << std::endl;
    std::cout << "second.data = " << second.data << std::endl;
    std::cout << "third. data = " << third.data << std::endl;

}
