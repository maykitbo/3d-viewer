#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QToolButton>
#include <QKeyEvent>
#include <QMouseEvent>
// #include <QSpinBox>
// #include <QDoubleSpinBox>
#include <QWheelEvent>
#include <QRect>
#include <math.h>
// #include <thread>

#include "../Controller/Controller.h"
// #include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace s21 {

class MEvent : public QObject {
        qreal move_ratio_;
        bool changed_ = false;
        QPointF mouse_pos_;
        QPointF center_pos_;
        Controller *control_;
        Ui::MainWindow *ui_;
        QWidget *widget_;
        bool eventFilter(QObject *object, QEvent *event) override;
        bool ResizeCase();
        bool KeyPressCase(QEvent *event);
        bool MouseMoveCase(QObject *object, QEvent *event);
        void MoveX(qreal x);
        void MoveY(qreal y);
        void MoveZ(qreal x, qreal y);
        void MoveXY(qreal x, qreal y);
        void RotateX(qreal x);
        void RotateY(qreal y);
        QPointF ModelCenter() const;
        float CosAngleVV(QPointF a, QPointF b) const;
        void RotateZ(QPointF new_pos);
        void RotateXY(qreal x, qreal y);
        bool MousePressedCase(QEvent *event);
        bool MouseWheelCase(QObject *object, QEvent *event);
        // bool MouseReleaseCase(QObject *object, QEvent *event);
        bool KeyZCase(QKeyEvent *keyEvent);
        bool KeyReleaseCase(QEvent *event);
        bool KeyShiftCase(QKeyEvent *keyEvent);
        bool MoveCase();
        void ChangeButtons();
    public:
        MEvent() : QObject() {}
        MEvent(Controller *c) : QObject(), control_(c) {}
        void SetButtons(Ui::MainWindow *ui);

};

} // namespace s21

#endif // EVENTFILTER_H
