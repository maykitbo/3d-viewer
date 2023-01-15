#include <iostream>
#include <list>
#include <memory>
#include <type_traits>





class A {
    protected:
        int h = 0;
    public:
        A(int g) : h(g) {}
};

class B : public A {
    public:
        B(int y) : A(y) {}
        void foo() { std::cout << h << "\n"; }
};





int main() {
    B h(5);
    h.foo();

    return 0;
}
