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

#ifndef CANVAS
#define CANVAS

#include <GL/gl.h>
#include <gtkmm.h>

namespace SketchItApplication {
namespace CanvasManager {
class Canvas : public Gtk::GLArea {
 public:
  Canvas();

 protected:
  void onRealize();
  bool onRender(const Glib::RefPtr<Gdk::GLContext>& context);
  void onResize(int width, int height);
  void onMouseDown(double x, double y);
  void onMouseMove(double x, double y);
  void onMouseUp();
  void onStylusDown(double x, double y);
  void onStylusMove(double x, double y);
  void onStylusUp(double x, double y);
  void onStylusProximity(double x, double y);

 private:
  struct StylusPoints {
    std::pair<double, double> coords;
    std::pair<double, double> tilts;
    double pressure;
    double rotation;
  };
  struct MousePoints {
    std::pair<double, double> coords;
  };
  Glib::RefPtr<Gtk::GestureStylus> gesture_stylus;
  Glib::RefPtr<Gtk::EventControllerMotion> gesture_mouse;
  double tiltX = 0;
  double tiltY = 0;
  double pressure = 0;
  double rotation = 0;
  std::vector<Canvas::StylusPoints> stylusPoints;
  std::vector<Canvas::MousePoints> mousePoints;
};
}  // namespace CanvasManager
}  // namespace SketchItApplication

#endif