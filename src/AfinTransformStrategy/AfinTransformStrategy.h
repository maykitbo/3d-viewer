#ifndef VIEWER_AFIN_TRANSFORM_STRATEGY_H
#define VIEWER_AFIN_TRANSFORM_STRATEGY_H

#include <cmath>
#include <QMatrix4x4>
#include <QVector4D>
#include <QOpenGLWidget>

#include "../Helpers/Helpers.h"

namespace s21 {

class AfinTransformStrategy {
 private:
  QMatrix4x4 move_matrix_;
  QMatrix4x4 rotate_matrix_;
  QMatrix4x4 zoom_matrix_;
  QMatrix4x4 projection_matrix_;
  int width_;
  int heigth_;
  Projection projection_type_;

  void SetProjection();

 public:
  AfinTransformStrategy();
  
  void SetMove(double x, double y, double z) noexcept;
  void SetRotate(double x_r, double y_r, double z_r);
  void SetZoom(double zoom);
  void ChangeProjection(Projection type);
  void ChangeScreenSize(int width, int heigth);
  void ResetMatrix();

  QMatrix4x4 GetMatrix();
    
};

}  // namespace s21



#endif  // VIEWER_AFIN_TRANSFORM_STRATEGY_H