#include "Fasade.h"
#include "../Controller/Controller.h"

using namespace s21;

void Fasade::SetRotate(float x, float y, float z) {
    Rotate(x, y, z);
    control_->SetRotateX(x);
    control_->SetRotateY(y);
    control_->SetRotateZ(z);
}

void Fasade::SetMove(float x, float y, float z) {
    Move(x, y, z);
    control_->SetMoveX(x);
    control_->SetMoveY(y);
    control_->SetMoveZ(z);
}

void Fasade::SetScale(float s) {
    Scale(s);
    control_->SetScale(s);
}

void Fasade::SetESize(int s) {
    ESize(s);
    control_->SetESize(s);
}

void Fasade::SetVSize(int s) {
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

void Fasade::SetRType(RotateType t) {
    RType(t);
    control_->SetRType((int)t);
}
