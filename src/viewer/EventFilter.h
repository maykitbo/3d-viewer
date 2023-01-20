#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QToolButton>
#include <QKeyEvent>
#include <QMouseEvent>
// #include <QSpinBox>
// #include <QDoubleSpinBox>
#include <QWheelEvent>
#include <chrono>
#include <functional>

#include "../Controller/Controller.h"

namespace s21 {

class Momentum {
    private:
        using Time = std::chrono::_V2::system_clock::time_point;
        Time Now() { return std::chrono::high_resolution_clock::now(); }
        Time time_ = Now();
        //  delta_;
        std::function<void(float)> act_;
        void Acceleration() {
        //     std::chrono::duration_cast<std::chrono::milliseconds>(time_ - last_time).count()
        //     // if (delta_ > Now() - time_) block_ = true;
        //     // else block_ = false;
        //     // delta_ = Now() - time_;
        //     // time_ = Now();
        }
        bool block_ = false;
    public:
        Momentum() {}
        template<class F>
        void Action(const F &act) {
            act(1.0);
            Acceleration();
            // auto buff = act_;
            act_ = act;
            // std::cout << "act == act " << (act_ == buff) << "\n";
            // if (act != act_) {
            //     act_ = act;
            //     UpTime();
            //     return;
            // }
        }
        void Extend() {
            
        }
        void Stop() { block_ = true; }

};

class MEvent : public QObject {
    private:
        Momentum inertia_;
        int k = 0;
        QPointF mouse_pos;
        Controller *control_;
        QToolButton *move_, *x_, *y_, *z_;
        QWidget *widget_;
        bool eventFilter(QObject *object, QEvent *event) override;
        bool KeyCase(QEvent *event);
        bool MouseMove(QObject *object, QEvent *event);
        void MoveX(float x) { control_->MouseMoveX(DefultValues::MoveRatio * x); }
        void MoveY(float y) { control_->MouseMoveY(-1 * DefultValues::MoveRatio * y); }
        void MoveZ(float z) { control_->MouseMoveY(DefultValues::MoveRatio * z); }
        void MoveXY(float x, float y) { control_->MouseMoveXY(DefultValues::MoveRatio * x, -1 * DefultValues::MoveRatio * y); }
        void RotateX(float x) { inertia_.Action([&](float k){control_->MouseRotateX(DefultValues::RotateRatio * x * k);}); }
        void RotateY(float y) { control_->MouseRotateY(-1 * DefultValues::RotateRatio * y); }
        void RotateZ(float z) { control_->MouseRotateY(DefultValues::RotateRatio * z); }
        void RotateXY(float x, float y) { control_->MouseRotateXY(DefultValues::RotateRatio * x, -1 * DefultValues::RotateRatio * y); }
        bool MousePressed(QEvent *event);
        bool MouseWheel(QObject *object, QEvent *event);
        bool MouseRelease(QObject *object, QEvent *event);
    public:
        MEvent() : QObject() {}
        MEvent(Controller *c) : QObject(), control_(c) {}
        // void SetController(Controller *c) { control_ = c; }
        void SetButtons(QToolButton *move, QToolButton *x, QToolButton *y, QToolButton *z, QWidget *widget);

};

} // namespace s21

#endif // EVENTFILTER_H
