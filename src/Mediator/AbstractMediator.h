#ifndef MEDIATOR_ABSTRACTMEDIATOR_H
#define MEDIATOR_ABSTRACTMEDIATOR_H

// #include "../Parser/Parser.h"
#include "../Helpers/Helpers.h"
#include <QString>


namespace s21 {

// class Controller;

class AbstractMediator {
    protected:
        QString ClolorToString(QColor col) { return QString("background-color: %1").arg(col.name()); }
        float RotateCool(float x) {
            while (x < 0) x += 360.0;
            return std::fmod(x, 360);
            // if (x < 0) x += 360.0;
        }
    public:
        AbstractMediator() {}
        virtual void Parse(std::string &file_path) = 0;
        virtual void Scale(float s) = 0;
        virtual void ESize(int s) = 0;
        virtual void VSize(int s) = 0;
        virtual void EType(EdgesType t) = 0;
        virtual void VType(VerticesType t) = 0;
        virtual void PType(Projection t) = 0;
        virtual void RType(RotateType t) = 0;
        virtual void Gif(double t, int fps) = 0;
        virtual void Render(RenderType type) = 0;
        virtual void Move(float x, float y, float z) = 0;
        virtual void VColor(QColor c) = 0;
        virtual void EColor(QColor c) = 0;
        virtual void BgColor(QColor c) = 0;
        virtual void SetRotate(float x, float y, float z) = 0;
        virtual void SetMove(float x, float y, float z) = 0;
        virtual void SetScale(float s) = 0;
        virtual void SetESize(int s) = 0;
        virtual void SetVSize(int s) = 0;
        virtual void SetEType(EdgesType t) = 0;
        virtual void SetVType(VerticesType t) = 0;
        virtual void SetPType(Projection t) = 0;
        virtual void SetRType(RotateType t) = 0;

};

} // namespace s21

#endif // MEDIATOR_ABSTRACTMEDIATOR_H

