#include "Controller/Controller.h"
#include "Command/Command.h"

using namespace s21;

int main() {
    Controller c;
    c.FileOpen("../objectives/cube.obj");
    // c.test();
    c.FileOpen("../objectives/cube.obj");
    c.FileOpen("../objectives/1.obj");
    c.FileOpen("../objectives/cube.obj");
    c.FileOpen("../objectives/cube.obj");
    return 0;
}