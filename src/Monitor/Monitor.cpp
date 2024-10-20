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

#include "Monitor.h"

#include <iostream>

#include "../SketchIt/SketchItWindow.h"

namespace SketchItApplication {
namespace MonitorManager {

// Public
Monitor::Monitor() {
  display = Gdk::Display::get_default();
  if (!display) {
    setDefaultGeometry("In class monitor display failed to be found");
    return;
  }
  if (!SketchItWindow::win) {
    setDefaultGeometry(
        "There was an error accessing the instance of the main application "
        "window in monitor");
    return;
  }
  monitor = display->get_monitor_at_surface(SketchItWindow::win->get_surface());
  if (!monitor) {
    setDefaultGeometry("In class monitor, primary monitor failed to be found");
    return;
  }
  monitor->get_geometry(geometry);
  width = geometry.get_width();
  height = geometry.get_height();
};

// Private
void Monitor::setDefaultGeometry(const std::string& err) {
  std::cout << err << "\n";
  width = 1000;
  height = 800;
}

}  // namespace MonitorManager
}  // namespace SketchItApplication