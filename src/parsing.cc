
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
        Point Pp;
        file >> Pp.x;
        file >> Pp.y;
        file >> Pp.z;
        vertex.push_back(Pp);
        // ----------------------------------------------------------------------  add [w]
    } else { //  ----------------------------------------------------------------  add vn vb
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

void Model::caseF() {
    lines.push_back(f_1_vec());
    while (file.peek() != '\n' && file) {
        if (file.peek() == ' ') lines.back().push_back(&(vertex[ftoi() - 1]));
        else file.ignore();  //  ------------------------------------------------  add f 1//2//3
    }
    file.ignore();
}


uint Model::ftoi() {
    uint n;
    file >> n;
    return n;
}
