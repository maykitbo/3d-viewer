#include "EventFilter.h"

#include <iostream>

using namespace s21;

void MEvent::SetButtons(QToolButton *move, QToolButton *x, QToolButton *y, QToolButton *z, QWidget *widget) {
    move_ = move;
    x_ = x;
    y_ = y;
    z_ = z;
    widget_ = widget;
}

bool MEvent::eventFilter(QObject *object, QEvent *event) {
    // if ((*QObject)move_ == object)
    switch (event->type()) {
        case QEvent::KeyPress:
            return KeyCase(event);
        case QEvent::MouseButtonPress:
            return MousePressed(event);
        case QEvent::MouseMove:
            return MouseMove(object, event);
        case QEvent::Wheel:
            return MouseWheel(object, event);
        case QEvent::MouseButtonRelease:
            return MouseRelease(object, event);

        //     std::cout << k++ << "MouseButtonRelease\n";
        //     MouseEvent(event);
        //     return true;
        // case QEvent::MouseMove:
        //     std::cout << k++ << "MouseMove\n";
        //     MouseEvent(event);
        //     return true;
        // case QEvent::GrabMouse:
        //     std::cout << k++ << "GrabMouse\n";
        //     MouseEvent(event);
        //     return true;
        default:
            return false;
    }
    return false;
}

bool MEvent::MouseRelease(QObject *object, QEvent *event) {
    if (widget_ != object) return false;
    inertia_.Extend();
    return true;
}

bool MEvent::MouseWheel(QObject *object, QEvent *event) {
    if (widget_ != object) return false;
    control_->MouseScale(static_cast<QWheelEvent*>(event)->angleDelta().y() > 0 ?\
                        DefultValues::ScaleRatio : 1 / DefultValues::ScaleRatio);
    return true;
}

bool MEvent::MousePressed(QEvent *event) {
    mouse_pos = static_cast<QMouseEvent*>(event)->globalPosition();
    return false;
}

bool MEvent::MouseMove(QObject *object, QEvent *event) {
    if (widget_ != object) return false;
    auto event_m = static_cast<QMouseEvent*>(event);
    auto new_pos = event_m->globalPosition();
    float x = new_pos.x() - mouse_pos.x();
    float y = new_pos.y() - mouse_pos.y();
    bool move = true;
    if (event_m->modifiers() & Qt::ShiftModifier) {
        if (move_->isChecked()) move = false;
    } else {
        if (!move_->isChecked()) move = false;
    }
    if (x_->isChecked()) {
        move ? MoveX(x) : RotateX(y);
    } else if (y_->isChecked()) {
        move ? MoveY(y) : RotateY(x);
    } else if (z_->isChecked()) {
        float z = x - y;
        move ? MoveZ(z) : RotateZ(z);
    } else {
        move ? MoveXY(x, y) : RotateXY(y, x);
    }
    mouse_pos = new_pos;
    return true;
}

bool MEvent::KeyCase(QEvent *event) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() & Qt::Key_Z && keyEvent->modifiers() & Qt::ControlModifier) {
        if (keyEvent->modifiers() & Qt::ShiftModifier) {
            control_->Redo();
        } else {
            control_->Undo();
            std::cout << "UNDO   ctrl z\n";
        }
        return true;
    }
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
        default:
            return false;
    }
    return false;
}

// bool MEvent::eventFilter(QObject *object, QEvent *event) {
//     if (event->type() == QEvent::KeyPress) {
//         QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//         if (keyEvent->key() & Qt::Key_Z && keyEvent->modifiers() & Qt::ControlModifier) {
//             if (keyEvent->modifiers() & Qt::ShiftModifier) {
//                 control_->Redo();
//             } else {
//                 control_->Undo();
//                 std::cout << "UNDO   ctrl z\n";
//             }
//             return true;
//         }
//     } else if (event->type() == QEvent::MouseButtonPress) {

//     } else if (event->type() == QEvent::MouseButtonRelease) {

//     } else if (event->type() == QEvent::GrabMouse) {

//     } else if (event->type() == QEvent::MouseMove) { // add QObject == OGLWidget
//         // std::cout << "grap\n";
//         QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
//         if (mouseEvent->button() ==  Qt::NoButton) {
//             auto x = mouseEvent->screenPos().x();
//             auto y = mouseEvent->screenPos().y();
//             std::cout << (double)x << " " << (double)y << "\n";
//         }
//         // mouseEvent->button() == Qt::LeftButton
//     }
//     return false;
// }



