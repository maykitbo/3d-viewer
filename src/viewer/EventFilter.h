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
// #include <math.h>
#include <thread>

#include "../Controller/Controller.h"

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
            std::cout << "Action delta = " << delta_ << "\n";
            time_ = Now();
            act_ = act;
            block_ = false;
        }
        void Extend() {
            std::cout << "Extend delta = " << delta_ << "\n";
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
                std::cout << "MOMENTUM WORK\n";
            }
        }
        void Stop() { block_ = true; }

};

class MEvent : public QObject {
    private:
        Momentum inertia_;
        int k = 0;
        bool changed_ = false;
        QPointF mouse_pos;
        QPointF center_pos_;
        Controller *control_;
        QToolButton *rotate_, *move_, *x_, *y_, *z_;
        QWidget *widget_;
        bool eventFilter(QObject *object, QEvent *event) override;
        bool KeyPressCase(QEvent *event);
        bool MouseMoveCase(QObject *object, QEvent *event);
        void MoveX(float x) { control_->MouseMoveX(DefultValues::MoveRatio * x); }
        void MoveY(float y) { control_->MouseMoveY(-1 * DefultValues::MoveRatio * y); }
        void MoveZ(float x, float y) { control_->MouseMoveZ(DefultValues::MoveRatio * (x - y)); }
        void MoveXY(float x, float y) { control_->MouseMoveXY(DefultValues::MoveRatio * x, -1 * DefultValues::MoveRatio * y); }
        void RotateX(float x) { inertia_.Action([&](float k){control_->MouseRotateX(DefultValues::RotateRatio * x * k);}); }
        void RotateY(float y) { control_->MouseRotateY(-1 * DefultValues::RotateRatio * y); }
        void RotateZ(float x, float y, QPointF new_pos) {
            float otn = (new_pos.x() - center_pos_.x()) / (new_pos.y() - center_pos_.y());
            float z = -(x - y * otn) / std::sqrt(1 + otn*otn);
            control_->MouseRotateZ(DefultValues::RotateRatio * z);
        }
        void RotateXY(float x, float y) { control_->MouseRotateXY(DefultValues::RotateRatio * x, -1 * DefultValues::RotateRatio * y); }
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
        // void SetController(Controller *c) { control_ = c; }
        void SetButtons(QToolButton *move, QToolButton *rotate, QToolButton *x, QToolButton *y, QToolButton *z, QWidget *widget);

};

} // namespace s21

#endif // EVENTFILTER_H
