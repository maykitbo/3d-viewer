#include "ShaderStrategy.h"

s21::ShaderStrategy::ShaderStrategy() {
  const char *vertexShaderSource =
    "attribute vec3 position;\n"
    "uniform mat4 coeffMatrix;\n"
    "void main()\n"
    "{\n"
    "gl_Position = coeffMatrix * vec4(position.x, position.y, "
    "position.z, "
    "1.0);\n"
    "}\0";

  const char *fragmentShaderSource =
    "uniform vec3 color;\n"
    "void main()\n"
    "{\n"
    "gl_FragColor = vec4(color.x, color.y, color.z, 1);\n"
    "}\n\0";

  prog_ = new QOpenGLShaderProgram;

  prog_->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  prog_->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                  fragmentShaderSource);

  prog_->bindAttributeLocation("position", 0);
  prog_->link();
  prog_->bind();

  coeff_address_ = prog_->uniformLocation("coeffMatrix");
  color_address_ = prog_->uniformLocation("color");

}

s21::ShaderStrategy::ShaderStrategy(std::vector<double> verticles, std::vector<uint> edges) : ShaderStrategy() {
  initialize_vbo(verticles);    // надо ли создавать vbo только 1 раз?
  initialize_ibo(edges);        // надо ли создавать ibo только 1 раз?
}

s21::ShaderStrategy::~ShaderStrategy() {
  delete prog_;
}

void s21::ShaderStrategy::initialize_vbo(std::vector<double> verticles) {
  QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
  vbo.create();
  vbo.bind();
  vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo.allocate(verticles.data(), verticles.size() * 3 * sizeof(float));

  prog_->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
  prog_->enableAttributeArray(0);
}

void s21::ShaderStrategy::initialize_ibo(std::vector<uint> edges) {
  QOpenGLBuffer ibo(QOpenGLBuffer::IndexBuffer);  
  ibo.create();
  ibo.bind();
  ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
  ibo.allocate(edges.data(), sizeof(unsigned int) * 2 * edges.size());
}

void s21::ShaderStrategy::set_color(Color color) {
  prog_->setUniformValue(color_address_, "color");
} 

void s21::ShaderStrategy::set_coeff(QMatrix4x4 coeffMatrix) {
  prog_->setUniformValue(coeff_address_, coeffMatrix);
}
