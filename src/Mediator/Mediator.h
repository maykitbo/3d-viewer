#ifndef MEDIATOR_MEDIATOR_H
#define MEDIATOR_MEDIATOR_H

#include "../Parser/Parser.h"
// #include "../Controller/Controller.h"
#include "../Helpers/Helpers.h"
#include <QString>

#include <iostream>

namespace s21 {

class Controller;

class Mediator {
    private:
        Parser pars_;
        Controller *control_;
        QString ClolorToString(QColor col) { return QString("background-color: %1").arg(col.name()); }
    public:
        Mediator(Controller *c) : control_(c) {}
        void Parse(std::string &file_path);
        VerticesVector getVertex() { return pars_.getVertex(); }
        EdgesVector getLines() { return pars_.getLines(); }

        void Scale(float s);

        void ESize(float s);
        void VSize(float s);
        void EType(EdgesType t);
        void VType(VerticesType t);
        void PType(Projection t);
        void RType(RotateType t);

        void Gif(double t, int fps);
        void Render(RenderType type);

        void Move(float x, float y, float z);
        void Rotate(float x, float y, float z);

        void VColor(QColor c);
        void EColor(QColor c);
        void BgColor(QColor c);

        void SetRotate(float x, float y, float z);
        void SetMove(float x, float y, float z);

        void SetScale(float s);
        void SetESize(int s);
        void SetVSize(int s);
        void SetEType(EdgesType t);
        void SetVType(VerticesType t);
        void SetPType(Projection t);
        void SetRType(RotateType t);

};

} // namespace s21

#endif // MEDIATOR_MEDIATOR_H
