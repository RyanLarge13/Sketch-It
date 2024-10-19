/*
Sketch It - A learn to draw program
Copyright (C) 2024 Ryan Large

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "Canvas.h"

#include <iostream>

namespace SketchItApplication {
namespace CanvasManager {
Canvas::Canvas() {
  gesture_stylus = Gtk::GestureStylus::create();
  gesture_mouse = Gtk::EventControllerMotion::create();
  gesture_mouse->signal_enter().connect(
      sigc::mem_fun(*this, &Canvas::onMouseDown));
  gesture_mouse->signal_motion().connect(
      sigc::mem_fun(*this, &Canvas::onMouseMove));
  gesture_mouse->signal_leave().connect(
      sigc::mem_fun(*this, &Canvas::onMouseUp));
  gesture_stylus->signal_down().connect(
      sigc::mem_fun(*this, &Canvas::onStylusDown));
  gesture_stylus->signal_motion().connect(
      sigc::mem_fun(*this, &Canvas::onStylusMove));
  gesture_stylus->signal_up().connect(
      sigc::mem_fun(*this, &Canvas::onStylusUp));
  gesture_stylus->signal_proximity().connect(
      sigc::mem_fun(*this, &Canvas::onStylusProximity));
  gesture_stylus->set_stylus_only(true);
  set_has_depth_buffer(true);
  set_auto_render(true);
  signal_realize().connect(sigc::mem_fun(*this, &Canvas::onRealize));
  signal_render().connect(sigc::mem_fun(*this, &Canvas::onRender), false);
  signal_resize().connect(sigc::mem_fun(*this, &Canvas::onResize));
  add_controller(gesture_stylus);
  add_controller(gesture_mouse);
}

void Canvas::onRealize() {
  Gtk::GLArea::on_realize();
  make_current();
  if (glGetError() != GL_NO_ERROR) {
    std::cerr << "Error initializing OpenGL" << std::endl;
    return;
  }
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

bool Canvas::onRender(const Glib::RefPtr<Gdk::GLContext>& context) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnd();
  glFlush();
  return true;
}

void Canvas::onResize(int width, int height) {
  make_current();
  glViewport(0, 0, width, height);
}

// Mouse events
void Canvas::onMouseDown(double x, double y) {}

void Canvas::onMouseMove(double x, double y) {}

void Canvas::onMouseUp() {}

// Stylus events

void Canvas::onStylusDown(double x, double y) {
  tiltX = gesture_stylus->get_axis(Gdk::AxisUse::XTILT).value_or(0.0);
  tiltY = gesture_stylus->get_axis(Gdk::AxisUse::YTILT).value_or(0.0);
  pressure = gesture_stylus->get_axis(Gdk::AxisUse::PRESSURE).value_or(0.0);
  rotation = gesture_stylus->get_axis(Gdk::AxisUse::ROTATION).value_or(0.0);
  std::cout << "TiltX: " << tiltX << "\n";
  std::cout << "TiltY: " << tiltY << "\n";
  std::cout << "Pressure: " << pressure << "\n";
  std::cout << "Rotation: " << rotation << "\n";
  Canvas::StylusPoints newPoint = {{x, y}, {tiltX, tiltY}, pressure, rotation};
  stylusPoints.push_back(newPoint);
}

void Canvas::onStylusMove(double x, double y) {
  tiltX = gesture_stylus->get_axis(Gdk::AxisUse::XTILT).value_or(0.0);
  tiltY = gesture_stylus->get_axis(Gdk::AxisUse::YTILT).value_or(0.0);
  pressure = gesture_stylus->get_axis(Gdk::AxisUse::PRESSURE).value_or(0.0);
  rotation = gesture_stylus->get_axis(Gdk::AxisUse::ROTATION).value_or(0.0);
  std::cout << "TiltX: " << tiltX << "\n";
  std::cout << "TiltY: " << tiltY << "\n";
  std::cout << "Pressure: " << pressure << "\n";
  std::cout << "Rotation: " << rotation << "\n";
  Canvas::StylusPoints newPoint = {{x, y}, {tiltX, tiltY}, pressure, rotation};
  stylusPoints.push_back(newPoint);
}

void Canvas::onStylusUp(double x, double y) {
  std::cout << "Stylus off grid" << "\n";
}

void Canvas::onStylusProximity(double x, double y) {
  std::cout << "Hovering" << "\n";
}

}  // namespace CanvasManager
}  // namespace SketchItApplication
