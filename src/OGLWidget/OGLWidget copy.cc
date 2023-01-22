#include "OGLWidget.h"

#include "Error.h"

 
// using namespace std;
 

s21::OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent), vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer) {
    this->setFocusPolicy(Qt::StrongFocus);
    Afin = new AfinTransformStrategy;
}

s21::OGLWidget::~OGLWidget() {
  delete Afin;
}

void s21::OGLWidget::initializeGL() {
  // std::cout << "initializeGL\n";
  glEnable(GL_DEPTH_TEST);
  initialize_shaders();
  set_addresses();

  // set_default_settings();
  add_example_vectors();

}

void s21::OGLWidget::resizeGL(int w, int h) {
  Afin->ChangeScreenSize(w,h);
}

void s21::OGLWidget::paintGL() {
  // add_example_vectors();
  set_buffers();
  if (vao.isCreated()) {
    glClearColor(bg_color_.redF(), bg_color_.greenF(), bg_color_.blueF(), 1);
    check_gl_error();

    prog->bind();
    check_gl_error();

    QMatrix4x4 MnojMatrix = Afin->GetMatrix();
    check_gl_error();

    prog->setUniformValue(coeff_address, MnojMatrix);
    check_gl_error();
    // std::cout << vao.isCreated() << " vao.bind()\n";
    vao.bind();
    check_gl_error();

    glClear(GL_COLOR_BUFFER_BIT);
    check_gl_error();

    draw_edges();
    check_gl_error();
    draw_vertices();
    check_gl_error();

    vao.release();
    check_gl_error();
  }
}

void s21::OGLWidget::draw_edges() {
  check_gl_error();
  // std::cout << "draw_edges\n";
  if (edges_type_ == dashed) {
    glEnable(GL_LINE_STIPPLE);
    check_gl_error();
    glLineStipple(3, 0x00FF);
    check_gl_error();
  }
  check_gl_error();

  glLineWidth(edges_size_);
  prog->setUniformValue(color_address, edges_color_);
  check_gl_error();
  // glDrawElementsBaseVertex(GL_LINES, lines_count_, GL_UNSIGNED_INT,0,0);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  check_gl_error();
  // std::cout << ibo.size() << "   {}   " << lines_count_ << "\n";
  glDrawElements(GL_LINES, (GLsizei)lines_count_, GL_UNSIGNED_INT,0);
  // std::cout << ibo.size() << "   {}   " << lines_count_ << "\n";
  check_gl_error();

  if (edges_type_ == dashed) {
    glDisable(GL_LINE_STIPPLE);
    check_gl_error();
  }
}

void s21::OGLWidget::draw_vertices() {
  // std::cout << "draw_vertices\n";
  if (vertices_type_ != none) {
    prog->setUniformValue(color_address, vertices_color_);
    check_gl_error();
    glPointSize(vertices_size_);
    check_gl_error();
    if (vertices_type_ == circle)
      glEnable(GL_POINT_SMOOTH);
      check_gl_error();
    // glDrawArraysInstancedARB(GL_POINTS, 0, vertices_count_,1);
    glDrawArrays(GL_POINTS, 0, vertices_count_/3);
    check_gl_error();
    if (vertices_type_ == circle)
      glDisable(GL_POINT_SMOOTH);
      check_gl_error();
  }
}


void s21::OGLWidget::set_coeff_matrix(QMatrix4x4 matrix) {
  prog->setUniformValue(coeff_address, matrix);
}

void s21::OGLWidget::set_buffers() {
  // std::cout << "set buffers\n";
  if (vao.isCreated()) vao.destroy();
  check_gl_error();
  if (ibo.isCreated()) ibo.destroy();
  check_gl_error();
  if (vbo.isCreated()) vbo.destroy();
  check_gl_error();

  vao.create();
  check_gl_error();
  vao.bind();
  check_gl_error();

  // QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
  vbo.create();
  check_gl_error();
  vbo.bind();
  vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  check_gl_error();
  vertices_count_ = verts_.size();
  vbo.allocate(verts_.data(), (1 + vertices_count_) * sizeof(float));
  check_gl_error();
  check_gl_error();

  prog->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
  prog->enableAttributeArray(0);

  // QOpenGLBuffer ibo(QOpenGLBuffer::IndexBuffer);
  ibo.create();
  check_gl_error();
  ibo.bind();
  check_gl_error();
  ibo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  check_gl_error();
  lines_count_ = lines_.size();
  check_gl_error();
  ibo.allocate(lines_.data(), (1 + lines_count_) * sizeof(uint));
  // std::cout << "edges into v " << ibo.size() << " " << lines_count_ << "\n";
  check_gl_error();
  // vao.bind();
  // vao.release();
  check_gl_error();
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
  verts_ = VerticesVector{1.000000, -1.000000, -1.000000, 1.000000, -1.000000, 1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 1.000000, 1.000000, 1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 1.000000, -1.000000};

  lines_ = EdgesVector{1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  // set_buffers(verts, lines);
  // std::cout << "add_example_vectors " << lines_.size() << " " << verts_.size() << "\n";
  set_buffers();
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
  bg_color_ = color;
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
  // bg_color_.setRgbF(1,1,1,1);
  // edges_color_.setRgbF(1,0,0,1);
  // vertices_color_.setRgbF(0,0,1,1);
  // vertices_type_ = circle;
  // edges_type_ = solid;
  // vertices_size_ = 10;
  // edges_size_ = 10;
}

void s21::OGLWidget::reset_matrix() {
  Afin->ResetMatrix();
  update();
}

void s21::OGLWidget::set_object(VerticesVector vertex_array, EdgesVector lines_array) {
  verts_ = vertex_array;
  lines_ = lines_array;
  set_buffers();
  // add_example_vectors();


  // VerticesVector verts{1.000000, -1.000000, -1.000000, 1.000000, -1.000000, 1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 1.000000, 1.000000, 1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 1.000000, -1.000000};

  // EdgesVector lines{1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  // set_buffers(verts, lines);

  // index_ = lines_array.data();
  // vertices_count_ = vertex_array.size();
  // lines_count_ = lines_array.size();
  // std::cout << vertices_count_ << " ppppppp " << lines_count_ << "\n";



  // set_buffers(vertex_array, lines_array);
  check_gl_error();
  update();
  check_gl_error();
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
