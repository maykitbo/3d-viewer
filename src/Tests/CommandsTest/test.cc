#include "test.h"

TEST_F(CommandTest, easy) {
    ALLOne();
    ALLOne();
    sleep(1);
    ALLOne();
}

TEST_F(CommandTest, many) {
    for (int k = 0; k < 1e4; ++k) {
        ALLOne();
    }
}

TEST_F(CommandTest, reset_open) {
    ALLOne();
    ALLOne();
    sleep(1);
    ALLOne();
    ALLOne();
    Reset();
    Reset();
    OpenFile();
    ALLOne();
    OpenFile();
    ALLOne();
    sleep(1);
    ALLOne();
    ALLOne();
    OpenFile();
    Reset();
}

TEST_F(CommandTest, color_select) {
    VColor(QColor(1, 2, 3));
    VColor(QColor(5, 7, 3));
    VColor(QColor(1, 8, 3));
    EndVColor(DialogButton::select, QColor(1, 8, 3));
}

TEST_F(CommandTest, color_cancel) {
    EColor(QColor(1, 2, 3));
    EColor(QColor(5, 7, 3));
    EColor(QColor(1, 8, 3));
    EndEColor(DialogButton::cancel, QColor(DefultValues::EdgesColor));
}

TEST_F(CommandTest, color) {
    EColor(QColor(9, 9, 123));
    EndEColor(DialogButton::select, QColor(9, 9, 123));
    EColor(QColor(1, 2, 3));
    EColor(QColor(5, 7, 3));
    BGColor(QColor(1, 2, 3));
    EColor(QColor(1, 8, 3));
    sleep(1);
    EColor(QColor(9, 9, 9));
    BGColor(QColor(66, 66, 66));
    EndEColor(DialogButton::cancel, QColor(9, 9, 123));
    EndBGColor(DialogButton::select, QColor(66, 66, 66));
}

TEST_F(CommandTest, undo) {
    RotateZ(5);
    MoveZ(1);
    sleep(1);
    MoveZ(-0.7);
    Undo([&] { zm_ = 1; });
    Undo([&] { zm_ = 0; });
    Undo([&] { zr_ = 0; });
    Undo([]{});
    Undo([]{});
    MouseRotateXY(-11, -1);
}

TEST_F(CommandTest, redo) {
    EColor(QColor(9, 9, 123));
    EndEColor(DialogButton::select, QColor(9, 9, 123));
    Redo([]{});
    EColor(QColor(1, 2, 3));
    sleep(1);
    EColor(QColor(5, 7, 3));
    sleep(1);
    EColor(QColor(1, 8, 3));
    EndEColor(DialogButton::select, QColor(1, 8, 3));
    Undo([&] { ec_ = QColor(9, 9, 123); });
    Undo([&] { ec_ = QColor(DefultValues::EdgesColor); });
    Undo([]{});
    Redo([&] { ec_ = QColor(9, 9, 123); });
    Redo([&] { ec_ = QColor(1, 8, 3); });
    Redo([&] { ec_ = QColor(1, 8, 3); });
}

TEST_F(CommandTest, redo_list_clean) {
    PType(central);
    Scale(1.1);
    MouseScale(2.2, 0, 0);
    RotateX(111);
    sleep(1);
    PType(parallel);
    Undo([&] { pt_ = central; });
    Undo([&] { xr_ = 0; });
    MoveY(-12);
    Redo([]{});
    Undo([&] { ym_ = 0; });
    Undo([&] { scale_ = 1.1; });
}

TEST_F(CommandTest, mouse_wheel_1) {
    MouseScale(2.2, 1, 1);
    Scale(3);
    sleep(1);
    MoveX(10);
    Undo([&] { xm_ = 1; });
    Redo([&] { xm_ = 10; });
    MouseScale(1.5, 7, -1);
    Undo([&] {
        scale_ = 3;
        xm_ = 10;
        ym_ = 1;
    });
    Undo([&] { xm_ = 1; });
    Undo([&] { scale_ = 1.0/2.2; });
    Undo([&] {
        scale_ = 1;
        xm_ = 0;
        ym_ = 0;
    });
}

TEST_F(CommandTest, mouse_wheel_2) {
    MouseScale(2.2, 1, 1);
    MouseMoveXY(4, 5);
    Undo([&] {
        xm_ = 1;
        ym_ = 1;
    });
    sleep(1);
    MouseScale(0.7, -4, -5);
    sleep(1);
    MouseScale(2.2, 2, 2);
    Undo([&] {
        scale_ *= 2.2;
        xm_ -= 2;
        ym_ -= 2;
    });
    MouseMoveXY(3, 4);
}

// TEST_F(CommandTest, over_buffer) {
//     for (int k = 0; k < 1000; k++) {
//         ALLOne();
//         sleep(1);
        
//     }
// }
