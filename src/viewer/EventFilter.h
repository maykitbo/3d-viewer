#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QToolButton>
#include <QKeyEvent>
#include <QMouseEvent>

#include "../Controller/Controller.h"

namespace s21 {

class MEvent : public QObject {
    private:
        int k = 0;
        QPointF mouse_pos;
        Controller *control_;
        QToolButton *move_, *x_, *y_, *z_;
        QWidget *widget_;
        bool eventFilter(QObject *object, QEvent *event) override;
        bool KeyCase(QEvent *event);
        void MouseEvent(QEvent *event);
    public:
        MEvent() : QObject() {}
        void SetController(Controller *c) { control_ = c; }
        void SetButtons(QToolButton *move, QToolButton *x, QToolButton *y, QToolButton *z, QWidget *widget);

};

} // namespace s21

#endif // EVENTFILTER_H
