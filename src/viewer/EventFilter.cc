#include "EventFilter.h"

#include <iostream>

using namespace s21;

void MEvent::SetButtons(QToolButton *move, QToolButton *rotate, QToolButton *x, QToolButton *y, QToolButton *z, QWidget *widget) {
    rotate_ = rotate;
    move_ = move;
    x_ = x;
    y_ = y;
    z_ = z;
    widget_ = widget;
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
        case QEvent::MouseButtonRelease:
            return MouseReleaseCase(object, event);
        case QEvent::KeyRelease:
            return KeyReleaseCase(event);
        default:
            return false;
    }
    return false;
}

bool MEvent::MouseReleaseCase(QObject *object, QEvent *event) {
    if (widget_ != object) return false;
    inertia_.Extend();
    return true;
}

bool MEvent::MouseWheelCase(QObject *object, QEvent *event) {
    if (widget_ != object) return false;
    control_->MouseScale(static_cast<QWheelEvent*>(event)->angleDelta().y() > 0 ?\
                        DefultValues::ScaleRatio : 1 / DefultValues::ScaleRatio);
    return true;
}

bool MEvent::MousePressedCase(QEvent *event) {
    inertia_.Stop();
    mouse_pos = static_cast<QMouseEvent*>(event)->globalPosition();
    QRect widgetRect = widget_->geometry();
    widgetRect.moveTopLeft(widget_->parentWidget()->mapToGlobal(widgetRect.topLeft()));
    center_pos_ = widgetRect.center();
    return false;
}

bool MEvent::MouseMoveCase(QObject *object, QEvent *event) {
    if (widget_ != object) return false;
    auto new_pos = static_cast<QMouseEvent*>(event)->globalPosition();
    float x = new_pos.x() - mouse_pos.x();
    float y = new_pos.y() - mouse_pos.y();
    if (x_->isChecked())
        move_->isChecked() ? MoveX(x) : RotateX(y);
    else if (y_->isChecked())
        move_->isChecked() ? MoveY(y) : RotateY(x);
    else if (z_->isChecked())
        move_->isChecked() ? MoveZ(x, y) : RotateZ(x, y, new_pos);
    else
        move_->isChecked() ? MoveXY(x, y) : RotateXY(y, x);
    mouse_pos = new_pos;
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
    if (move_->isChecked()) rotate_->click();
    else move_->click();
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




