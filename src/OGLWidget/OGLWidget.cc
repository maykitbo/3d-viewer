#include "OGLWidget.h"

s21::OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    this->setFocusPolicy(Qt::StrongFocus);
}

s21::OGLWidget::~OGLWidget() {
  delete Afin;
}

void s21::OGLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  initialize_shaders();
  set_addresses();
  Afin = new AfinTransformStrategy;

  add_example_vectors();
}

void s21::OGLWidget::resizeGL(int w, int h) {
  Afin->ChangeScreenSize(w,h);
}

void s21::OGLWidget::paintGL() {
  glClearColor(0,0,0,1);
  prog->bind();
  QMatrix4x4 MnojMatrix = Afin->GetMatrix();
  prog->setUniformValue(coeff_address, MnojMatrix);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  vao.bind();
  prog->setUniformValue(color_address, lineColor);
  glDrawElementsBaseVertex(GL_LINES, 12Projection type, GL_UNSIGNED_INT,0,0);
  vao.release();
}

void s21::OGLWidget::set_coeff_matrix(QMatrix4x4 matrix) {
  prog->setUniformValue(coeff_address, matrix);
}

void s21::OGLWidget::set_buffers(VerticesVector vertex_array, EdgesVector lines_array ) {

  if (vao.isCreated()) vao.destroy();

  vao.create();
  vao.bind();

  QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
  vbo.create();
  vbo.bind();
  vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  vbo.allocate(vertex_array.data(), vertex_array.size() * sizeof(float));

  prog->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
  prog->enableAttributeArray(0);

  QOpenGLBuffer ibo(QOpenGLBuffer::IndexBuffer);
  ibo.create();
  ibo.bind();
  ibo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  lines_count_ = lines_array.size();
  ibo.allocate(lines_array.data(), sizeof(unsigned int) * lines_count_);

  vao.release();
}



void s21::OGLWidget::initialize_shaders() {
  const char *vertexShaderSource =
      "attribute vec3 position;\n"
      "uniform mat4 coeffMatrix;\n"
      "void main()\n"
      "{\n"
      "gl_Position = coeffMatrix * vec4(position, 1.0);\n"
      "}\0";

  const char *fragmentShaderSource =
      "uniform vec3 color;\n"
      "void main()\n"
      "{\n"
      "gl_FragColor = vec4(color.x, color.y, color.z, 1);\n"
      "}\n\0";

    prog = new QOpenGLShaderProgram;
    prog->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    prog->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                  fragmentShaderSource);
    prog->bindAttributeLocation("position", 0);
    prog->link();
    
}

void s21::OGLWidget::set_addresses() {
  coeff_address = prog->uniformLocation("coeffMatrix");
  color_address = prog->uniformLocation("color");
}



void s21::OGLWidget::add_example_vectors() {
  VerticesVector verts{-0.5,0,-0.5,0.5,0,-0.5,0,0.5,-0.5,0,-0.5,-1};
  EdgesVector lines{0, 1, 1, 2, 2, 0, 0, 3, 1, 3, 2, 3};
  set_buffers(verts, lines);
}

void s21::OGLWidget::rotate_object(float x, float y, float z) {
  Afin->SetRotate(x,y,z);
  update();
}

void s21::OGLWidget::move_object(float x, float y, float z) {
  Afin->SetMove(x,y,z);
  update();
}

void s21::OGLWidget::zoom_object(float zoom) {
  Afin->SetZoom(zoom);
  update();
}

void s21::OGLWidget::change_perspective(Projection type) {
  Afin->ChangeProjection(type);
  update();
}

