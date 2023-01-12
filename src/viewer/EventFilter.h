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
        Controller *control_;
        QToolButton *move_, *rotate_, *xyz_, *x_, *y_, *z_;
        bool eventFilter(QObject *object, QEvent *event) override;
    public:
        MEvent() : QObject() {}
        void SetController(Controller *c) { control_ = c; }
        void SetButtons(QToolButton *move, QToolButton *rotate,\
            QToolButton *xyz, QToolButton *x, QToolButton *y, QToolButton *z);

};

} // namespace s21

#endif // EVENTFILTER_H
