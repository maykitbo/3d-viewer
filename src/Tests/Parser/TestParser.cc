#include <chrono>
#include <iostream>

#include <gtest/gtest.h>

#include "../../Parser/Parser.h"

typedef std::vector<float> VerticesVector;
typedef std::vector<uint> EdgesVector;

// namespace s21 {
using namespace s21;

class CommandTest : public ::testing::Test {
  private:
    s21::Parser pars_;
  public:
    void F_T(std::string path, VerticesVector v, EdgesVector e) {
      pars_.parse(path);
      auto v_p = pars_.getVertex();
      auto e_p = pars_.getLines();
      for (uint k = 0; k < v.size(); ++k) {
        ASSERT_FLOAT_EQ(v_p[k], v[k]);
      }
      for (uint k = 1; k < e.size() - 1; ++k) {
        ASSERT_FLOAT_EQ(e_p[k], e[k]);
      }
    }
    void Print() {
      std::cout << "vartices: ";
      for (auto i : pars_.getVertex()) {
        std::cout << i << " ";
      }
      std::cout << "\n";
      std::cout << "lines: ";
      for (auto i : pars_.getLines()) {
        std::cout << i << " ";
      }
      std::cout << "\n";
    }
};

TEST_F(CommandTest, cube) {
    VerticesVector v_cube{0.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
    EdgesVector e_cube{0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3, 2, 2, 0 ,0 ,1 ,1, 3, 3, 2, 2, 7, 7, 6, 6, 2, 2, 3, 3, 7, 7, 4, 4, 6, 6, 7, 7, 4, 4, 7, 7, 5, 5, 0, 0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 1, 1, 5, 5, 7, 7, 1, 1, 7, 7, 3};
    F_T("../../objectives/cube.obj", v_cube, e_cube);
    Print();
}

// using namespace std::chrono;

// static void test_p(std::string str) {
//   auto start = high_resolution_clock::now();
//   s21::Parser P;
//   P.parse(str);
//   auto stop = high_resolution_clock::now();
//   auto duration = duration_cast<microseconds>(stop - start);
//   std::cout << str << ": " << duration.count() << " ms\n";
// }

// int main() {
//   test_p("../../objectives/Controller.obj");
// }

