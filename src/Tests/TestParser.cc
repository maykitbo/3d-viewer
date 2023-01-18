#include <chrono>
#include <iostream>

#include "../Parser/Parser.h"

using namespace std::chrono;

static void test_p(std::string str) {
  auto start = high_resolution_clock::now();
  s21::Parser P;
  P.parse(str);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << str << ": " << duration.count() << " ms\n";
}

int main() {
  test_p("../../objectives/Controller.obj");
}

