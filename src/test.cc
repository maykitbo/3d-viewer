#include "Controller/Controller.h"
#include "Command/Command.h"

using namespace s21;

int main() {
    Controller c;
    c.FileOpen("../objectives/cube.obj");
    c.test();
    c.FileOpen("../objectives/cube.obj");
    c.FileOpen("../objectives/1.obj");
    c.FileOpen("../objectives/cube.obj");
    c.ObjectRotate(1, 2, 3);
    c.ObjectMove(1, 5, -7);
    c.FileOpen("../objectives/cube.obj");
    c.ObjectMove(-3.3, 56, 0);
    c.ObjectZoom(1235);
    c.test();
    c.ObjectRotate(3, 3, 3);
    c.ChangeBackgroundColor(Color(1, 2, 3));
    c.ChangeLineColor(Color(9, 9, 9));
    c.ChangeLineType(solid);
    c.test();
    c.ChangeVerticesColor(Color(1, 200, 100));
    c.ChangeVerticesType(circle);
    c.SaveImage(jpeg);
    c.test();
    c.ChangeProjection(central);
    return 0;
}