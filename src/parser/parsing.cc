
#include "parsing.h"

#include <iostream>

void Model::parser(std::string fName) {
    file.open(fName);
    while (file) {
        switch (file.get()) {
            case 'v':
                caseV();
                break;
            case 'f':
                caseF();
                break;
            // case 'g': --------------------------------------------------------  add g
            default:
                file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }
    file.close();
}

void Model::caseV() {
    if (file.peek() == ' ') {
        for (int k = 0; k < 3; ++k) {
            vertex.push_back(ftot<double>());
        }
        // ----------------------------------------------------------------------  add [w]
    } else { //  ----------------------------------------------------------------  add vn vb
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

void Model::caseF() {
    // lines.push_back(f_1_vec());
    while (file.peek() != '\n' && file) {
        if (file.peek() == ' ') lines.push_back(ftot<uint>());
        else file.ignore();  //  ------------------------------------------------  add f 1//2//3
    }
    file.ignore();
}


