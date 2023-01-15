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

  set_default_settings();
  add_example_vectors();

}

void s21::OGLWidget::resizeGL(int w, int h) {
  Afin->ChangeScreenSize(w,h);
}

void s21::OGLWidget::paintGL() {
  if (vao.isCreated()) {
    glClearColor(bg_color_.redF(), bg_color_.greenF(), bg_color_.blueF(), 1);

    prog->bind();
    
    // Afin->SetMove(3,0,0);

    QMatrix4x4 MnojMatrix = Afin->GetMatrix();
    prog->setUniformValue(coeff_address, MnojMatrix);

    vao.bind();

    glClear(GL_COLOR_BUFFER_BIT);

    draw_edges();
    draw_vertices();

    vao.release();
  }
}

void s21::OGLWidget::draw_edges() {
  if (edges_type_ == dashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 0x00FF);
  }

  glLineWidth(edges_size_);
  prog->setUniformValue(color_address, edges_color_);
  glDrawElementsBaseVertex(GL_LINES, 12, GL_UNSIGNED_INT,0,0);

  if (edges_type_ == dashed) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void s21::OGLWidget::draw_vertices() {
  if (vertices_type_ != none) {
    prog->setUniformValue(color_address, vertices_color_);
    glPointSize(vertices_size_);
    if (vertices_type_ == circle)
      glEnable(GL_POINT_SMOOTH);
    glDrawArraysInstancedARB(GL_POINTS, 0, vertices_count_,1);
    if (vertices_type_ == circle)
      glDisable(GL_POINT_SMOOTH);
  }
}


void s21::OGLWidget::set_coeff_matrix(QMatrix4x4 matrix) {
  prog->setUniformValue(coeff_address, matrix);
}

void s21::OGLWidget::set_buffers(VerticesVector vertex_array, EdgesVector lines_array) {

  if (vao.isCreated()) vao.destroy();

  vao.create();
  vao.bind();

  QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
  vbo.create();
  vbo.bind();
  vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  vertices_count_ = vertex_array.size();
  vbo.allocate(vertex_array.data(), vertices_count_ * sizeof(float));

  prog->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
  prog->enableAttributeArray(0);

  QOpenGLBuffer ibo(QOpenGLBuffer::IndexBuffer);
  ibo.create();
  ibo.bind();
  ibo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  lines_count_ = lines_array.size();
  ibo.allocate(lines_array.data(), lines_count_ * sizeof(uint));

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
      "uniform vec4 color;\n"
      "void main()\n"
      "{\n"
      "gl_FragColor = color;\n"
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
  VerticesVector verts{-0.5, 0,    -0.5,
                        0.5, 0,    -0.5,
                        0,   0.5,  -0.5,
                        0,   -0.5, -1};

  EdgesVector lines{0, 1,
                    1, 2,
                    2, 0,
                    0, 3,
                    1, 3,
                    2, 3};
  set_buffers(verts, lines);
}

void s21::OGLWidget::change_vertices_type(VerticesType type) {
  vertices_type_ = type;
  update();
}

void s21::OGLWidget::change_vertices_color(QColor color) {
  vertices_color_ = color;
  update();
}

void s21::OGLWidget::change_verticles_size(int size) {
  vertices_size_ = size;
  update();
}

void s21::OGLWidget::change_line_type(EdgesType type) {
  edges_type_ = type;
  update();
}

void s21::OGLWidget::change_line_color(QColor color) {
  edges_color_ = color;
  update();
}

void s21::OGLWidget::change_line_size(int size) {
  edges_size_ = size;
  update();
}

void s21::OGLWidget::change_bg_color(QColor color) {
  edges_color_ = color;
  update();
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

void s21::OGLWidget::change_projection(Projection type) {
  Afin->ChangeProjection(type);
  update();
}

void s21::OGLWidget::set_default_settings() {
  bg_color_.setRgbF(1,1,1,1);
  edges_color_.setRgbF(1,0,0,1);
  vertices_color_.setRgbF(0,0,1,1);
  vertices_type_ = circle;
  edges_type_ = solid;
  vertices_size_ = 10;
  edges_size_ = 10;
}

void s21::OGLWidget::reset_matrix() {
  Afin->ResetMatrix();
  update();
}

void s21::OGLWidget::set_object(VerticesVector vertex_array, EdgesVector lines_array) {
  set_buffers(vertex_array, lines_array);
  update();
}

void s21::OGLWidget::save_image(RenderType type) {
  QString format;
  if (type == jpeg) {
    format = "*.jpg";
  } else if (type == bmp) {
    format = "*.bmp";
  } else {
    return;
  }
  QString save_file_path =
    QFileDialog::getSaveFileName(0, "Сохранить файл как", "", format);

  if (!save_file_path.isEmpty()) {
    grab().save(save_file_path);
  }
}
