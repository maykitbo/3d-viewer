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
#include <chrono>
#include <functional>
#include <math.h>
// #include <thread>

#include "../Controller/Controller.h"
// #include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace s21 {

class Momentum {
    private:
        using Time = decltype((std::chrono::high_resolution_clock::now)());
        Time Now() { return std::chrono::high_resolution_clock::now(); }
        Time time_ = Now();
        int64_t delta_ = 21;
        std::function<void(float)> act_;
        bool block_ = false;
    public:
        Momentum() {}
        template<class F>
        void Action(const F &act) {
            act(1.0);
            delta_ = std::chrono::duration_cast<std::chrono::milliseconds>(Now() - time_).count();
            // std::cout << "Action delta = " << delta_ << "\n";
            time_ = Now();
            act_ = act;
            block_ = false;
        }
        void Extend() {
            // std::cout << "Extend delta = " << delta_ << "\n";
            if (delta_ < 20) {
                // double del = 20.0 / (double)delta_;
                // std::thread thr([&](){
                //     while (!block_ && del > 0) {
                //         std::cout << del << " delta\n";
                //         act_(1.0);
                //         // std::this_thread::sleep_for(std::chrono::milliseconds(100));
                //         del -= 0.05;
                //     }
                // });
                // thr.detach();
                // std::cout << "MOMENTUM WORK\n";
            }
        }
        void Stop() { block_ = true; }

};

// class MainWindow;

class MEvent : public QObject {
    private:
        Momentum inertia_;
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
        void MoveX(qreal x) { control_->MouseMoveX(move_ratio_ * (float)x); }
        void MoveY(qreal y) { control_->MouseMoveY(-1 * move_ratio_ * (float)y); }
        void MoveZ(qreal x, qreal y) { control_->MouseMoveZ(move_ratio_ * (float)(x - y)); }
        void MoveXY(qreal x, qreal y) { control_->MouseMoveXY(move_ratio_ * (float)x, -1 * move_ratio_ * (float)y); }
        // void RotateX(qreal x) { inertia_.Action([&](float k){control_->MouseRotateX(DefultValues::RotateRatio * x * k);}); }
        void RotateX(qreal x) { control_->MouseRotateX(DefultValues::RotateRatio * (float)x); }
        void RotateY(qreal y) { control_->MouseRotateY(-1 * DefultValues::RotateRatio * (float)y); }
        float CosAngleVV(QPointF a, QPointF b) const {
            return (a.x()*b.x() + a.y()*b.y()) / std::sqrt((a.x()*a.x() + a.y()*a.y()) * (b.x()*b.x() + b.y()*b.y()));
        }
        void RotateZ(QPointF new_pos) {
            QPointF p(mouse_pos_ - center_pos_);
            int znak = mouse_pos_.y() > center_pos_.y() ? -1 : 1;
            control_->MouseRotateZ(std::acos(CosAngleVV(p, QPointF(new_pos - center_pos_))) * (180 / M_PI) *\
                (CosAngleVV(QPointF(new_pos - mouse_pos_), znak * QPointF(1, - p.x() / p.y())) > 0 ? -1 : 1));
        }
        void RotateXY(qreal x, qreal y) { control_->MouseRotateXY(DefultValues::RotateRatio * (float)x, -1 * DefultValues::RotateRatio * (float)y); }
        bool MousePressedCase(QEvent *event);
        bool MouseWheelCase(QObject *object, QEvent *event);
        bool MouseReleaseCase(QObject *object, QEvent *event);
        bool KeyZCase(QKeyEvent *keyEvent);
        bool KeyReleaseCase(QEvent *event);
        bool KeyShiftCase(QKeyEvent *keyEvent);
        void ChangeButtons();
    public:
        MEvent() : QObject() {}
        MEvent(Controller *c) : QObject(), control_(c) {}
        void SetButtons(Ui::MainWindow *ui);

};

} // namespace s21

#endif // EVENTFILTER_H
