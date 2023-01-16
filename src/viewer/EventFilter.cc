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
    switch (event->type()) {
        case QEvent::KeyPress:
            // std::cout << k++ << "KeyPressed\n";
            return KeyCase(event);
        case QEvent::MouseButtonPress:
            // QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            mouse_pos = static_cast<QMouseEvent*>(event)->position();
            return true;
        case QEvent::MouseMove:
            // std::cout << k++ << "MouseButtonPress\n";
            if(object == widget_) MouseEvent(event);
            else return false;
            return true;
        // case QEvent::MouseButtonRelease:
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

void MEvent::MouseEvent(QEvent *event) {
    // std::cout << k++ << "MouseMove\n";
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if (!mouseEvent->isBeginEvent()) { 
    //     mouse_pos = mouseEvent->position();
    // } else {
        if (x_->isChecked()) {
            float x = mouseEvent->position().x() - mouse_pos.x();
            move_->isChecked() ? control_->MouseMoveX(x) : control_->MouseRotateX(x);
        } else if (y_->isChecked()) {
            float y = (mouseEvent->position().x() + mouseEvent->position().y()) - (mouse_pos.x() + mouse_pos.y());
            move_->isChecked() ? control_->MouseMoveX(y) : control_->MouseRotateX(y);
        } else if (z_->isChecked()) {
            float z = mouseEvent->position().x() - mouse_pos.x();
            move_->isChecked() ? control_->MouseMoveX(z) : control_->MouseRotateX(z);
        } else {
            
            float x = mouseEvent->position().x() - mouse_pos.x();
            float z = mouseEvent->position().y() - mouse_pos.y();
            std::cout << x << " " << z << " mouse pos\n";
            move_->isChecked() ? control_->MouseMoveXZ(x, z) : control_->MouseRotateXZ(x, z);
        }
    }
    mouse_pos = mouseEvent->position();
    // std::cout << "begin event: " << mouseEvent->isBeginEvent() << " // end event: " << mouseEvent->isEndEvent() << "\n";
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



