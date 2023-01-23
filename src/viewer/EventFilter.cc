#include "EventFilter.h"

#include <iostream>

using namespace s21;

void MEvent::SetButtons(Ui::MainWindow *ui) {
    // rotate_ = rotate;
    // move_ = move;
    // scale_ = scale;
    // x_ = x;
    // y_ = y;
    // z_ = z;
    // widget_ = widget;
    ui_ = ui;
}

// ui_->handButton, ui->rotateMouseButton, ui->xMouseButton, ui_->yMouseButton, ui->zMouseButton, ui->widget, ui_->scaleSpin

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
        case QEvent::Resize:
            return ResizeCase();
        default:
            return false;
    }
    return false;
}

bool MEvent::ResizeCase() {
    auto h = ui_->widget->geometry().height();
    auto w = ui_->widget->geometry().width();
    move_ratio_ = ui_->scaleSpin->value() * 3 / (w > h ? h : w);
    // std::cout << w << " " << h << " " << move_ratio_ << " width height move_ratio\n";
    return false;
}

bool MEvent::MouseReleaseCase(QObject *object, QEvent *event) {
    if (ui_->widget != object) return false;
    inertia_.Extend();
    return true;
}

bool MEvent::MouseWheelCase(QObject *object, QEvent *event) {
    if (ui_->widget != object) return false;
    control_->MouseScale(static_cast<QWheelEvent*>(event)->angleDelta().y() > 0 ?\
                        DefultValues::ScaleRatio : 1 / DefultValues::ScaleRatio);
    return true;
}

bool MEvent::MousePressedCase(QEvent *event) {
    inertia_.Stop();
    mouse_pos = static_cast<QMouseEvent*>(event)->globalPosition();
    QRect widgetRect = ui_->widget->geometry();
    widgetRect.moveTopLeft(ui_->widget->parentWidget()->mapToGlobal(widgetRect.topLeft()));
    center_pos_ = widgetRect.center();
    return false;
}

bool MEvent::MouseMoveCase(QObject *object, QEvent *event) {
    if (ui_->widget != object) return false;
    auto new_pos = static_cast<QMouseEvent*>(event)->globalPosition();
    qreal x = new_pos.x() - mouse_pos.x();
    qreal y = new_pos.y() - mouse_pos.y();
    if (ui_->xMouseButton->isChecked())
        ui_->handButton->isChecked() ? MoveX(x) : RotateX(y);
    else if (ui_->yMouseButton->isChecked())
        ui_->handButton->isChecked() ? MoveY(y) : RotateY(x);
    else if (ui_->zMouseButton->isChecked())
        ui_->handButton->isChecked() ? MoveZ(x, y) : RotateZ(x, y, new_pos);
    else
        ui_->handButton->isChecked() ? MoveXY(x, y) : RotateXY(y, x);
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




