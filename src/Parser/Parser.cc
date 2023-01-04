
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
    file_.close();
}

void Parser::caseV() {
    if (file_.peek() == ' ') {
        for (int k = 0; k < 3; ++k) {
            vertex_.push_back(ftot<double>());
        }
        // ----------------------------------------------------------------------  add [w]
    } else { //  ----------------------------------------------------------------  add vn vb
        file_.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

void Parser::caseF() {
    // lines.push_back(f_1_vec());
    while (file_.peek() != '\n' && file_) {
        if (file_.peek() == ' ') lines_.push_back(ftot<uint>());
        else file_.ignore();  //  ------------------------------------------------  add f 1//2//3
    }
    file_.ignore();
}

void Parser::clear() {
    vertex_.clear();
    lines_.clear();
}


