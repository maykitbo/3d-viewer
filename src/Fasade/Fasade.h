#ifndef FASADE_FASADE_H
#define FASADE_FASADE_H

#include <string>

#include "../Parser/Parser.h"
#include "../OGLWidget/OGLWidget.h"
#include "../Helpers/Helpers.h"

namespace s21
{

  class Fasade {
  private:
    Parser *Parser;
    OGLWidget *Widget;

  public:
    void OpenFile(std::string &file_path);
    void MoveObject(float x, float y, float z);
    void RotateObject(float x, float y, float z);
    void ScaleObject(float scale);
    void SetProjection(Projection type);
    void SetLineType(EdgesType type);
    void SetLineColor(QColor color);
    void SetPointType(VerticesType type);
    void SetPointColor(QColor color);
    void SetBgColor(QColor color);
    void SaveImage(RenderType type);
  };

} // namespace s21

#endif // FASADE_FASADE_H
