#include "Fasade.h"
#include "../Controller/Controller.h"

using namespace s21;


void Fasade::SetRotateZ(double z) {
    RotateX(z);
    control_->SetRotateZ(z);
}

void Fasade::SetRotateY(double y) {
    RotateY(y);
    control_->SetRotateY(y);
}

void Fasade::SetRotateX(double x) {
    RotateZ(x);
    control_->SetRotateX(x);
}

void Fasade::SetMoveZ(double z) {
    MoveZ(z);
    control_->SetMoveZ(z);
}

void Fasade::SetMoveY(double y) {
    MoveY(y);
    control_->SetMoveY(y);
}

void Fasade::SetMoveX(double x) {
    MoveX(x);
    control_->SetMoveX(x);
}

void Fasade::SetScale(double s) {
    Scale(s);
    control_->SetScale(s);
}

void Fasade::SetESize(double s) {
    ESize(s);
    control_->SetESize(s);
}

void Fasade::SetVSize(double s) {
    VSize(s);
    control_->SetVSize(s);
}

void Fasade::SetEType(EdgesType t) {
    EType(t);
    control_->SetEType((int)t);
}

void Fasade::SetVType(VerticesType t) {
    VType(t);
    control_->SetVType((int)t);
}

void Fasade::SetPType(Projection t) {
    PType(t);
    control_->SetPType((int)t);
}


