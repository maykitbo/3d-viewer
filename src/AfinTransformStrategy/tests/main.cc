#include "AfinTransformStrategy.h"
#include "../s21_matrix/s21_matrix.h"
#include <iostream>


int main() {
    s21::AfinTransformStrategy afin;
    // afin.SetRotate(90,90,90);
    afin.SetMove(5,0,0);
    QMatrix4x4 t = afin.GetMatrix();
    QVector4D point(1,1,1,1);
    QVector4D out = t.map(point);
    std::cout << out.x() << std::endl;
    std::cout << out.y() << std::endl;
    std::cout << out.z() << std::endl;

    return 0;
}
