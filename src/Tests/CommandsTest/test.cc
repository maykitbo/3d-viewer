#include "test.h"



TEST_F(CommandTest, rotate_test) {
    control_.RotateX(5);
    xr_ += 5;
    TestEq();
}

TEST_F(CommandTest, move_test) {
    for (int k = 9; k < 40; ++k) {
        control_.MouseMoveX(-2);
        xm_ -= 2;
    }
    TestEq();
}

TEST_F(CommandTest, move_rotate_test_1) {
    for (int k = 9; k < 4000; ++k) {
        control_.MouseRotateX(-2);
        control_.MouseMoveZ(0.1);
        control_.RotateY(k);
        zm_ += 0.1;
        xr_ -= 2;
        yr_ = k;
    }
    TestEq();
}

TEST_F(CommandTest, move_rotate_test_2) {
    for (int k = 0; k < 1e5; ++k) {
        control_.MouseMoveX(-1);
        control_.MouseMoveX(1);
        control_.MouseMoveY(-5);
        control_.MouseMoveY(5);
        control_.MouseMoveZ(1.11);
        control_.MouseMoveZ(-1.11);
        control_.RotateX(-7);
        control_.RotateY(-11);
        control_.RotateZ(0.005);
    }
    xr_ = -7;
    yr_ = -11;
    zr_ = 0.005;
    TestEq();
}

