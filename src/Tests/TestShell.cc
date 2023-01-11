#include <chrono>
#include <iostream>

#include "../Commands/Commands.h"
#include "../Parser/Parser.h"
#include "../Helpers/Helpers.h"

using namespace std::chrono;

class s21::Fasade {
    private:
        s21::Parser pars_;
    public:
        Fasade() : pars_() {}
        void Parse(std::string &file_path) { pars_.parse(file_path); }
        // VerticesVector getVertex() { return pars_.getVertex(); }
        // EdgesVector getLines() { return pars_.getLines(); }
        void RotateX(double x) {}
        void RotateY(double y) {}
        void RotateZ(double z) {}
        void MoveX(double x) {}
        void MoveY(double y) {}
        void MoveZ(double z) {}
        void Scale(double s) {}
        void ESize(double s) {}
        void VSize(double s) {}
        void EType(s21::EdgesType t) {}
        void VType(s21::VerticesType t) {}
        void PType(s21::Projection t) {}

        void SetRotateZ(double z) {}
        void SetRotateY(double y) {}
        void SetRotateX(double x) {}
        void SetMoveX(double x) {}
        void SetMoveY(double y) {}
        void SetMoveZ(double z) {}
        void SetScale(double s) {}
        void SetESize(double s) {}
        void SetVSize(double s) {}
        void SetEType(s21::EdgesType t) {}
        void SetVType(s21::VerticesType t) {}
        void SetPType(s21::Projection t) {}

};

void test_p() {
  auto start = high_resolution_clock::now();
  s21::Shell sh;
  s21::Fasade fs;
  sh.AddFasade(&fs);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << duration.count() << " ms\n";
}

int main() {
  test_p();
}
