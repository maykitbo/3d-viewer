#ifndef PARSING_H
#define PARSING_H

// #include <vector>
#include <string>
#include <fstream>
#include <limits>

#include "../Helpers/Helpers.h"

namespace s21 {

class Parser {
    private:
        std::ifstream file_;
        VerticesVector vertex_;
        EdgesVector lines_;
        template<class T>
        T ftot() {
            T n;
            file_ >> n;
            return n;
        }
        void caseV();
        void caseF();
    public:
        // Parser() noexcept : vertex_(), lines_(), file_() {}
        void parse(std::string &fName);
        [[nodiscard]] VerticesVector getVertex() const noexcept { return vertex_; }
        [[nodiscard]] EdgesVector getLines() const noexcept { return lines_; }
        void clear();
};

} // namespace s21



#endif // PARSING_H
