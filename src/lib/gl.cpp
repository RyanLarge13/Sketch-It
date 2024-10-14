#include "gl.h"

#include <iostream>

MyGLCanvas::MyGLCanvas() {
  gesture_stylus = Gtk::GestureStylus::create();
  gesture_mouse = Gtk::EventControllerMotion::create();
  gesture_mouse->signal_enter().connect(
      sigc::mem_fun(*this, &MyGLCanvas::onMouseDown));
  gesture_mouse->signal_motion().connect(
      sigc::mem_fun(*this, &MyGLCanvas::onMouseMove));
  gesture_mouse->signal_leave().connect(
      sigc::mem_fun(*this, &MyGLCanvas::onMouseUp));
  gesture_stylus->signal_down().connect(
      sigc::mem_fun(*this, &MyGLCanvas::onStylusDown));
  gesture_stylus->signal_motion().connect(
      sigc::mem_fun(*this, &MyGLCanvas::onStylusMove));
  gesture_stylus->signal_up().connect(
      sigc::mem_fun(*this, &MyGLCanvas::onStylusUp));
  gesture_stylus->signal_proximity().connect(
      sigc::mem_fun(*this, &MyGLCanvas::onStylusProximity));
  gesture_stylus->set_stylus_only(true);
  set_has_depth_buffer(true);
  set_auto_render(true);
  signal_realize().connect(sigc::mem_fun(*this, &MyGLCanvas::onRealize));
  signal_render().connect(sigc::mem_fun(*this, &MyGLCanvas::onRender), false);
  signal_resize().connect(sigc::mem_fun(*this, &MyGLCanvas::onResize));
  add_controller(gesture_stylus);
  add_controller(gesture_mouse);
}

void MyGLCanvas::onRealize() {
  Gtk::GLArea::on_realize();
  make_current();
  if (glGetError() != GL_NO_ERROR) {
    std::cerr << "Error initializing OpenGL" << std::endl;
    return;
  }
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

bool MyGLCanvas::onRender(const Glib::RefPtr<Gdk::GLContext>& context) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnd();
  glFlush();
  return true;
}

void MyGLCanvas::onResize(int width, int height) {
  make_current();
  glViewport(0, 0, width, height);
}

// Mouse events
void MyGLCanvas::onMouseDown(double x, double y) {}

void MyGLCanvas::onMouseMove(double x, double y) {}

void MyGLCanvas::onMouseUp() {}

// Stylus events

void MyGLCanvas::onStylusDown(double x, double y) {
  tiltX = gesture_stylus->get_axis(Gdk::AxisUse::XTILT).value_or(0.0);
  tiltY = gesture_stylus->get_axis(Gdk::AxisUse::YTILT).value_or(0.0);
  pressure = gesture_stylus->get_axis(Gdk::AxisUse::PRESSURE).value_or(0.0);
  rotation = gesture_stylus->get_axis(Gdk::AxisUse::ROTATION).value_or(0.0);
  std::cout << "TiltX: " << tiltX << "\n";
  std::cout << "TiltY: " << tiltY << "\n";
  std::cout << "Pressure: " << pressure << "\n";
  std::cout << "Rotation: " << rotation << "\n";
  MyGLCanvas::StylusPoints newPoint = {
      {x, y}, {tiltX, tiltY}, pressure, rotation};
  stylusPoints.push_back(newPoint);
}

void MyGLCanvas::onStylusMove(double x, double y) {
  tiltX = gesture_stylus->get_axis(Gdk::AxisUse::XTILT).value_or(0.0);
  tiltY = gesture_stylus->get_axis(Gdk::AxisUse::YTILT).value_or(0.0);
  pressure = gesture_stylus->get_axis(Gdk::AxisUse::PRESSURE).value_or(0.0);
  rotation = gesture_stylus->get_axis(Gdk::AxisUse::ROTATION).value_or(0.0);
  std::cout << "TiltX: " << tiltX << "\n";
  std::cout << "TiltY: " << tiltY << "\n";
  std::cout << "Pressure: " << pressure << "\n";
  std::cout << "Rotation: " << rotation << "\n";
  MyGLCanvas::StylusPoints newPoint = {
      {x, y}, {tiltX, tiltY}, pressure, rotation};
  stylusPoints.push_back(newPoint);
}

void MyGLCanvas::onStylusUp(double x, double y) {
  std::cout << "Stylus off grid" << "\n";
}

void MyGLCanvas::onStylusProximity(double x, double y) {
  std::cout << "Hovering" << "\n";
}