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

#ifndef MONITOR_H
#define MONITOR_H

#include <gtkmm.h>

namespace SketchItApplication {
namespace MonitorManager {
class Monitor {
 public:
  Monitor();

  void init(Gtk::Window* win);

  Glib::RefPtr<Gdk::Display> display;
  Glib::RefPtr<Gdk::Monitor> monitor;
  Glib::RefPtr<Gdk::Surface> surface;
  Gdk::Rectangle geometry;
  int width;
  int height;

 protected:
  void setDefaultGeometry(const std::string& err);

 private:
};
}  // namespace MonitorManager
}  // namespace SketchItApplication

#endif
