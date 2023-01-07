
#include <iostream>
#include <functional>

class A {
    private:
        double a = 1.1;
    public:
        void F(double d) {
            std::cout << a << " " << d << "\n";
        }
};

// template<class T>
void G(std::function<void(double)> func) {
    func(2.2);
}

int main() {
    A aa;
    G(std::bind(&A::F, aa, std::placeholders::_1));
    return 0;
}