#include "EventFilter.h"

#include <iostream>

using namespace s21;

void MEvent::SetButtons(Ui::MainWindow *ui) {
    ui_ = ui;
}

bool MEvent::eventFilter(QObject *object, QEvent *event) {
    switch (event->type()) {
        case QEvent::KeyPress:
            return KeyPressCase(event);
        case QEvent::MouseButtonPress:
            return MousePressedCase(event);
        case QEvent::MouseMove:
            return MouseMoveCase(object, event);
        case QEvent::Wheel:
            return MouseWheelCase(object, event);
        case QEvent::KeyRelease:
            return KeyReleaseCase(event);
        case QEvent::Resize:
            return ResizeCase();
        case QEvent::Move:
            return MoveCase();
        default:
            return false;
    }
    return false;
}

bool MEvent::MoveCase() {
    QRect widgetRect = ui_->widget->geometry();
    widgetRect.moveTopLeft(ui_->widget->parentWidget()->mapToGlobal(widgetRect.topLeft()));
    center_pos_ = widgetRect.center();
    return false;
}

bool MEvent::ResizeCase() {
    QRect widgetRect = ui_->widget->geometry();
    auto h = widgetRect.height();
    auto w = widgetRect.width();
    move_ratio_ = 3.0 / (w < h ? w : h);
    return false;
}

bool MEvent::MouseWheelCase(QObject *object, QEvent *event) {
    if (ui_->widget != object) return false;
    auto wheel_event = static_cast<QWheelEvent*>(event);
    auto point = wheel_event->globalPosition() - ModelCenter();
    float scale = wheel_event->angleDelta().y() > 0 ? DefultValues::ScaleRatio : 1 / DefultValues::ScaleRatio;
    QPointF m_c_point = (point - (point / (scale)));
    control_->MouseScale(scale, move_ratio_ * m_c_point.x(), -1 * move_ratio_ * m_c_point.y());
    return true;
}

bool MEvent::MousePressedCase(QEvent *event) {
    mouse_pos_ = static_cast<QMouseEvent*>(event)->globalPosition();
    return false;
}


bool MEvent::MouseMoveCase(QObject *object, QEvent *event) {
    if (ui_->widget != object) return false;
    auto new_pos = static_cast<QMouseEvent*>(event)->globalPosition();
    qreal x = new_pos.x() - mouse_pos_.x();
    qreal y = new_pos.y() - mouse_pos_.y();
    if (ui_->xMouseButton->isChecked())
        ui_->handButton->isChecked() ? MoveX(x) : RotateX(y);
    else if (ui_->yMouseButton->isChecked())
        ui_->handButton->isChecked() ? MoveY(y) : RotateY(x);
    else if (ui_->zMouseButton->isChecked())
        ui_->handButton->isChecked() ? MoveZ(x, y) : RotateZ(new_pos);
    else
        ui_->handButton->isChecked() ? MoveXY(x, y) : RotateXY(y, x);
    mouse_pos_ = new_pos;
    return true;
}

bool MEvent::KeyPressCase(QEvent *event) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (changed_) ChangeButtons();
    switch (keyEvent->key()) {
        case Qt::Key_Up:
            control_->MouseMoveZ(1);
            return true;
        case Qt::Key_Down:
            control_->MouseMoveZ(-1);
            return true;
        case Qt::Key_Left:
            control_->MouseMoveX(-1);
            return true;
        case Qt::Key_Right:
            control_->MouseMoveX(1);
            return true;
        case Qt::Key_Z:
            return KeyZCase(keyEvent);
        case Qt::Key_Shift:
            return KeyShiftCase(keyEvent);
        default:
            return false;
    }
    return false;
}

bool MEvent::KeyShiftCase(QKeyEvent *keyEvent) {
    if (keyEvent->key() ^ Qt::Key_Shift || keyEvent->modifiers() ^ Qt::ShiftModifier) {
        return false;
    }
    ChangeButtons();
    return true;
}

void MEvent::ChangeButtons() {
    changed_ = !changed_;
    if (ui_->handButton->isChecked()) ui_->rotateMouseButton->click();
    else ui_->handButton->click();
}

bool MEvent::KeyReleaseCase(QEvent *event) {
    if (changed_ && static_cast<QKeyEvent*>(event)->key() & Qt::Key_Shift)
        ChangeButtons();
    return false;
}

bool MEvent::KeyZCase(QKeyEvent *keyEvent) {
    if (keyEvent->modifiers() & Qt::ControlModifier) {
        if (keyEvent->modifiers() & Qt::ShiftModifier)
            control_->Redo();
        else
            control_->Undo();
        return true;
    }
    return false;
}

void MEvent::RotateZ(QPointF new_pos) {
    QPointF center = ui_->rotateBox->currentIndex() == balance ? ModelCenter() : center_pos_;
    QPointF p(mouse_pos_ - center);
    int znak = mouse_pos_.y() > center.y() ? -1 : 1;
    control_->MouseRotateZ(std::acos(CosAngleVV(p, QPointF(new_pos - center))) * (180 / M_PI) *\
        (CosAngleVV(QPointF(new_pos - mouse_pos_), znak * QPointF(1, - p.x() / p.y())) > 0 ? -1 : 1));
}

void MEvent::RotateXY(qreal x, qreal y) {
    control_->MouseRotateXY(DefultValues::RotateRatio * (float)x, -1 * DefultValues::RotateRatio * (float)y);
}

void MEvent::MoveX(qreal x) {
    control_->MouseMoveX(move_ratio_ * (float)x);
}

void MEvent::MoveY(qreal y) {
    control_->MouseMoveY(-1 * move_ratio_ * (float)y);
}

void MEvent::MoveZ(qreal x, qreal y) {
    control_->MouseMoveZ(move_ratio_ * (float)(x - y));
}

void MEvent::MoveXY(qreal x, qreal y) {
    control_->MouseMoveXY(move_ratio_ * (float)x, -1 * move_ratio_ * (float)y);
}

void MEvent::RotateX(qreal x) {
    control_->MouseRotateX(DefultValues::RotateRatio * (float)x);
}

void MEvent::RotateY(qreal y) {
    control_->MouseRotateY(-1 * DefultValues::RotateRatio * (float)y);
}

QPointF MEvent::ModelCenter() const {
    return center_pos_ + QPointF(ui_->moveXSpin->value() / move_ratio_, -1 * ui_->moveYSpin->value() / move_ratio_);
}

float MEvent::CosAngleVV(QPointF a, QPointF b) const {
    return (a.x()*b.x() + a.y()*b.y()) / std::sqrt((a.x()*a.x() + a.y()*a.y()) * (b.x()*b.x() + b.y()*b.y()));
}




