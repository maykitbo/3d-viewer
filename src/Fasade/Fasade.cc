#include "Fasade.h"

#include <iostream>

using namespace s21;

void Fasade::Parse(std::string &file_path) {
    pars_.parse(file_path);

// действия после парсинга

    std::cout << pars_.getVertex().size() << "\n";
    for (auto i : pars_.getVertex()) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::cout << pars_.getLines().size() << "\n";
    for (auto i : pars_.getLines()) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}