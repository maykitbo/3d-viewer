#include "Controller/Controller.h"
#include "Commands/Commands.h"

#include <thread>

using namespace s21;

template<class T>
static void th_d(const T &func) {
    // std::thread thr([&] { func(); });
    std::thread thr(func);
    thr.detach();
}

template<class T>
static void th_j(const T &func) {
    // std::thread thr([&] { func(); });
    std::thread thr(func);
    thr.join();
}

int main() {
    Controller c;
    // c.FileOpen("../objectives/cube.obj");
    // c.test();
    // c.FileOpen("../objectives/cube.obj");
    // c.FileOpen("../objectives/1.obj");
    // c.FileOpen("../objectives/cube.obj");
    // c.ObjectRotate(1, 2, 3);
    // c.ObjectMove(1, 5, -7);
    // c.FileOpen("../objectives/cube.obj");
    // c.ObjectMove(-3.3, 56, 0);
    // c.ObjectZoom(1235);
    // c.test();
    // c.ObjectRotate(3, 3, 3);
    // c.ChangeBackgroundColor(Color(1, 2, 3));
    // c.ChangeLineColor(Color(9, 9, 9));
    // c.ChangeLineType(solid);
    // c.test();
    // c.ChangeVerticesColor(Color(1, 200, 100));
    // c.ChangeVerticesType(circle);
    // c.SaveImage(jpeg);
    // c.test();
    // c.ChangeProjection(central);
    th_d([&] { c.FileOpen("../objectives/cube.obj"); });
    th_d([&] { c.FileOpen("../objectives/cube.obj"); });
    th_d([&] { c.FileOpen("../objectives/cube.obj"); });
    th_d([&] { c.test(); });

    c.test();
    return 0;
}