#ifndef FASADE_FASADE_H
#define FASADE_FASADE_H

#include <string>

#include "../Parser/Parser.h"
#include "../OGLWidget/OGLWidget.h"
#include "../Helpers/Helpers.h"

namespace s21
{

  class BackFasade {
  private:
    Parser *Parser_;
    OGLWidget *Widget_;

  public:
    BackFasade();
    BackFasade(Parser *parser, OGLWidget* widget);

    ~BackFasade();

    void OpenFile(std::string &file_path);
    void MoveObject(float x, float y, float z);
    void RotateObject(float x, float y, float z);
    void ScaleObject(float scale);
    void SetProjection(Projection type);
    void SetLineType(EdgesType type);
    void SetLineSize(int size);
    void SetLineColor(QColor color);
    void SetPointType(VerticesType type);
    void SetPointColor(QColor color);
    void SetPointSize(int size);
    void SetBgColor(QColor color);
    void SaveImage(RenderType type);
    OGLWidget GiveWidget();
  };

} // namespace s21

#endif // FASADE_FASADE_H
