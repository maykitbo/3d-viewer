
#include "Parser.h"

#include <iostream>

using namespace s21;

void Parser::parse(std::string &fName) {
    clear();
    file_.open(fName);
    while (file_) {
        switch (file_.get()) {
            case 'v':
                caseV();
                break;
            case 'f':
                caseF();
                break;
            // case 'g': --------------------------------------------------------  add g
            default:
                file_.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }
    vertex_.resize(vertex_i_);
    lines_.resize(lines_i_-1);
    file_.close();
}

void Parser::caseV() {
    if (file_.peek() == ' ') {
        for (int k = 0; k < 3; ++k) {
            file_ >> vertex_[vertex_i_];
            ++vertex_i_;
            if (!(vertex_i_ % 1000)) vertex_.resize(vertex_i_ + 1001);
        }
        // ----------------------------------------------------------------------  add [w]
    } else { //  ----------------------------------------------------------------  add vn vb
        file_.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

void Parser::caseF() {
    // lines.push_back(f_1_vec());
    while (file_.peek() != '\n' && file_) {
        if (file_.peek() == ' ') {
            file_ >> lines_[lines_i_];
            lines_[lines_i_]--;
            if (lines_i_ % 2) {
                ++lines_i_;
                lines_[lines_i_] = lines_[lines_i_ - 1];
            }
            // lines_[lines_i_]--;
            ++lines_i_;
            if (!(lines_i_ % 1000)) lines_.resize(lines_i_ + 1001);
        }
        // if (file_.peek() == ' ') file_ >> *lines_.emplace_back(1);
        else file_.ignore();  //  ------------------------------------------------  add f 1//2//3
    }
    file_.ignore();
}

inline void Parser::clear() {
    vertex_.clear();
    lines_.clear();
    vertex_.resize(1001);
    lines_.resize(1001);
    vertex_i_ = 0, lines_i_ = 0;
}


