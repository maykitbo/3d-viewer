#include <iostream>
#include <list>
#include <memory>
#include <type_traits>

class basic1 {
    public:
        void foo() { std::cout << "basic1\n"; }
};

class basic2 {
    public:
        void foo() { std::cout << "basic2\n"; }
};

class Parant {
    public:
        virtual void foo() = 0;
};

class A : public Parant {
    public:
        void foo() override { std::cout << "A(PARANT)\n"; }
};

class B : public Parant {
    public:
        void foo() override { std::cout << "B(PARANT)\n"; }
};

//typename std::enable_if<std::is_base_of<Parant, C>::value>::type

// template<class C>
// template<typename std::enable_if<std::is_base_of<Parant, C>::value, C>::type>
// class test {
//     public:
//         void fo(C com) {
//             std::cout << "SPEC: ";
//             com.foo();
//         }
// };


template<class C>
class test {
    public:
        void fo(C com) {
            std::cout << std::is_base_of<Parant, C>::value << "  \n";
            com.foo();
        }
};

// template<class C> C test<C>::val;




int main() {
    std::cout << std::is_base_of<Parant, A>::value << "\n";
    

    return 0;
}
