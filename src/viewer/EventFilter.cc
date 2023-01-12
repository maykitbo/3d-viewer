#include "EventFilter.h"

using namespace s21;

void MEvent::SetButtons(QToolButton *move, QToolButton *rotate,\
            QToolButton *xyz, QToolButton *x, QToolButton *y, QToolButton *z) {
    move_ = move;
    rotate_ = rotate;
    xyz_ = xyz;
    x_ = x;
    y_ = y;
    z_ = z;
}

bool MEvent::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() & Qt::Key_Z && keyEvent->modifiers() & Qt::ControlModifier) {
            if (keyEvent->modifiers() & Qt::ShiftModifier)
                control_->Redo();
            else
                control_->Undo();
            return true;
        }
    } else if (event->type() == QEvent::MouseMove) { // add QObject == OGLWidget
        // std::cout << "grap\n";
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() ==  Qt::NoButton) {
            auto x = mouseEvent->screenPos().x();
            auto y = mouseEvent->screenPos().y();
            std::cout << (double)x << " " << (double)y << "\n";
        }
        // mouseEvent->button() == Qt::LeftButton
    }
    return false;
}



