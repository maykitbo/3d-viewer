#include "Mediator.h"
#include "../Controller/Controller.h"

using namespace s21;

void Mediator::SetRotate(float x, float y, float z) {
    Rotate(x, y, z);
    control_->SetRotateX(x);
    control_->SetRotateY(y);
    control_->SetRotateZ(z);
}

void Mediator::SetMove(float x, float y, float z) {
    Move(x, y, z);
    control_->SetMoveX(x);
    control_->SetMoveY(y);
    control_->SetMoveZ(z);
}

void Mediator::SetScale(float s) {
    Scale(s);
    control_->SetScale(s);
}

void Mediator::SetESize(int s) {
    ESize(s);
    control_->SetESize(s);
}

void Mediator::SetVSize(int s) {
    VSize(s);
    control_->SetVSize(s);
}

void Mediator::SetEType(EdgesType t) {
    EType(t);
    control_->SetEType((int)t);
}

void Mediator::SetVType(VerticesType t) {
    VType(t);
    control_->SetVType((int)t);
}

void Mediator::SetPType(Projection t) {
    PType(t);
    control_->SetPType((int)t);
}

void Mediator::SetRType(RotateType t) {
    RType(t);
    control_->SetRType((int)t);
}
