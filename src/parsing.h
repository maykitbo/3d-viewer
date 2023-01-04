#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <string>
#include <fstream>
#include <limits>

struct Point {
    double x, y, z; // ----------------- add [w]
    Point() noexcept : x(0), y(0), z(0) {}
    template <class T>
    Point(double x_, double y_, double z_) noexcept : x(x_), y(y_), z(z_) {}
};

typedef std::vector<double> v_vec;
typedef std::vector<Point*> f_1_vec;
typedef std::vector<f_1_vec> f_vec;

class Model {
    private:
        std::ifstream file;
        v_vec vertex;
        f_vec lines;
        uint ftoi();
        void caseV();
        void caseF();
    public:
        Model() noexcept : vertex(), lines(), file() {}
        void parser(std::string fName);
        [[nodiscard]] v_vec getVertex() const noexcept { return vertex; }
        [[nodiscard]] f_vec getLines() const noexcept { return lines; }
};



#endif // PARSING_H
