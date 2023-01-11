#ifndef FASADE_FASADE_H
#define FASADE_FASADE_H

#include "../Parser/Parser.h"
// #include "../Controller/Controller.h"
#include "../Helpers/Helpers.h"
#include <QString>

#include <iostream>

namespace s21 {

class Controller;

class Fasade {
    private:
        Parser pars_;
        Controller *control_;
        QString ClolorToString(QColor col) { return QString("background-color: %1").arg(col.name()); }
    public:
        Fasade(Controller *c) : control_(c) {}
        void Parse(std::string &file_path);
        VerticesVector getVertex() { return pars_.getVertex(); }
        EdgesVector getLines() { return pars_.getLines(); }
        void RotateX(double x);
        void RotateY(double y);
        void RotateZ(double z);
        void MoveX(double x);
        void MoveY(double y);
        void MoveZ(double z);
        void Scale(double s);
        void ESize(double s);
        void VSize(double s);
        void EType(EdgesType t);
        void VType(VerticesType t);
        void PType(Projection t);

        void VColor(QColor c);
        void EColor(QColor c);
        void BgColor(QColor c);

        void SetRotateZ(double z);
        void SetRotateY(double y);
        void SetRotateX(double x);
        void SetMoveX(double x);
        void SetMoveY(double y);
        void SetMoveZ(double z);
        void SetScale(double s);
        void SetESize(double s);
        void SetVSize(double s);
        void SetEType(EdgesType t);
        void SetVType(VerticesType t);
        void SetPType(Projection t);

};

} // namespace s21

#endif // FASADE_FASADE_H
