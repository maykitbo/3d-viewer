#include "parsing.h"

#include <iostream>


int main() {
    Model A;

    time_t time = clock();
    A.parser("objectives/Controller.obj");
    double sec = double(clock() - time) / CLOCKS_PER_SEC;
    std::cout << sec << " " << A.getVertex().size() << " " << A.getLines().size() << "\n";

    // for (auto i : A.getVertex()) {
    //     std::cout << i.x << " " << i.y << " " << i.z << "\n";
    // }
    // std::cout << "----\n";
    // for (auto i : A.getLines()) {
    //     for (auto j : i) {
    //         std::cout << j->x << " " << j->y << " " << j->z << "  ++  ";
    //     }
    //     std::cout << "\n";
    // }
    return 0;
}
