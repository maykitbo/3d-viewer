#ifndef MEDIATOR_MEDIATOR_H
#define MEDIATOR_MEDIATOR_H

#include "AbstractMediator.h"
#include "../Helpers/Helpers.h"
#include <QString>
#include <math.h>
#include <functional>

#include <iostream>

namespace s21 {

template<class Controller, class Fasade>
class Mediator : public AbstractMediator {
    private:
        Controller *control_;
        Fasade *fasade_;
    public:
        Mediator(Controller *c, Fasade *f) : control_(c), fasade_(f) {}
        void Parse(std::string &file_path) override {
            fasade_->OpenFile(file_path);
        }
        void Move(float x, float y, float z) override {
             fasade_->MoveObject(x, y, z);
        }
        void Scale(float s) override {
            fasade_->ScaleObject(s);
        }
        void ESize(int s) override {
            fasade_->SetLineSize(s);
        }
        void VSize(int s) override {
            fasade_->SetPointSize(s);
        }
        void EType(EdgesType t) override {
            fasade_->SetLineType(t);
        }
        void VType(VerticesType t) override {
            fasade_->SetPointType(t);
        }
        void PType(Projection t) override {
            fasade_->SetProjection(t);
        }
        void RType(RotateType t) override {
            // fasade_->SetRotateType(t);
        }
        void VColor(QColor c) override {
            fasade_->SetPointColor(c);
            control_->SetVColor(ClolorToString(c));
        }
        void EColor(QColor c) override {
            fasade_->SetLineColor(c);
            control_->SetEColor(ClolorToString(c));
        }
        void BgColor(QColor c) override {
            fasade_->SetBgColor(c);
            control_->SetBgColor(ClolorToString(c));
        }
        void Gif(double t, int fps) override {
            fasade_->SaveGif(t, fps, std::function<void(void)>([&]{ control_->ChangeVisible(); }));
        }
        void Render(RenderType type) override {
            control_->ChangeVisible();
            fasade_->SaveImage(type);
            // control_->ChangeVisible();
        }
        void SetRotate(float x, float y, float z) override {
            x = RotateCool(x);
            y = RotateCool(y);
            z = RotateCool(z);
            fasade_->RotateObject(x, y, z);
            control_->SetRotateX(x);
            control_->SetRotateY(y);
            control_->SetRotateZ(z);
        }
        void SetMove(float x, float y, float z) override {
            Move(x, y, z);
            control_->SetMoveX(x);
            control_->SetMoveY(y);
            control_->SetMoveZ(z);
        }
        void SetScale(float s) override {
            Scale(s);
            control_->SetScale(s);
        }
        void SetESize(int s) override {
            ESize(s);
            control_->SetESize(s);
        }
        void SetVSize(int s) override {
            VSize(s);
            control_->SetVSize(s);
        }
        void SetEType(EdgesType t) override {
            EType(t);
            control_->SetEType((int)t);
        }
        void SetVType(VerticesType t) override {
            VType(t);
            control_->SetVType((int)t);
        }
        void SetPType(Projection t) override {
            PType(t);
            control_->SetPType((int)t);
        }
        void SetRType(RotateType t) override {
            RType(t);
            control_->SetRType((int)t);
        }

};

} // namespace s21

#endif // MEDIATOR_MEDIATOR_H
