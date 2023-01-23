#ifndef PARSING_H
#define PARSING_H

// #include <vector>
// #include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <math.h>

// #include "../Helpers/Helpers.h"

namespace s21 {

typedef std::vector<float> VerticesVector;
typedef std::vector<uint> EdgesVector;

class Parser {
    private:
        std::ifstream file_;
        VerticesVector vertex_;
        EdgesVector lines_;
        uint vertex_i_, lines_i_;
        float max_ = 0;
        void caseV();
        void caseF();
    public:
        // Parser() noexcept : vertex_(), lines_(), file_() {}
        void parse(std::string &fName);
        [[nodiscard]] VerticesVector getVertex() const noexcept { return vertex_; }
        [[nodiscard]] EdgesVector getLines() const noexcept { return lines_; }
        [[nodiscard]] uint GetLinesIndex() const noexcept { return lines_i_; }
        [[nodiscard]] uint GetVertexIndex() const noexcept { return vertex_i_; }
        [[nodiscard]] float GetMaxValue() const noexcept { return max_; }
        void clear();
};

} // namespace s21



#endif // PARSING_H
