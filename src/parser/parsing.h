#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <string>
#include <fstream>
#include <limits>

typedef std::vector<double> v_vec;
typedef std::vector<uint> e_vec;

class Model {
    private:
        std::ifstream file;
        v_vec vertex;
        e_vec lines;
        template<class T>
        T Model::ftot() {
            T n;
            file >> T;
            return T;
        }
        void caseV();
        void caseF();
    public:
        Model() noexcept : vertex(), lines(), file() {}
        void parser(std::string fName);
        [[nodiscard]] v_vec getVertex() const noexcept { return vertex; }
        [[nodiscard]] e_vec getLines() const noexcept { return lines; }
};



#endif // PARSING_H
