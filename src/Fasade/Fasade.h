#ifndef FASADE_FASADE_H
#define FASADE_FASADE_H

#include "../Parser/Parser.h"

namespace s21 {

class Fasade {
    private:
        Parser pars_;
    public:
        void Parse(std::string &file_path);
};

} // namespace s21

#endif // FASADE_FASADE_H
