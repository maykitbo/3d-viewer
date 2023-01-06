#include <iostream>

template<class... Types>
struct Tuple {};


int main() {
    Tuple<> t0;
    Tuple<int> t1;
    Tuple<int, float> t2;
    
    return 0;
}
